//Comprehensive shader with all combined capabilities based on the phong shader
#version 410
out vec4 FragColour;

//Material
//NOTE! OBJMesh automatically tries to load default values from obj and mtl files
struct Material {
	sampler2D diffuse;	//diffuse
	sampler2D specular;	//specular
	sampler2D normal;	//normal
	float shininess;	//aka specular power
};

//Lights
const uint MAX_LIGHTS = 16;
//enums
const int DIRECTIONAL = 0;
const int OMNI = 1;
const int SPOT = 2;
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
in vec3 Tangent;
in vec3 BiTangent;
//-------------- Uniforms ------------//
uniform vec3 ViewPos;	//camera position

//uniform Material material;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
float specularPower = 0.0001;		//WET CAR LOOK JUST FOR THE FERRARI
//uniform float specularPower;

uniform int NumOfLights;
uniform Light lights[MAX_LIGHTS];
//------------------------------------//

//Function prototypes
vec3 CalcLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	//Ensure inputs are normalized
	vec3 N = normalize(Normal);
	vec3 T = normalize(Tangent);
	vec3 B = normalize(BiTangent);
	mat3 TBN = mat3(T, B, N);

	vec3 viewDir = normalize(ViewPos - FragPos.xyz);

	vec3 result = vec3(0);
	
	//Apply lighting from ALL lights of many types
	for (int i = 0; i < NumOfLights; ++i)
	{
		result += CalcLight(lights[i], N, FragPos.xyz, viewDir);
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

	//------- Common -------
	lightDir = light.type == DIRECTIONAL || light.type == SPOT ? normalize(-light.direction) : normalize(light.position - fragPos);
	
	//------- Diffuse -------
	float diffuseTerm = max(dot(normal, lightDir), 0.0);	//The diffuse is brighter if the light is more aligned toward's the surface's normal. If it's on the backside of the surface, nothing (0.0) will be shown
	
	//------ Specular -------
	vec3 reflectDir = reflect(-lightDir, normal);
	float specularTerm = pow(max(dot(viewDir, reflectDir), 0.0), specularPower);
//	float specularTerm = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	float lambertTerm = max(0, min(1, dot(normal, -lightDir)));

	switch (light.type)
	{
	case SPOT:
		float theta = dot(lightDir, normalize(-light.direction));
		float epsilon = light.cutOff - light.outerCutOff;
		intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
		//continue on to also calculate attentuation...
	case OMNI:
		float distance = length(light.position - fragPos);
		attenuation = 1.0 / (light.constant + light.linear*distance + light.quadratic*(distance*distance));
		break;
	}

//	vec3 testKa = Ka;
//	vec3 testKd = Kd;
//	vec3 testKs = Ks;
//	diffuseTerm = 0.3;
//	specularTerm = 0.2;

	//Resultant
//	vec3 ambient = light.Ia * testKa * texture(material.diffuse, TexCoord).xyz;
//	vec3 diffuse = light.Id * testKd * diffuseTerm * texture(material.diffuse, TexCoord).xyz; // * lambertTerm;
//	vec3 specular = light.Is * testKs * specularTerm * texture(material.specular, TexCoord).xyz;
	vec3 ambient = light.Ia * Ka;
	vec3 diffuse = light.Id * diffuseTerm * Kd; //* lambertTerm;
	vec3 specular = light.Is * specularTerm * Ks;	

	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;
	return (ambient + diffuse + specular);
}