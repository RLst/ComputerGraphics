
namespace Minity
{
	class GameObject;

	class Component : public Object
	{
	protected:
		GameObject* m_gameObject;	//The game object this component is attached to. A component is always attached to a game object. Should be set when the component is created
		Transform* m_transform;		//Cached transform component that is attached to the components 
		const char* tag;			//Undesirable

		//User can choose to override, else these core functions will just do nothing
		virtual void Awake() {}
		virtual void Start() {}
		virtual void Update() {}
		virtual void End() {}
	public:
		void BaseInit()
		{
			//Get the transform
			m_transform = m_gameObject->m_transform;
			Awake();
			Start();
		}

		void BaseUpdate()
		{
			Update();
		}

		void BaseEnd()
		{
			End();
		}
	}
}