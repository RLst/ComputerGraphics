#include "Light.h"

#include <iostream>

#include "Gizmos.h"
#include "Math.h"

#include "glm/ext.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/compatibility.hpp"	//For lerp!

namespace pkr
{
Light::Light(LightType lightType, bool a_isVisualised) :
	type(lightType),
	isVisualised(a_isVisualised)
{}


DirectionalLight::DirectionalLight(bool isVisualised) :
	Light(LightType::DIRECTIONAL, isVisualised)
{}
void DirectionalLight::DrawVisualisation()
{
	if (!isVisualised)
		return;

	//Draw a thick cylinder
	static unsigned int segments = 12;
	static float radius = 0.5f;
	static float halfLength = 0.75f;

	//https://gamedev.stackexchange.com/questions/118960/convert-a-direction-vector-normalized-to-rotation
	float angZWorld = std::atan2f(direction.y, direction.x);
	mat4 rotXY = glm::rotate(angZWorld, vec3(0, 0, 1));
	float angZ = -std::asin(direction.z);
	mat4 rotZ = glm::rotate(angZ, vec3(0, 1, 0));
	mat4 rotate(rotXY * rotZ);
	//-------------------------------------------------------------
	mat4 transform = glm::translate(position) * rotate * glm::rotate(glm::radians(-90.f), vec3(0, 0, 1))/** glm::lookAt(position, direction, vec3(1,0,0))*/;

	//aie::Gizmos::addAABBFilled(vec3(0), vec3(radius, halfLength, radius), vec4(diffuse, 0.5f), &transform);
	aie::Gizmos::addCylinderFilled(vec3(0), radius, halfLength, segments, glm::vec4(diffuse, 0.3f), &transform);
	aie::Gizmos::addTransform(transform, 3);
}


OmniLight::OmniLight(LightType lightType, bool isVisualised) :
	Light(lightType, isVisualised)
{}
OmniLight::OmniLight(bool isVisualised) :
	Light(LightType::OMNI, isVisualised)
{}
OmniLight::OmniLight(float a_constant, float a_linear, float a_quadratic, bool isVisualised) :
	Light(LightType::OMNI, isVisualised),
	constant(a_constant), linear(a_linear), quadratic(a_quadratic)
{
	//Calculate the multiplier between linear and quadratic values
	lin2quadFactor = linear / quadratic;
}
void OmniLight::RecalcQuadraticValue()
{
	//Calc quad based on linear
	quadratic = linear * lin2quadFactor;
}
void OmniLight::DrawVisualisation()
{
	if (!isVisualised)
		return;

	float radius = pkr::Math::Map(linear, minLinearValue, maxLinearValue, gz_maxSize, gz_minSize);

	glm::mat4 transform = glm::mat4(1) * glm::translate(position);
	aie::Gizmos::addSphere(position, radius, gz_segments, gz_segments, glm::vec4(diffuse, 0.3f), &transform);
}


SpotLight::SpotLight(bool isVisualised) :
	OmniLight(LightType::SPOT, isVisualised)
{}
void SpotLight::DrawVisualisation()
{
	if (!isVisualised)
		return;

	//Draw a thin cylinder
	static unsigned int segments = 12;
	static float maxradius = 0.5f;
	static float maxhalflength = 0.5f;

	//Calc radius based on light settings
	//-----TEMP! BAD PRACTICE, this should be in some kind of update function
	static float originalLinear = linear;	//Capture original value
	static float originalQuadratic = quadratic;
	static float quadFactor = linear / quadratic;


	//https://gamedev.stackexchange.com/questions/118960/convert-a-direction-vector-normalized-to-rotation
	float angZWorld = std::atan2f(direction.y, direction.x);
	mat4 rotXY = glm::rotate(angZWorld, vec3(0, 0, 1));
	float angZ = -std::asin(direction.z);
	mat4 rotZ = glm::rotate(angZ, vec3(0, 1, 0));
	mat4 rotate(rotXY * rotZ);
	//-------------------------------------------------------------

	mat4 transform = glm::translate(position) * rotate * glm::rotate(glm::radians(-90.f), vec3(0, 0, 1));
	//mat4 transform = glm::translate(position) * glm::lookAt(position, vec3(0), vec3(0,1,0)) * glm::rotate(glm::radians(-90.f), vec3(0, 0, 1));

	aie::Gizmos::addCylinderFilled(vec3(0), maxradius, maxhalflength, segments, glm::vec4(diffuse, 0.3f), &transform);
	aie::Gizmos::addTransform(transform, 2);

	//Calc quad based on linear
	quadratic = linear * quadFactor;
}
}