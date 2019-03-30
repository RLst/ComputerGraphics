#version 410

uniform vec3 Kd;

out vec4 FragColour;

void main()
{
	FragColour = vec4(Kd, 1);
}










//struct GSOutput
//{
//	float4 pos : SV_POSITION;
//};
//
//[maxvertexcount(3)]
//void main(
//	triangle float4 input[3] : SV_POSITION, 
//	inout TriangleStream< GSOutput > output
//)
//{
//	for (uint i = 0; i < 3; i++)
//	{
//		GSOutput element;
//		element.pos = input[i];
//		output.Append(element);
//	}
//}