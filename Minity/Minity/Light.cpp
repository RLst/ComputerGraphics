#include "Light.h"

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

//-----------------------------------------------------------
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

	//-----------------------------------------------------------
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

//-----------------------------------------------------------
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

//-----------------------------------------------------------
SpotLight::SpotLight(bool isVisualised) :
	OmniLight(LightType::SPOT, isVisualised)
{}
SpotLight::SpotLight(float a_constant, float a_linear, float a_quadratic, float a_cutOff, float a_outerCutOff, bool isVisualised) :
	OmniLight(LightType::SPOT, isVisualised),
	cutOff(a_cutOff), outerCutOff(a_outerCutOff)
{
	//Wonder why I can't initialize in the member init list?
	constant = a_constant;
	linear = a_linear;
	quadratic = a_quadratic;

	//Calculate the multiplier between linear and quadratic values
	lin2quadFactor = linear / quadratic;
}
void SpotLight::DrawVisualisation()
{
	if (!isVisualised)
		return;

	//----------------- Calclate Transform ------------------------
	//https://gamedev.stackexchange.com/questions/118960/convert-a-direction-vector-normalized-to-rotation
	float angZWorld = std::atan2f(direction.y, direction.x);
	mat4 rotXY = glm::rotate(angZWorld, vec3(0, 0, 1));
	float angZ = -std::asin(direction.z);
	mat4 rotZ = glm::rotate(angZ, vec3(0, 1, 0));
	mat4 rotate(rotXY * rotZ);
	//-------------------------------d------------------------------
	mat4 transform = glm::translate(position) * rotate * glm::rotate(glm::radians(-90.f), vec3(0, 0, 1));

	//----------------- Calculate gizmo sizes -----------------------
	float length = pkr::Math::Map(linear, minLinearValue, maxLinearValue, gz_maxSize, gz_minSize);
	float coneFactor = 0.5f;
	float cutOffConeSize = cutOff * coneFactor;
	float outerCutOffConeSize = outerCutOff * coneFactor;

	aie::Gizmos::addCylinderFilled(vec3(0), cutOff, length, gz_segments, glm::vec4(diffuse, 0.3f), &transform);
	aie::Gizmos::addCylinderFilled(vec3(0), outerCutOff, length, gz_segments, glm::vec4(diffuse, 0.1f), &transform);
	aie::Gizmos::addTransform(transform, 2);
}
}