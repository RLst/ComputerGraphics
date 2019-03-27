#include "glm/ext.hpp"
#include "GLFW/glfw3.h"
#include <vector>
#include <string>

/* Suggested file layout
namespace Minity
    //OpenGL
    gl_core_4_4.h

    //Core modules
    App     //Main app
    Time
    Random
    Colour
    Math
    Input
    Graphics
    
    GameObject
    World

    Components
        //Required
        Transform

        //Optionals
        Rigidbody/2D
        Collider/2D
        Light
        Camera
        Renderer
        Gizmo  //Requires Renderer component
        GUI_Text

        Behaviour        //Base for all scripts


*/

namespace Minity {
namespace Core
{
    class Random;   //Functions to return good random using MT engines
    class Colour;   //Functions to return colours in the form of glm::vec4
    class Math;     //Functions like math constants (pi, e), sin, cos etc?

    std::vector<GameObject*> gameObjects;
    std::vector<World*> worlds;

    class CoreEngine
    {
    private:
        bool m_isTerminating;
        GLFWwindow* m_window;

        CoreEngine() :
            m_window(nullptr),      //Reset window
            m_isTerminating(false)  //App is still running
        {}


        void Run()
        {
            CoreInit();
            while (!m_isTerminating)
            {
                CoreUpdate();
                CoreDraw();
            }
            CoreEnd();
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

        void CoreEnd()
        {
            End();
        }

    public:
        virtual void Start() {}
        virtual void Update() {}
        // virtual void Draw() {}
        virtual void End() {}
    };

    //////////////////////
    class Object
    {
        //Base to GameObject and Component
    public:
        string name;
        static void Destroy();
        static void FindObject();
        static Object Instantiate();
    };

    ///////////////////////////
    class GameObject : Object
    {
    
    private:
        bool m_enabled;
        std::string m_name;

        std::vector<Component> components;
        Scene* m_scene = nullptr;

        void CoreInit()
        {
            //Run awake for all components
            for (auto c : components)
            {
                c->Awake();
            }
            //Run start for all components that are enabled
        }

        void CoreUpdate()
        {
            //Run fixed update for all components
            for (auto c : components)
            {
                c->FixedUpdate();
            }
            //Run update for all components
            for (auto c : components)
            {
                c->Update();
            }
            //Run late update for all components MAYBE?
            for (auto c : components)
            {
                c->LateUpdate();
            }
        }

    public:
        GameObject()
        {
            addComponent(new Transform());
        }

        void addedToScene(const Scene& scene)
        {
            m_scene = scene;
        }

        void addComponent(const Component& component)
        {
            components.push_back(component);
            component.addedToGameObject(this);
        }



        void update()
        {
            //Run update on all components

        }

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

        //Properties
        void setEnabled(bool setting) { m_enabled = setting; }
        bool isEnabled() const { return m_enabled; }
    };

    /////////
    class World
    {
        std::vector<GameObject> gameObjects;
        EventDispatcher* m_eventDispatcher;
        WorldRenderer* m_worldRenderer;
    };


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
    
    /////// /Componenets
    class Component
    {
        virtual void ComponentInit() {}
        virtual void ComponentUpdate() {}
        virtual void ComponentEnd() {}
    };

    class Transform : Component
    {
        //All GameObjects must have one of these. Cannot be removed (ideally)
    public:
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
    };

    class Rigidbody2D : Component; class Rigidbody : Component;
    class Collider2D : Component; class Collider : Component;
    class Camera : Component;
    class Light : Component;
    class Renderer : Component;
    class Animation : Component;     //Maybe


    //// Behaviours
    class Behaviour : Component
    {
        //Behaviours are essentially the scripts. Derive from Behaviour to create a "script"
    public:
        bool enabled;
        //Other members related only to with scripts

        // void Update() override {} //?

    };

    #include "scripts/MyCustomScript.h"
    class MyCustomScript : Behaviour
    {
        void Start() override;
        void Update() override;
        void End() override;
    };

}
}

#include "Minity.h"

using namespace MinityEngine;

namespace MyProject
{


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