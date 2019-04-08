//Comprehensive shader with all combined capabilities based on the phong shader
#version 410

in vec4 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;
in vec3 vTangent;
in vec3 vBiTangent;

//Texture
uniform sampler2D DiffuseTexture;
uniform sampler2D SpecularTexture;
uniform sampler2D NormalTexture;

//Camera
uniform vec3 CameraPosition;

//Lights
const unsigned int NUM_OF_LIGHTS = 32;
struct Light {
	vec3 Diffuse;
	vec3 Direction;
};
uniform Light Lights[NUM_OF_LIGHTS];

uniform vec3 Ia;    //Ambient
uniform vec3 Id;    //Diffuse
uniform vec3 Is;    //Specular
//uniform vec3 LightDirection;

//Material
uniform vec3 Ka;	//Ambient
uniform vec3 Kd;	//Diffuse
uniform vec3 Ks;	//Specular
uniform float SpecularPower;

out vec4 FragColour;

void main()
{
    //Ensure normal and light direction are normalised
    vec3 N = normalize(vNormal);
    vec3 L = normalize(LightDirection);

	vec3 texDiffuse = texture(DiffuseTexture, vTexCoord).rgb;

    //Calculate lambert term (negate light direction)
    float lambertTerm = max(0, min(1, dot(N, -L)));

	//Calculate view vector and reflection vector
	vec3 V = normalize(CameraPosition - vPosition.xyz);
	vec3 R = reflect(L, N);

	//Caulcate the specular term
	float specularTerm = pow(max(0, dot(R, V)), SpecularPower);

    //Calculate diffuse
	vec3 ambient = Ia * Ka;
	vec3 diffuse = Id * Kd * texDiffuse * lambertTerm;
	vec3 specular = Is * Ks * specularTerm;

    //Final output
    FragColour = vec4(ambient + diffuse + specular, 1);
}