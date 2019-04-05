//Comprehensive shader with all combined capabilities based on the phong shader
#version 410

layout(location = 0) in vec4 aPosition;
layout(location = 1) in vec4 aNormal;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec4 aTangent;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;	//Need this matrix to transform the position
uniform mat3 Normal;	//Need this matrix to tranform the normal

out vec4 vPosition;
out vec3 vNormal;
out vec2 vTexCoord;
out vec3 vTangent;
out vec3 vBiTangent;

void main()
{
	vPosition = Model * aPosition;
	vNormal = Normal * aNormal.xyz;
	vTexCoord = aTexCoord;
	vTangent = Normal * aTangent.xyz;
	vBiTangent = cross(vNormal, vTangent) * aTangent.w;
	gl_Position = Projection * View * vPosition;
}
