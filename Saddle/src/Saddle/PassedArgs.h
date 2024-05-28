#pragma once

#include "SaddleApi.h"

#include <vector>

namespace Saddle {

    class SDL_API PassedArgs {
    public:

        void* operator[](int i) const { return m_args[i]; }
        void* operator[](int i);

        void next(void* val) { m_args.push_back(val); }

    private:

        std::vector<void*> m_args;

    };

}