#include "Serializer.h"

namespace Saddle {

    static void Serializer::saveScene(Scene* scene) {
        ofstream file(scene->getName() + ".sdlscene");
        file.open();
        for(Object* object : scene->getObjects()) {
            file << object->serialize();
        }
        file.close();
    }

}