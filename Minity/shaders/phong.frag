//Classic Phong Fragment Shader
#version 410

in vec3 vNormal;

uniform vec3 Ia;    //Ambient
uniform vec3 Id;    //Diffuse
uniform vec3 Is;    //Specular
uniform vec3 LightDirection;

out vec4 FragColour;

void main()
{
    //Ensure normal and light direction are normalised
    vec3 N = normalize(vNormal);
    vec3 L = normalize(LightDirection);

    //Calculate lambert term (negate light direction)
    float lambertTerm = max(0, min(1, dot(N, -L)));

    //Calculate diffuse
    vec3 diffuse = Id * lambertTerm;

    //Final output
    FragColour = vec4(diffuse, 1);
}