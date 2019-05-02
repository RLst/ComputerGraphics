////A Simple textured shader
//#shader vertex
//#version 330 core
//
//layout(location = 0) in vec4 aPosition;
//layout(location = 1) in vec4 aNormal;
//layout(location = 2) in vec2 aTexCoord;
//layout(location = 3) in vec4 aTangent;
//
//uniform mat4 uProjectionViewModel;
//uniform mat4 uModel;	//Need this matrix to transform the position
//uniform mat3 uNormal;	//Need this matrix to tranform the normal
//
//out vec4 FragPos;
//out vec3 Normal;
//out vec2 TexCoord;
//out vec3 Tangent;
//out vec3 BiTangent;
//
//void main()
//{
//	FragPos = uModel * aPosition;
//	Normal = uNormal * aNormal.xyz;
//	TexCoord = aTexCoord;
//	Tangent = uNormal * aTangent.xyz;
//	BiTangent = cross(Normal, Tangent) * aTangent.w;
//	gl_Position = uProjectionViewModel * aPosition;
//};

#version 410
in vec4 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D diffuseTexture;
uniform sampler2D normalTexture;
uniform sampler2D specularTexture;

uniform vec3 ViewPos;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float specularPower;

uniform vec3 Ia;
uniform vec3 Id;
uniform vec3 Is;
uniform vec3 LightDirection;

out vec4 FragColour;

void main()
{
	vec3 N = normalize(Normal);
	vec3 L = normalize(LightDirection);

	float lambertTerm = max(0, min(1, dot(N, -L)));

	vec3 V = normalize(ViewPos - FragPos.xyz);
	vec3 R = reflect(L, N);

	float specularTerm = pow(max(0, dot(R,V)), specularPower);

	vec3 texDiffuse = texture(diffuseTexture, TexCoord).rgb;
	vec3 texNormal = texture(normalTexture, TexCoord).rgb;
	vec3 texSpecular = texture(specularTexture, TexCoord).rgb;

	vec3 ambient = Ia * Ka;
	vec3 diffuse = Id * Kd * lambertTerm * texDiffuse;
	vec3 specular = Is * Ks * specularTerm * texSpecular;

	FragColour = vec4(ambient + diffuse + specular, 1);
};