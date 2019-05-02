#pragma once
#include "Object.h"

namespace pkr
{
	class World;
	class Transform;

	class GameObject : public Object
	{
	private:


	public:
		GameObject(const char* name);

		//Properties
		const char*		tag;

		//Cache
		World*			world;	//The world that this game object is part of
		Transform*		transform;
	};
}
