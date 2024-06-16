#pragma once

#include "../SaddleApi.h"
#include "../PassedArgs.h"

#include <vector>

namespace Saddle {

    class SDL_API Layer {
    public:
        virtual ~Layer() = default;

        virtual void onLayerAdded() { onLayerAdded(0); }
        virtual void onLayerAdded(const PassedArgs* args) {}
        virtual void onLayerRemoved() { onLayerRemoved(0); }
        virtual void onLayerRemoved(const PassedArgs* args) {}

        virtual void onUpdate() { onUpdate(0); }
        virtual void onUpdate(const PassedArgs* args) {}
        virtual void onLateUpdate() { onLateUpdate(0); }
        virtual void onLateUpdate(const PassedArgs* args) {}

    };

}