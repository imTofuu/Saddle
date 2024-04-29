#pragma once

#include <SaddleApi.h>
#include <SaddleLogging.h>

#include <vector>

namespace Saddle {
    class Object;
    class SDL_API Scene : public Loggable {
    public:

        Scene() : Scene("Scene" /*numscenes*/) {}
        Scene(std::string name);

        ~Scene();

        Object& addObject() { addObject("Object (" + m_sceneObjects.size() + ")") }
        Object& addObject(std::string name)

        std::string toString() const override { return "Scene" }
        std::string getName() const { return m_name; }
    private:
        std::string m_name;

        std::vector<Object*> m_sceneObjects;
    }
}