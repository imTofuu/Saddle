#pragma once

#include "../SaddleApi.h"

#include "Layer.h"

#include <list>

namespace Saddle {

    class SDL_API LayerManager {
    public:

        template<class T> static T& addLayer(int i);
        template<class T> static T& getLayer();

        static std::list<Layer*>& getLayers() { return *m_layers; }

    private:

        static std::list<Layer*>* m_layers;

    };

    std::list<Layer*>* LayerManager::m_layers = new std::list<Layer*>();

    template<class T>
    T& LayerManager::addLayer(int i) {
        auto iterator = m_layers.begin();
        advance(iterator, i);
        T* t = new T()
        m_layers.insert(iterator, t);
        t->onLayerAdded();
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