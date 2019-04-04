//A Normal Map Fragment Shader
#version 410

in vec4 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;
in vec3 vTangent;
in vec3 vBiTangent;

//Textures
uniform sampler2D DiffuseTexture;
uniform sampler2D SpecularTexture;
uniform sampler2D NormalTexture;

//Camera
uniform vec3 CameraPosition;

//Material
uniform vec3 Ka;	//Ambient
uniform vec3 Kd;	//Diffuse
uniform vec3 Ks;	//Specular
uniform float SpecularPower;

//Lights
uniform vec3 Ia;    //Ambient
uniform vec3 Id;    //Diffuse
uniform vec3 Is;    //Specular
uniform vec3 LightDirection;

out vec4 FragColour;

void main()
{
    //Ensure normal and light direction are normalised
    vec3 N = normalize(vNormal);
	vec3 T = normalize(vTangent);
	vec3 B = normalize(vBiTangent);
    vec3 L = normalize(LightDirection);
	mat3 TBN = mat3(T, B, N);

	vec3 texDiffuse = texture(DiffuseTexture, vTexCoord).rgb;
	vec3 texSpecular = texture(SpecularTexture, vTexCoord).rgb;
	vec3 texNormal = texture(NormalTexture, vTexCoord).rgb;

    //Calculate lambert term (Don't negate light direction?)
    float lambertTerm = max(0, dot(N, -L));

	//Calculate view vector and reflection vector
	vec3 V = normalize(CameraPosition - vPosition.xyz);
	vec3 R = reflect(L, N);

	//Calculate the specular term
	float specularTerm = pow(max(0, dot(R, V)), SpecularPower);

    //Calculate diffuse
	vec3 ambient = Ia * Ka;
	vec3 diffuse = Id * Kd * texDiffuse * lambertTerm;
	vec3 specular = Is * Ks * texSpecular * specularTerm;

    //Final output
    FragColour = vec4(ambient + diffuse + specular, 1);
}