#pragma once

#include "VertexBuffer.h"

class VtxBufferLayout;

class VtxArray
{
public:
    VtxArray();
    ~VtxArray();

    void Bind() const;
    void Unbind() const;

    void ConfigVtxLayout(const VtxBuffer& vb, const VtxBufferLayout& layout);

private:
    unsigned int rendererID_;
};
