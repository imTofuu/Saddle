#include "Layer.h"

namespace Saddle {

    void Layer::onLayerAdded() { onLayerAdded(0); }
    void Layer::onLayerRemoved() { onLayerRemoved(0); }
    void Layer::onUpdate() { onUpdate(0); }
    void Layer::onLateUpdate() { onLateUpdate(0); }


}