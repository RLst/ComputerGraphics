namespace Minity
{
	class Behaviour : public Component
	{
	public:
		 void Awake() override {}
		 void Start() override {}
		
		 void FixedUpdate() override {}
		 void Update() override {}
		 void LateUpdate() override {}

		 void End() override {}

	public:
		virtual void OnCollisionEnterStayExit() {};
		virtual void OnMouseDownDragEnterOverUp() {};
		virtual void OnTriggerEnterStayExit() {};

		virtual void log() {};
		virtual void print() {};
	};
}