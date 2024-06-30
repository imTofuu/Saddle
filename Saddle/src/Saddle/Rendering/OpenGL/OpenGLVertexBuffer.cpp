#include "OpenGLVertexBuffer.h"

#include <glad/glad.h>

namespace Saddle {

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* values, int length) : VertexBuffer(values, length) {

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_UNIFORM_BUFFER, vbo);
        glBufferData(GL_UNIFORM_BUFFER, getLength(), getValues(), GL_STATIC_DRAW);

    }

    void OpenGLVertexBuffer::bind() {

        glBindBuffer(GL_ARRAY_BUFFER, vbo);

    }

}