#pragma once

#include "../SaddleApi.h"
#include "../Logging/Logger.h"

#include <vector>

namespace Saddle {
    class Object;

    /**
     * \brief Saddle Scene class. Saddle scenes contain and are responsible for
     * objects inside of it.
     * 
     * \extends Loggable Can be converted to a string and passed into a logger
     * loggable.
    */
    class SDL_API Scene : public Loggable {
    public:
        ~Scene();

        /**
         * \brief Creates and adds an object to the scene with a default name.
         * 
         * \return A reference to the object created.
        */
        Object& addObject() { return addObject("Object (" + m_sceneObjects->size()); }

        /**
         * \brief Creates and adds an object to the scene.
         * 
         * \param name The name of the to be created. 
         * 
         * \return A reference to the object created.
        */
        Object& addObject(std::string name);

        /**
         * \brief
        */
        static Scene& createScene() { return createScene("Scene"); }

        /**
         * \brief
        */
        static Scene& createScene(std::string name);


        /**
         * \return A reference to the active scene at the time of calling. The
         * active scene is the scene being rendered and processed.
        */
        static Scene& getActiveScene() { return *m_activeScene; }

        /**
         * \param scene A reference to a scene that is to be made active. An
         * active scene is a scene that is rendered and processed. If a scene
         * is created and there is currently no active scene, it will
         * automatically be made active.
        */
        static void setActiveScene(Scene& scene) { m_activeScene = &scene; }


        /**
         * \return A const reference to the objects contained by the scene at
         * the time of calling.
        */
        const std::vector<Object*>& getObjects() const { return *m_sceneObjects; }

        /**
         * \return A reference to the objects contained by the scene at the
         * time of calling.
        */
        std::vector<Object*>& getObjects() { return *m_sceneObjects; }


        /**
         * \return The name of the scene.
        */
        std::string getName() const { return m_name; }

        std::string toString(int indents) const override;

    private:

        Scene() : Scene("Scene" /*numscenes*/) {}
        Scene(std::string name);

        std::string m_name;

        static Scene* m_activeScene;

        std::vector<Object*> *m_sceneObjects;
    };
}