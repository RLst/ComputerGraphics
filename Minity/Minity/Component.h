#pragma once
#include "Object.h"
#include "glm\glm.hpp"

namespace pkr
{
	class Component : public Object
	{
		//Component is abstract?
	private:

	public:
		//Initialisations
		virtual void Awake();
		virtual void Start();

		//Updates
		virtual void FixedUpdate();
		virtual void Update();
		virtual void LateUpdate();

		//Rendering
		virtual void PreRender();
		virtual void Render();
		virtual void PostRender();
		virtual void OnGui();
		virtual void OnRenderGizmos();

		//Shutdowns
		virtual void End();
	};

	class Transform : Component
	{
	private:
		glm::mat4 transform;
	public:
		glm::vec3 position();
		glm::vec3 eulerAngles();
		glm::vec3 scale();
		glm::quat rotation();

		glm::vec3 up() const;
		glm::vec3 forwar() const;
		glm::vec3 right() const;
	};

}
