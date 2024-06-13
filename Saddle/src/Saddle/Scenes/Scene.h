#pragma once

#include "../SaddleApi.h"
#include "../Logging/Logger.h"
#include "../Logging/Loggable.h"

#include "../util/ObjectList.h"

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

        Object& addObject() { return addObject("Object (" + m_sceneObjects.size()); }
        Object& addObject(std::string name);

        static Scene& createScene() { return createScene("Scene"); }
        static Scene& createScene(std::string name);

        static Scene& getActiveScene() { return *m_activeScene; }
        static void setActiveScene(Scene* scene) { m_activeScene = scene; }

        const std::vector<Object&>& getObjects() { return m_sceneObjects.get(); }
        const std::vector<const Object&>& getObjects() const { return m_sceneObjects.getConst(); }

        static const std::vector<Scene&>& getAllScenes() { return m_scenes; }


        std::string getName() const { return m_name; }

        std::string toString(int indents) const override;

    private:

        Scene() : Scene("Scene" /*numscenes*/) {}
        Scene(std::string name);

        std::string m_name;

        static Scene* m_activeScene;
        static std::vector<Scene&> m_scenes;

        ObjectList<Object> m_sceneObjects;

    };
}