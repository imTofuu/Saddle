#pragma once

#include <fstream>

#include "Scenes/Scene.h"

namespace Saddle {
    class Scene;
    class SDL_API Serializer {
    public:

        static void saveScene(Scene* scene);

    };

}