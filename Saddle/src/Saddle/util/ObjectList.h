#pragma once

#include "../SaddleApi.h"

#include <vector>

namespace Saddle {

    template<class T>
    class SDL_API ObjectList {
    public:

        std::vector<T*> get() { return list; }
        std::vector<const T*> getConst() const { return constList; }

        void add(T* obj) { list.push_back(obj); constList.push_back(obj); }
        void remove(T* obj);
        void remove(int i);

        std::size_t size() const { return list.size(); }

        T& operator[](int i) { return *list[i]; }
        const T& operator[](int i) const { return *constList[i]; }

    private:
        std::vector<T*> list;
        std::vector<const T*> constList;
    };

}