//Comprehensive shader with all combined capabilities based on the phong shader
#version 410

layout(location = 0) in vec4 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec4 aTangent;

out vec4 FragPos;
out vec3 Normal;
out vec2 TexCoord;
out vec3 Tangent;
out vec3 BiTangent;

uniform mat4 Model;	//Need this matrix to transform the position
uniform mat4 View;
uniform mat4 Projection;
	//Calculate the Normal by inverse transposing Model

void main()
{
	FragPos = Model * aPosition;
	Normal = mat3(transpose(inverse(Model))) * aNormal;
	TexCoord = aTexCoord;
	Tangent = Normal * aTangent.xyz;
	BiTangent = cross(Normal, Tangent) * aTangent.w;

	gl_Position = Projection * View * FragPos;
}
