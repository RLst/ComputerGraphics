#pragma once

#include <glm/vec3.hpp>

#include "Component.h"

namespace pkr
{
	enum eLightType
	{
		DIRECTIONAL,
		OMNI,
		SPOT,
		AMBIENT
	};

	class Light
	{
	protected:
		bool		isVisualised = false;	//Gizmo shown, Omni = Sphere, Spot = Cylinder, Directional = Axes

		virtual void Update();

	public:
		Light() = delete;
		Light(eLightType lightType);
		eLightType	type;
		glm::vec3	position;
		glm::vec3	direction;
		glm::vec3	diffuse;
		glm::vec3	specular;

		struct DirectionalLight
		{
			glm::vec3 position;
		} directionalLight;
	};

}
