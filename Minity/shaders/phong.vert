//Classic Phong Vertex Shader
#version 410

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 Normal;
layout(location = 2) in vec2 TexCoord;

uniform mat4 ProjectionViewModel;
uniform mat4 ModelMatrix;	//Need this matrix to transform the position
uniform mat3 NormalMatrix;	//Need this matrix to tranform the normal

out vec4 vPosition;
out vec3 vNormal;
out vec2 vTexCoord;

void main()
{
	vPosition = ModelMatrix * Position;
	vNormal = NormalMatrix * Normal.xyz;
	vTexCoord = TexCoord;
	gl_Position = ProjectionViewModel * Position;
}
