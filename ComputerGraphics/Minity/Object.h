#pragma once

#include <vector>

namespace pkr
{
	class Type;

	class Object
	{
	private:
		std::vector<Object> objects;

	public:
		const char* name;		//The name of the object

		void Destroy(Object* obj, float delay = 0);		//Removes a gameobject, component or asset
		Object* Instantiate(Object* obj);				//Clones the object original and returns the clone
		void FindObjectOfType(Type* type);				//
	};
}
