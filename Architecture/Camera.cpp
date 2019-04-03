
namespace Minity
{
	class Camera : public Component
	{
		Transform* m_transform;
	protected:
		void Init() override
		{
			
		}

		void Update()
		{
			//Update stuff

			//Send to renderer?
		}

		void End();
	};
}