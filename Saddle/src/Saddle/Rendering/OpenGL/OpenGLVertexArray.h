#pragma once

#include "../../SaddleApi.h"

#include "../VertexArray.h"

namespace Saddle {

    class SDL_API OpenGLVertexArray : public VertexArray {
    public:

        OpenGLVertexArray(VertexBuffer* buffers, int numBuffers);

        void bind() override;

    private:

        unsigned int vao;

    };

}