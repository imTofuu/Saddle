#include "ExposedValueComponent.h"

namespace Saddle {

    std::string ExposedValueComponent::serialize() const {
        std::string str;
        for(auto& pair : values) {

            str += pair.first + ":" + reinterpret_cast<char*>(pair.second) + "\\";

        }
    }

    void ExposedValueComponent::deserialize(std::unordered_map<std::string, void*> values) {
        this->values = values;
    }

}