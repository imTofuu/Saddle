#include "Scene.h"

namespace Saddle {

    Scene* Scene::m_activeScene = nullptr;

    Scene::Scene(std::string name) {
        this->m_name = name;
        this->m_sceneObjects = new std::vector<Object*>();

        if (!m_activeScene) setActiveScene(*this);
    }

    Scene::~Scene() {
        Serializer::saveScene(this);
        for(auto* object : *m_sceneObjects) {
            delete object;
        }
        delete m_sceneObjects;
    }

    Object& Scene::addObject(std::string name) {
        Object* object = new Object(name);
        m_sceneObjects->push_back(object);
        return *object;
    }

    std::string Scene::toString(int indents) const {
        std::string str = std::string(indents, '    ') += getName();
        for (int i = 0; i < m_sceneObjects->size(); i++) {
            if (i == 0) str += ":\n";
            Object* object = (*m_sceneObjects)[i];
            str += object->toString(indents + 1);
            if (i == m_sceneObjects->size() - 1) str += "\n";
        }
        return str;
    }

    std::string Scene::serialize() const {
        std::string str = "<Scene=" + getName() + ">";
        for (Object* obj : *m_sceneObjects) {
            str += obj->serialize();
        }
        str += "</Scene>";
        return str;
    }
}