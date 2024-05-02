#pragma once

#include <fstream>
#include "Serializable.h"

#include "./Scenes/Scene.h"

namespace Saddle {

    class Serializer {
        public:

        std::string serialize(const Scene& scene) const {
            std::ofstream file(scene.getName() + ".sdlscene");
            for(int i = 0; i < scene.getObjects().size(); i++) {
                file << scene.getObjects()[i].serialize();
            }
        }

    }

}