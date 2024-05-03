#include "Serializable.h"

namespace Saddle {

    std::string Serializable::serialize() const {
        std::string str;
        for(auto& pair : data) {
            str += pair.first;
        }
        return str;
    }

}