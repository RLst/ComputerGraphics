//A world consists of gameobjects

#include <vector>
#include <memory>

#include "GameObject.cpp"

//NOTE!
//Hmmmm... in this case World is akin to App
//and MyWorld is akin to Game

//Thinking and brainstorming...
//Core should hold a list of worlds and a list of all objects
//Each object should have a parent reference to only ONE world

namespace Minity
{
	//Type enums?
	enum class Type		//This should be more global
	{
		PLAYER,
		ENEMY
	};

	class World		//Abstract
	{
	protected:
		std::vector<std::unique_ptr<GameObject>> gameObjects;

	public:
		GameObject* AddGameObject(Type type);
		GameObject* AddGameObject()...;
		void GetGameObject();
		void RemoveGameObject();

		virtual void Create() = 0;

		void Init()	//Start the world
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

	class MyWorld : public World
	{
	private:
		GameObject* m_player;
		std::vector<GameObject*> m_enemies;

	public:
		void Create() override
		{
			////THIS HERE IS essentially the equivalent of the unity editor where you create and setup THIS PARTICULAR WORLD (SCENE) and game objects.
			//Components must be added to game objects and set up here as well
			//YOU MUST USE "AddGameObject" so that upon shutdown all the deallocation will be handled correctly

			m_player = AddGameObject(Type::PLAYER);		
			
			for (int i = 0; i < 10; ++i)
			{
				m_enemies.push_back(AddGameObject(Type::ENEMY));
			}
		}
	};
}

 // Minity


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