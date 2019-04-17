//Comprehensive shader with all combined capabilities based on the phong shader
#version 410
out vec4 FragColour;

//Material
//NOTE! OBJMesh automatically tries to load default values from obj and mtl files
struct Material {
	sampler2D Kd;	//diffuse
	sampler2D Ks;	//specular
//	sampler2D Kn;	//normal
	float shininess;	//aka specular power
};

//Lights
const uint MAX_LIGHTS = 4;
const int DIRECTIONAL = 0;
const int OMNI = 1;
const int SPOT = 2;
//#define MAX_LIGHTS 16
struct Light {		//light 
	//Common
	int type;
	vec3 position;
	vec3 direction;
	vec3 Ia;	//ambient
	vec3 Id;	//diffuse
	vec3 Is;	//specular

	//Point
	float constant;
	float linear;
	float quadratic;

	//Spot
	float cutOff;
	float outerCutOff;
};

//--------------- Inputs ---------------//
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;
//in vec3 Tangent;
//in vec3 BiTangent;
//-------------- Uniforms ------------//
uniform vec3 ViewPos;	//camera position

//uniform sampler2D Ka;
uniform sampler2D Kd;
uniform sampler2D Ks;
uniform float specularPower;

uniform int NumOfLights;
uniform Light Lights[MAX_LIGHTS];
//------------------------------------//

//Function prototypes
vec3 CalcLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	//Ensure inputs are normalized
	vec3 N = normalize(Normal);
//	vec3 T = normalize(Tangent);
//	vec3 B = normalize(BiTangent);
//	mat3 TBN = mat3(T, B, N);

	vec3 viewDir = normalize(ViewPos - FragPos.xyz);

	vec3 result = vec3(1);
	
	//Apply lighting from ALL lights of many types
	for (int i = 0; i < NumOfLights; ++i)
	{
		result += CalcLight(Lights[i], N, FragPos.xyz, viewDir);
	}
	FragColour = vec4(result, 1.0);
}

//----- Functions Definitions -----
//Calculates the color based on light type 
vec3 CalcLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir;
	float attenuation = 1.0;	//Default to 1 so that it won't affect Directional Lights
	float intensity = 1.0;		//Default to 1 so that it won't affect Directional or Point lights

	//Ambient
	vec3 ambient = light.Ia * texture(Kd, TexCoord).rgb;

	//Diffuse
//	lightDir = light.type == DIRECTIONAL ? normalize(-light.direction) : normalize(light.position - fragPos);
	if (light.type == DIRECTIONAL)		//Test to see if ternary operator is the culprit
		lightDir = normalize(-light.direction);
	else
		lightDir = normalize(light.position - fragPos);

	float diffuseTerm = max(dot(normal, lightDir), 0.0);	//The diffuse is brighter if the light is more aligned toward's the surface's normal. If it's on the backside of the surface, nothing (0.0) will be shown
	vec3 diffuse = light.Id * diffuseTerm * texture(Kd, TexCoord).rgb;

	//Specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float specularTerm = pow(max(dot(viewDir, reflectDir), 0.0), specularPower);
	vec3 specular = light.Is * specularTerm * texture(Ks, TexCoord).rgb;
//	float specularTerm = pow(max(dot(viewDir, reflectDir), 0.0), material.specularPower);

	//Intensity and Attenuation for Omni and Spot Lights
	switch (light.type)
	{
	case SPOT:
		float theta = dot(lightDir, normalize(-light.direction));
		float epsilon = (light.cutOff - light.outerCutOff);
		intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
		//continue on to also calculate attentuation...
	case OMNI:
		float distance = length(light.position - fragPos);
		attenuation = 1.0 / (light.constant + light.linear*distance + light.quadratic*(distance*distance));
	}

	//Resultant
	ambient *= attenuation;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;
	return (ambient + diffuse + specular);
}