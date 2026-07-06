#include "VertexArray.h"

#include "VertexBufferLayout.h"

VtxArray::VtxArray()
{
    GLCALL(glGenVertexArrays(1, &rendererID_));
}

VtxArray::~VtxArray()
{
    GLCALL(glDeleteVertexArrays(1, &rendererID_));
}

void VtxArray::Bind() const
{
    GLCALL(glBindVertexArray(rendererID_));
}

void VtxArray::Unbind() const
{
    GLCALL(glBindVertexArray(0));
}

void VtxArray::ConfigVtxLayout(const VtxBuffer& vb, const VtxBufferLayout& layout)
{
    this->Bind();
    vb.Bind();
    const auto& elements = layout.GetElements();

    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); ++i) {
        const auto& element = elements[i];
        GLCALL(glEnableVertexAttribArray(i));
        GLCALL(glVertexAttribPointer(i, element.count, element.type, element.normalize,
                                     layout.GetStride(), (const void*) offset));
        offset += element.count * VtxBufferLayout_Elem::GetSizeOfType(element.type);
    }
}
