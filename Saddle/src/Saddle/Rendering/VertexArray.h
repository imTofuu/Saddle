#pragma once

#include "../SaddleApi.h"

namespace Saddle {

    class VertexBuffer;
    class SDL_API VertexArray {
    public:

        virtual ~VertexArray() = default;

        static VertexArray* createVertexArray(VertexBuffer* buffers, int numBuffers);

        virtual void bind() = 0;

    protected:

        VertexArray() {}

    };

}