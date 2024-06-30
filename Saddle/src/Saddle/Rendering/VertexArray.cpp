#include "VertexArray.h"

#include <glad/glad.h>

#include "OpenGL/OpenGLVertexArray.h"

#include "VertexBuffer.h"

namespace Saddle {

    VertexArray* VertexArray::createVertexArray(VertexBuffer* buffers, int numBuffers) {
        return new OpenGLVertexArray(buffers, numBuffers);
    }
    
}