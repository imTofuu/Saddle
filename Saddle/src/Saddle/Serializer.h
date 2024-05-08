#pragma once

#include <fstream>
#include <iostream>

#include "Scenes/Scene.h"

namespace Saddle {
    class Scene;
    class SDL_API Serializer {
    public:

        /**
         * \param scene Saves the scene and everything it contains to a
         * .sdlscene file. Data is saved in a human readable and editable
         * format.
        */
        static void saveScene(Scene* scene);

    };

}