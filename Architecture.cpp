namespace MinityEngine
{
    class string;

    class CoreEngine
    {
    private:
        void Run()
        {
            CoreInit();
            while (!terminating)
            {
                CoreUpdate();
                CoreDraw();
            }
        }

        void CoreInit()
        {
            Start();
        }

        void CoreUpdate()
        {
            Update();
        }

        void CoreDraw()
        {
            Draw();
        }
    public:
        virtual void Start();
        virtual void Update();
        virtual void Draw();
        virtual void End();
        

    }

    class GameObject
    {

    }
    
    class Object;
    {
    public:
        string name;
        static void Destroy();
        static void FindObject();
        static Object Instantiate();
    }

    class GameObject : Object
    {
    private:
        std::vector<Component> m_components;
    public:
        int layer;
        bool active;
        bool isStatic;
        string tag;
    
    }

    class Component : Object
    {
    public:
        GameObject gameObject;
        string tag;
        Component rigidbody;
        Component camera;
        Component light;
        Component animation;
        Component renderer;
        Component audio;
        Component collider;
        Component particleSystem;

        Transform transform;

        void BroadcastMessage();
        void SendMessage();
        void GetComponent();

    }

    class Behaviour : Component
    {
    public:
        bool enabled;
    }

    class MonoBehaviour : Behaviour
    {
    public:
        bool useGUILayout;
        bool runInEditMode;
        static void print(const char *);
        void CancelInvoke();
        void Invoke();
        Coroutine StartCoroutine();
    }
}

using namespace MinityEngine;

namespace MyProject
{
    class 


}