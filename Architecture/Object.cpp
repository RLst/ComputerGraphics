
//Base class of Gameobject and Component and maybe world?
//Is this even really necessary?

namespace Minity
{
	class Object
	{
	protected:
		const char* name;
	protected:
		static void Destroy();
		static void FindObjectOfType();
		static void Instantiate();
	}
}