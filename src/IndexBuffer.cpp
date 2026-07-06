#include "IndexBuffer.h"

#include "Renderer.h"

IdxBuffer::IdxBuffer(const unsigned int* data, unsigned int count)
    : count_(count)
{
    GLCALL(glGenBuffers(1, &rendererID_));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID_));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IdxBuffer::~IdxBuffer()
{
    this->Unbind();
    GLCALL(glDeleteBuffers(1, &rendererID_));
}

void IdxBuffer::Bind() const
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID_));
}

void IdxBuffer::Unbind() const
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
