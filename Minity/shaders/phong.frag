//Classic Phong Fragment Shader
#version 410

in vec4 vPosition;
in vec3 vNormal;

//Camera
uniform vec3 CameraPosition;

//Lights
uniform vec3 Ia;    //Ambient
uniform vec3 Id;    //Diffuse
uniform vec3 Is;    //Specular
uniform vec3 LightDirection;

//Material
uniform vec3 Ka;	//Ambient
uniform vec3 Kd;	//Diffuse
uniform vec3 Ks;	//Specular
uniform float SpecularPower;

out vec4 FragColour;

void main()
{
    //Ensure normal and light direction are normalised
    vec3 N = normalize(vNormal);
    vec3 L = normalize(LightDirection);

    //Calculate lambert term (negate light direction)
    float lambertTerm = max(0, min(1, dot(N, -L)));

	//Calculate view vector and reflection vector
	vec3 V = normalize(CameraPosition - vPosition.xyz);
	vec3 R = reflect(L, N);

	//Caulcate the specular term
	float specularTerm = pow(max(0, dot(R, V)), SpecularPower);

    //Calculate diffuse
	vec3 ambient = Ia * Ka;
	vec3 diffuse = Id * Kd * lambertTerm;
	vec3 specular = Is * Ks * specularTerm;

    //Final output
    FragColour = vec4(ambient + diffuse + specular, 1);
}