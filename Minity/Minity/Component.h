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
		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void End() = 0;
	};

	class Transform : Component
	{
	private:
		glm::mat4 transform;
	public:
		glm::vec3 position() const;
		glm::vec3 eulerAngles() const;
		glm::vec3 scale() const;
		glm::quat rotation() const;

		glm::vec3 up() const;
		glm::vec3 forwar() const;
		glm::vec3 right() const;
	};

}
