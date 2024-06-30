#include "OpenGLVertexArray.h"

#include <glad/glad.h>
#include "../VertexBuffer.h"

namespace Saddle {

    OpenGLVertexArray::OpenGLVertexArray(VertexBuffer* buffers, int numBuffers) {
        glGenVertexArrays(1, &vao);

        glBindVertexArray(vao);

        for(int i = 0; i < numBuffers; i++) {
            buffers[i].bind();
            glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, buffers[i].getStride(), (void*)0);
            glEnableVertexAttribArray(i);
        }
    }

    void OpenGLVertexArray::bind() {

        glBindVertexArray(vao);

    }

}