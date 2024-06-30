#pragma once

#include "../SaddleApi.h"

namespace Saddle {

    class SDL_API VertexBuffer {
    public:

        virtual ~VertexBuffer() {}

        virtual void bind() = 0;

        static VertexBuffer* createVertexBuffer(float *values, int length);

        float* getValues() { return values; }
        int getLength() { return length; }
        int getStride() { return stride; }

    protected:

        VertexBuffer(float* values, int length) : values(values), length(length), stride(3 * sizeof(float)) {}

    private:

        float* values;
        int length;

        int stride;

    };

}