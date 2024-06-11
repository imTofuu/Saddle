#pragma once

#include "../SaddleApi.h"

#include "Layer.h"

#include <list>

namespace Saddle {

    class SDL_API LayerManager {
    public:

        template<class T> static T& addLayer(int i, const PassedArgs* args);
        template<class T> static T& getLayer();

        static std::list<Layer*>& getLayers() { return m_layers; }

    private:

        static std::list<Layer*> m_layers;

    };

    template<class T>
    T& LayerManager::addLayer(int i, const PassedArgs* args) {
        auto iterator = m_layers->begin();
        advance(iterator, i);
        T* t = new T();
        m_layers->insert(iterator, t);
        t->onLayerAdded(args);
        return *t;
    }

    template<class T>
    T& LayerManager::getLayer() {
        for(auto * layer : m_layers) {
            if(dynamic_cast<T*>(layer) != 0) return *dynamic_cast<T*>(layer);
        }
        SDL_CORE_ASSERT(false, "LayerManager does not contain a layer of type T.");
    }

}