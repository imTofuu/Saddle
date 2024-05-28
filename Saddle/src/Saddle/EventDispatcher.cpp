#include "EventDispatcher.h"
#include "Objects/Component.h"

namespace Saddle {

    EventDispatcher* EventDispatcher::dispatcher = new EventDispatcher();

    void EventDispatcher::dispatchPreRender() {
        for(auto * component : *(Component::m_components)) {
            component->preRender();
        }
    }

    void EventDispatcher::dispatchCreated(Component* component) {
        component->created();
    }

    void EventDispatcher::dispatchStart() {
        for(auto * component : *(Component::m_components)) {
            component->start();
        }
    }

    void EventDispatcher::dispatchUpdate(double delta) {
        for(auto * component : *(Component::m_components)) {
            component->update(delta);
        }
    }
}
