//A world consists of gameobjects

#include <vector>

class GameObject;

namespace Minity
{
	class World
	{
	protected:
		std::vector<GameObject*> gameObjects;

	public:
		void Init()	//Build the world
		{
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

			for (auto go : gameObjects)
				go->Init();

		}

		void Update()	//Update the world
		{
			for (auto go : gameObjects)
				go->Update();
		}

		void End()		//End the world
		{
			for (auto go : gameObjects)
				go->End();
		}
	};
} // Minity
