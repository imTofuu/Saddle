#pragma once

#include <SaddleComponents.h>

#include <bits/stdc++.h>

namespace Saddle {

    class ExposedValueComponent : public Component {
    public:

        template<typename T> T* operator[](std::string index);

        std::string serialize() const override;
        void deserialize() override;

    private:


        std::unordered_map<std::string, void*> values;

    };

    template<typename T>
    T* ExposedValueComponent::operator[](std::string index) {
        if(values.find(index) == values.end()) values[index] = new T();
        return values[index];
    }

}