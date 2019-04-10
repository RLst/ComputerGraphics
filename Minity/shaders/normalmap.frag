//A Normal Map Fragment Shader
#version 410
out vec4 FragColour;

in vec4 FragPos;
in vec3 Normal;
in vec2 TexCoord;
in vec3 Tangent;
in vec3 BiTangent;

//Textures
uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;

//Camera
uniform vec3 ViewPos;

//Material
uniform vec3 Ka;	//Ambient
uniform vec3 Kd;	//Diffuse
uniform vec3 Ks;	//Specular
uniform float specularPower;

//Lights
uniform vec3 Ia;    //Ambient
uniform vec3 Id;    //Diffuse
uniform vec3 Is;    //Specular
uniform vec3 LightDirection;

void main()
{
    //Ensure normal and light direction are normalised
    vec3 N = normalize(Normal);
	vec3 T = normalize(Tangent);
	vec3 B = normalize(BiTangent);
    vec3 L = normalize(LightDirection);
	mat3 TBN = mat3(T, B, N);

	vec3 texDiffuse = texture(diffuseTexture, TexCoord).rgb;
	vec3 texSpecular = texture(specularTexture, TexCoord).rgb;
	vec3 texNormal = texture(normalTexture, TexCoord).rgb;

    //Calculate lambert term (Don't negate light direction?)
    float lambertTerm = max(0, min(1, dot(N, -L)));

	//Calculate view vector and reflection vector
	vec3 V = normalize(ViewPos - FragPos.xyz);
	vec3 R = reflect(L, N);

	//Calculate the specular term
	float specularTerm = pow(max(0, dot(R, V)), specularPower);

	N = TBN * (texNormal * 2 - 1);

    //Calculate diffuse
	vec3 ambient = Ia * Ka;
	vec3 diffuse = N * Id * Kd * texDiffuse * lambertTerm;
	vec3 specular = Is * Ks * texSpecular * specularTerm;

    //Final output
    FragColour = vec4(ambient + diffuse + specular, 1);
}