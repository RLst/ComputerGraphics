//A gameobject consists of components

#include <vector>

class Components;
class Transform;

namespace Minity
{
	class GameObject
	{
	protected:
		Transform* transform;
		std::vector<Components*> components;

	public:

		void Init()
		{
			for (auto c : components)
			{
				c->Awake();
				c->Start();
			}
		}

		void Update()
		{
			for (auto c : components)
			{
				c->Update();
			}
		}

		void End()
		{
			for (auto c : components)
			{
				c->End();
			}
		}
	};
}