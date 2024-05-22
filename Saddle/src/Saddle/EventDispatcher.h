#pragma once

#include <SaddleApi.h>

SADDLE {

    class SDL_API EventDispatcher {
    private:

        EventDispatcher();

    public:

        static void dispatchPreRender();

        static void dispatchCreated(Component& component);
        static void dispatchStart();
        static void dispatchUpdate(double delta);

    }

}