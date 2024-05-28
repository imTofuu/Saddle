#pragma once

#include "SaddleApi.h"
#include "../PassedArgs.h"

#include <vector>

namespace Saddle {

    class SDL_API Layer {
    public:
        virtual ~Layer() = default;

        virtual void onLayerAdded(const PassedArgs* args) {}
        virtual void onLayerRemoved(const PassedArgs* args) {}

        virtual void onUpdate(const PassedArgs* args) {}

    };

}