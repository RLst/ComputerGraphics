//Comprehensive shader with all combined capabilities based on the phong shader
#version 410

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec4 aTangent;

//----------- Uniforms ------------//
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
//---------------------------------//
out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;
out vec3 Tangent;
out vec3 BiTangent;
//--------------------------------//

//uniform mat4 uProjectionViewModel;
//uniform mat4 uModel;
//uniform mat3 uNormal;

void main()
{
//	FragPos = uModel * vec4(aPosition, 1.0);
//	Normal = uNormal * aNormal.xyz;
//	TexCoord = aTexCoord;
//
//	Tangent = uNormal * aTangent.xyz;
//	BiTangent = cross(Normal, Tangent) * aTangent.w;
//
//	gl_Position = uProjectionViewModel * vec4(aPosition, 1.0);

	FragPos = vec3(uModel * vec4(aPosition, 1.0));
	Normal = mat3(transpose(inverse(uModel))) * aNormal;
	TexCoord = aTexCoord;
	Tangent = Normal * aTangent.xyz;
	BiTangent = cross(Normal, Tangent) * aTangent.w;

	gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
}
