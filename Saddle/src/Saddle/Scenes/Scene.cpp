#include "Scene.h"

namespace Saddle {
    Scene::Scene(std::string name) {
        this->name = name;
    }

    Scene::~Scene() {
        for(auto* object : m_sceneObjects) {
            delete object;
        }
    }

    Object& Scene::addObject(std::string name) {
        Object* object = new Object(name);
        m_sceneObjects.push_back(object);
        return *object;
    }
}