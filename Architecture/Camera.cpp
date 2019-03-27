
namespace Minity
{
	class Camera : public Component
	{
	private:
		vec3 position;
		vec3 rotation;
		float fov;

	protected:
		void Init()
		{}

		void Update()
		{
			//Update stuff

			//Send to renderer?
		}

		void End();
	};
}