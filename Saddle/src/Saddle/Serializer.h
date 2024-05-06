#pragma once

#include <fstream>

#include "Scenes/Scene.h"

namespace Saddle {
    class Scene;
    class SDL_API Serializer {
    public:

        static void saveScene(Scene* scene) {
            std::ofstream file(scene->getName() + ".sdlscene");
            for (int i = 0; i < scene->getObjects().size(); i++) {
                file << scene->serialize();
            }
            file.close();
        }

    };

}