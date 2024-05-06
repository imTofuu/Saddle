#pragma once

#include <SaddleApi.h>
#include <SaddleLogging.h>
#include "./../Saddle/Objects/Object.h"

#include <SaddleSerializing.h>

#include <vector>

namespace Saddle {
    class Object;
    class Serializer;
    class SDL_API Scene : public Loggable, public Serializable {
    public:
        Scene() : Scene("Scene" /*numscenes*/) {}
        Scene(std::string name);

        ~Scene();

        Object& addObject() { return addObject("Object (" + m_sceneObjects->size()); }
        Object& addObject(std::string name);

        std::string toString(int indents) const override;
        std::string getName() const { return m_name; }

        static Scene& getActiveScene() { return *m_activeScene; }
        static void setActiveScene(Scene& scene) { m_activeScene = &scene; }

        const std::vector<Object*>& getObjects() const { return *m_sceneObjects; }
        std::vector<Object*>& getObjects() { return *m_sceneObjects; }

    private:

        friend class Serializer;

        std::string serialize() const override;
        void deserialize(std::unordered_map<std::string, void*> values) override {}

        std::string m_name;

        static Scene* m_activeScene;

        std::vector<Object*> *m_sceneObjects;
    };
}