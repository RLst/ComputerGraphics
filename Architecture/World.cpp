//A world consists of gameobjects

#include <vector>

#include "GameObject.cpp"

namespace Minity
{
	class World
	{
	protected:
		std::vector<GameObject*> gameObjects;

	public:
		void AddGameObject();
		void GetGameObject();
		void RemoveGameObject();

		void Init()	//Build the world
		{
			for (auto& go : gameObjects)
				go->BaseInit();
		}

		void Update()	//Update the world
		{
			for (auto& go : gameObjects)
				go->BaseUpdate();
		}

		void End()		//End the world
		{
			for (auto& go : gameObjects)
				go->BaseEnd();
		}
	};
} // Minity


			// for (auto go : gameObjects)
			// {
			// 	if (go->isActive())
			// 	{
			// 		if (go->JustAwoken())
			// 		{
			// 			go->Awake();
			// 		}
			// 	}
			// 	go->awake();
			// }