#include "Light.h"

#include "Gizmos.h"

#include "glm/ext.hpp"
#include "glm/gtx/transform.hpp"

namespace pkr
{
	Light::Light(eLightType lightType, bool a_isVisualised) :
		type(lightType),
		isVisualised(a_isVisualised)
	{}


	DirectionalLight::DirectionalLight(bool isVisualised) :
		Light(eLightType::DIRECTIONAL, isVisualised)
	{}
	void DirectionalLight::DrawVisualisation()
	{
		if (!isVisualised)
			return;

		//Draw a thin cylinder
		static float radius = 0.5f;
		static float halfLength = 1.0f;
		static unsigned int segments = 16;

		static float rot = 0;
		rot += 0.5f;

		//https://gamedev.stackexchange.com/questions/118960/convert-a-direction-vector-normalized-to-rotation
		float angZWorld = std::atan2f(direction.y, direction.x);
		mat4 rotXY = glm::rotate(angZWorld, vec3(0, 0, 1));
		float angZ = -std::asin(direction.z);
		mat4 rotZ = glm::rotate(angZ, vec3(0, 1, 0));
		mat4 rotate(rotXY * rotZ);
		//-------------------------------------------------------------


		mat4 transform = glm::translate(position) * rotate * glm::rotate(glm::radians(-90.f), vec3(0, 0, 1))/** glm::lookAt(position, direction, vec3(1,0,0))*/;

		//aie::Gizmos::addAABBFilled(vec3(0), vec3(radius, halfLength, radius), vec4(diffuse, 0.5f), &transform);
		aie::Gizmos::addCylinderFilled(vec3(0), radius, halfLength, segments, glm::vec4(diffuse, 0.5f), &transform);
		aie::Gizmos::addTransform(transform, 5);
	}
	

	OmniLight::OmniLight(eLightType lightType, bool isVisualised) :
		Light(lightType, isVisualised)
	{}
	OmniLight::OmniLight(bool isVisualised) :
		Light(eLightType::OMNI, isVisualised)
	{}
	void OmniLight::DrawVisualisation()
	{
		if (!isVisualised)
			return;

		//Draw a sphere
		static float radius = 0.2f;
		static unsigned int segments = 6;
		glm::mat4 transform = glm::mat4(1) * glm::translate(position);
		aie::Gizmos::addSphere(position, radius, segments, segments, glm::vec4(diffuse, 0.5f), &transform);
	}


	SpotLight::SpotLight(bool isVisualised) :
		OmniLight(eLightType::SPOT, isVisualised)
	{}
	void SpotLight::DrawVisualisation()
	{
		if (!isVisualised)
			return;

		//Draw a thin cylinder
		static float radius = 0.50f;
		static float halfLength = 0.75f;
		static unsigned int segments = 16;
		glm::mat4 transform = glm::mat4(1) * glm::translate(position) * glm::lookAt(position, direction, glm::vec3(0, 1, 0));

		aie::Gizmos::addCylinderFilled(position, radius, halfLength, segments, glm::vec4(diffuse, 0.5f), &transform);
	}
}