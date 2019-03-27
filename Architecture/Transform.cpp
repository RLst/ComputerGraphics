//Static class that will be always available to the user

namespace glm{
	struct vec3;
	struct quat;
	struct vec4;
	struct mat4;
}

namespace Minity
{
	class Transform : public Component
	{
		friend class Core;

	public:
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
	};
}