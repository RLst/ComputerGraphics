//A Simple textured shader
#version 410

in vec2 vTexCoord;

uniform float Intensity;
uniform sampler2D DiffuseTexture;

out vec4 FragColour;

void main()
{
	FragColour = texture(DiffuseTexture, vTexCoord) * Intensity;
}