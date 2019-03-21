namespace MinityEngine
{
    class string;
    std::vector<GameObject*> gameObjects;

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
            Update()
            {
                for (auto go : gameObjects)
                {
                    go->update();
                }
            }
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
        std::string m_name;
        std::vector<Component> components;
        Scene* m_scene = nullptr;

        GameObject()
        {
            addComponent(new Transform());
        }

        void addedToScene(const Scene& scene)
        {
            m_scene = scene;
        }

        void addComponent(Component component)
        {
            components.push_back(component);
            component.addedToGameObject(this);
        }

        void update()
        {
            //Run update on all components

        }

    private:
        void draw() //Should this be hidden from the user???
        {
            //Loop through all components and draw if necessary
            for (auto c : components)
            {
                //If the component has a renderer component then draw that component?
                if (c->draw() != null)
                {
                    c->draw();
                }
            }
        }
    }
    
    class Object;
    {
    public:
        string name;
        static void Destroy();
        static void FindObject();
        static Object Instantiate();
    }

    /////////
    class Scene
    {
        std::vector<GameObject> gameObjects;
        EventDispatcher* m_eventDispatcher;
        SceneRender* m_renderer;
    }


    //////////

    class GameObject //: Object
    {
    private:
        std::vector<Component> m_components;
    public:
        GameObject()
        {

        }

        int layer;
        bool active;
        bool isStatic;
        string tag;
    
    }

    class Component
    {
        virtual void Start() {}
        virtual void Update() {}
        void Draw() {}
        void End() {}
    }

    class Transform : Component
    {
    public:
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
    }

    class Behaviour : Component
    {
    public:
        bool enabled;

        void Update() override {} //?

    }

    class PlayerBehaviour : Behaviour
    {
        void Update() override
        {
            
        }
    }

    // class Component : Object
    // {
    // public:
    //     GameObject gameObject;
    //     string tag;
    //     Component rigidbody;
    //     Component camera;
    //     Component light;
    //     Component animation;
    //     Component renderer;
    //     Component audio;
    //     Component collider;
    //     Component particleSystem;

    //     Transform transform;

    //     void BroadcastMessage();
    //     void SendMessage();
    //     void GetComponent();

    // }



    // class MonoBehaviour : Behaviour
    // {
    // public:
    //     bool useGUILayout;
    //     bool runInEditMode;
    //     static void print(const char *);
    //     void CancelInvoke();
    //     void Invoke();
    //     Coroutine StartCoroutine();
    // }
}

using namespace MinityEngine;

namespace MyProject
{
    class 


}