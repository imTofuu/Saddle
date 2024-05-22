#include "EventDispatcher.h"

#include "Objects/Component.h"

SADDLE {

    static void EventDispatcher::dispatchPreRender() {
        for(auto * component : Component::m_components) {
            component->preRender();
        }
    }

    static void EventDispatcher::dispatchCreated(Component& component) {
        component->created();
    }

    static void EventDispatcher::dispatchStart() {
        for(auto * component : Component::m_components) {
            component->start();
        }
    }

    static void EventDispatcher::dispatchUpdate(double delta) {
        for(auto * component : Component::m_components) {
            component->update(delta);
        }
    }

}