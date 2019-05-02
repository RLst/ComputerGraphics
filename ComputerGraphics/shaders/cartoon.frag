#version 410

//Diffuse light properties
vec3 DiffuseLightDirection = vec3(1, 0, 0);
vec4 DiffuseColour = vec4(1,1,1,1);
float DiffuseIntensity = 1.0f;

//Toon shader properties
vec4 LineColor = vec4(0, 0, 0, 1);
float LineThickness = 0.03f;

//Texture properties
uniform sampler2D DiffuseTexture;


