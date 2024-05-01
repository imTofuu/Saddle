#pragma once

#include <SaddleApi.h>
#include <SaddleLogging.h>
#include "./../Saddle/Objects/Object.h"

#include <vector>

namespace Saddle {
    class Object;
    class SDL_API Scene : public Loggable {
    public:
        Scene() : Scene("Scene" /*numscenes*/) {}
        Scene(std::string name);

        ~Scene();

        Object& addObject() { return addObject("Object (" + m_sceneObjects->size()); }
        Object& addObject(std::string name);

        std::string toString(int indents) const override;
        std::string getName() const { return *m_name; }

        static Scene& getActiveScene() { return *m_activeScene; }
        static void setActiveScene(Scene& scene) { m_activeScene = &scene; }
    private:
        std::string *m_name;

        static Scene* m_activeScene;

        std::vector<Object*> *m_sceneObjects;
    };
}