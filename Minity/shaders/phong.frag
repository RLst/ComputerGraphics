//Classic Phong Fragment Shader
#version 410

in vec3 vNormal;

uniform vec3 LightDirection;

out vec4 FragColour;

void main()
{
    //Ensure normal and light direction are normalised
    vec3 N = normalize(vNormal);
    vec3 L = normalize(LightDirection);

    //Calculate lambert term (negate light direction)
    float lambertTerm = max(0, min(1, dot(N, -L)));

    //output lamber as grayscale
    FragColour = vec4(lambertTerm, lambertTerm, lambertTerm, 1);
}