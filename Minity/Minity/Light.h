#pragma once

#include <glm/vec3.hpp>

#include "Component.h"

namespace aie
{
	class ShaderProgram;
}

namespace pkr
{
	enum eLightType
	{
		DIRECTIONAL,
		OMNI,
		SPOT,
		AMBIENT
	};

	struct AmbientLight
	{
		glm::vec3	diffuse;
	};

	class Light
	{
	public:
		Light() = delete;
		Light(eLightType lightType, bool a_isVisualised = true);

		//Common
		bool		isVisualised = true;	//Gizmo shown, Omni = Sphere, Spot = Cylinder, Directional = Thick line
		eLightType	type;
		glm::vec3	position;
		glm::vec3	direction;
		glm::vec3	ambient;
		glm::vec3	diffuse;
		glm::vec3	specular;

		//void Update();
		virtual void DrawVisualisation() = 0;
		virtual void BindToShader(const aie::ShaderProgram& shaderProgram);
	};

	class DirectionalLight : public Light
	{
	public:
		DirectionalLight(bool isVisualised = true);
		void DrawVisualisation() override;
	};

	class OmniLight : public Light
	{
	public:
		OmniLight(bool isVisualised = true);
		float constant;
		float linear;
		float quadratic;

		void DrawVisualisation() override;
	};

	class SpotLight : public OmniLight
	{
	public:
		float cutOff;
		float outerCutOff;
	};
}
