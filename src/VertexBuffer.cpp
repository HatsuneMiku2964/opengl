#include "VertexBuffer.h"

#include "Renderer.h"

VtxBuffer::VtxBuffer(const void* data, unsigned int size)
{
    GLCALL(glGenBuffers(1, &rendererID_));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, rendererID_));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VtxBuffer::~VtxBuffer()
{
    Unbind();
    GLCALL(glDeleteBuffers(1, &rendererID_));
}

void VtxBuffer::Bind() const
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, rendererID_));
}

void VtxBuffer::Unbind() const
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
