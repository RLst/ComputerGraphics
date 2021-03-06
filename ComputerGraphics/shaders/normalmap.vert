//Classic Phong Vertex Shader
#version 410

layout(location = 0) in vec4 aPosition;
layout(location = 1) in vec4 aNormal;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec4 aTangent;

uniform mat4 uProjectionViewModel;
uniform mat4 uModel;	//Need this matrix to transform the position
uniform mat3 uNormal;	//Need this matrix to tranform the normal

out vec4 FragPos;
out vec3 Normal;
out vec2 TexCoord;
out vec3 Tangent;
out vec3 BiTangent;

void main()
{
	FragPos = uModel * aPosition;
	Normal = uNormal * aNormal.xyz;
	TexCoord = aTexCoord;
	Tangent = uNormal * aTangent.xyz;
	BiTangent = cross(Normal, Tangent) * aTangent.w;
	gl_Position = uProjectionViewModel * aPosition;
}
