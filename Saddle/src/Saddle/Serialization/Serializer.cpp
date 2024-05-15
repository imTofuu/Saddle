#include "Serializer.h"

#include <fstream>
#include <iostream>

namespace Saddle {

    void Serializer::saveScene(Scene* scene) {
        std::ofstream file;
        file.open(scene->getName() + ".sdlscene", std::ofstream::out);
        for(Object* object : scene->getObjects()) {
            object->serialize(file);
        }
        file.close();
    }

}