#include "Scene.h"
#include "../Objects/Object.h"

namespace Saddle {

    Scene* Scene::m_activeScene = nullptr;
    std::vector<Scene*> Scene::m_scenes = std::vector<Scene*>();

    Scene::Scene(std::string name) {
        this->m_name = name;

        if (!m_activeScene) setActiveScene(this);
    }

    Scene::~Scene() {
        for(auto & object : m_sceneObjects.get()) {
            delete & object;
        }
    }

    Object& Scene::addObject(std::string name) {
        Object* object = new Object(name, *this);
        m_sceneObjects.add(object);

        return *object;
    }

    Scene& Scene::createScene(std::string name) {
        Scene* scene = new Scene(name);
        m_scenes.push_back(scene);
        return *scene;
    }

    std::string Scene::toString(int indents) const {
        std::string str = std::string(indents, '    ') += getName();
        for (int i = 0; i < m_sceneObjects.size(); i++) {
            if (i == 0) str += ":\n";
            const Object& object = m_sceneObjects[i];
            str += object.toString(indents + 1);
            if (i == m_sceneObjects.size() - 1) str += "\n";
        }
        return str;
    }
}