#pragma once

#include <SaddleApi.h>
#include "Objects/Component.h"

namespace Saddle {

    class Component;
    class SDL_API EventDispatcher {
    private:

        EventDispatcher() {}

        static EventDispatcher* dispatcher;

    public:

        static EventDispatcher& getMainDispatcher() { return *dispatcher; }

        void dispatchPreRender();

        void dispatchCreated(Component* component);
        void dispatchStart();
        void dispatchUpdate(double delta);

    };

    

}