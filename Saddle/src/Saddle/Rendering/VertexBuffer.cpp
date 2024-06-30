#include "VertexBuffer.h"

#include "OpenGL/OpenGLVertexBuffer.h"

namespace Saddle {

    VertexBuffer* VertexBuffer::createVertexBuffer(float* values, int length) {
        return new OpenGLVertexBuffer(values, length);
    }

}