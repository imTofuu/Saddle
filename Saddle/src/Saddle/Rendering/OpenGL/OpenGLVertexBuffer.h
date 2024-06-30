#pragma once

#include "../../SaddleApi.h"
#include "../VertexBuffer.h"

namespace Saddle {

    class VertexBuffer;
    class SDL_API OpenGLVertexBuffer : public VertexBuffer {
    public:

        OpenGLVertexBuffer(float* values, int length);

        void bind() override;

    private:

        unsigned int vbo;

    };

}