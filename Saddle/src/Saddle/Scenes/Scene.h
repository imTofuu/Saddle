#pragma once

#include <SaddleApi.h>
#include <SaddleLogging.h>
#include "./../Saddle/Objects/Object.h"

#include <SaddleSerializing.h>

#include <vector>

namespace Saddle {
    class Object;
    class Serializer;

    /**
     * \brief Saddle Scene class. Saddle scenes contain and are responsible for
     * objects inside of it.
     * 
     * \extends Loggable Can be converted to a string and passed into a logger
     * loggable.
     * 
     * \extends Serializable Scenes are responsible for serializing themselves
     * when the project is saved. Serialized scenes are saved to a .sdlscene
     * file and are human readable and editable. .sdlscene files contains all
     * of the objects that the scene contains and all of its objects
     * components.
    */
    class SDL_API Scene : public Loggable, public Serializable {
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

        friend class Serializer;

        void serialize(std::ofstream& file) const override;
        void deserialize(std::unordered_map<std::string, void*> values) override {}

        std::string m_name;

        static Scene* m_activeScene;

        std::vector<Object*> *m_sceneObjects;
    };
}