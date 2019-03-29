#pragma once

#include <vector>

namespace pkr
{
	class Object
	{
	private:
		std::vector<Object> objects;

	public:
		const char* name;

		void Destroy(Object* obj, float delay = 0);
		Object* Instantiate(Object* obj);
		void FindObject(Object* obj);

	};
}
