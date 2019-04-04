//A gameobject consists of components

#include <vector>

#include "Component.cpp"
class Transform;

namespace Minity
{
	class GameObject : Object
	{
	protected:
		bool m_isStatic
		World* m_ofWorld;	//The world that this gameobject is part of
		Transform* m_transform;		//Get reference in Init()
		std::vector<Component*> components;

	public:
		void GetComponent();
		void AddComponent()
		{
			//Make the component...
			components.push_back(new Component());

			//Set component's game object reference
			components.end()->m_gameObject = this;
		}
		void RemoveComponent();
		void SetActive();
		void isActive();
		void BroadcastMessage();	//Not important, tag based, prone to error
		void SendMessage();			//Not important

		void BaseInit()
		{
			m_transform = GetComponent<Transform>();

			for (auto c : components)
			{
				c->BaseInit();
			}
		}

		void BaseUpdate()
		{
			for (auto c : components)
			{
				c->BaseUpdate();
			}
		}

		void BaseEnd()
		{
			for (auto c : components)
			{
				c->BaseEnd();
			}
		}
	};
}