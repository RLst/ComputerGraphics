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

		//Draw a cylinder
		static float radius = 0.3f;
		static float halfLength = 0.75f;
		static unsigned int segments = 16;
		glm::mat4 transform = glm::mat4(1) * glm::translate(position) * glm::lookAt(position, direction, glm::vec3(0, 1, 0));

		aie::Gizmos::addCylinderFilled(position, radius, halfLength, segments, glm::vec4(diffuse, 0.5f), &transform);
		
		//...
	}
	


	OmniLight::OmniLight(bool isVisualised) :
		Light(eLightType::OMNI, isVisualised)
	{}
	void OmniLight::DrawVisualisation()
	{
		if (!isVisualised)
			return;

		//Draw a sphere
		static float radius = 0.3f;
		static unsigned int segments = 8;
		glm::mat4 transform = glm::mat4(1) * glm::translate(position) * glm::lookAt(position, direction, glm::vec3(0, 1, 0));

		aie::Gizmos::addSphere(position, radius, segments, segments, glm::vec4(diffuse, 0.5f), &transform);

		//...
	}
}