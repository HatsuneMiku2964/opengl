#pragma once

#include <GL/glew.h>
#include <vector>

#include "Renderer.h"

struct VtxBufferLayout_Elem
{
    unsigned int type;
    unsigned int count;
    unsigned char normalize;

    static unsigned int GetSizeOfType(const unsigned int type)
    {
        switch (type) {
        case GL_FLOAT:
            return sizeof(GLfloat); break;
        case GL_UNSIGNED_INT:
            return sizeof(GLuint); break;
        case GL_UNSIGNED_BYTE:
            return sizeof(GLbyte); break;
        default: break;
        }
        ASSERT(false);
        return 0;
    }
};

class VtxBufferLayout
{
public:
    VtxBufferLayout()
        : stride_(0)
    {
    }

    template<typename T>
    void Push(unsigned int c) { static_assert(false); }

    template<>
    void Push<float>(unsigned int c)
    {
        elements_.push_back({GL_FLOAT, c, GL_FALSE});
        stride_ += c * VtxBufferLayout_Elem::GetSizeOfType(GL_FLOAT);
    }

    template<>
    void Push<unsigned int>(unsigned int c)
    {
        elements_.push_back({GL_UNSIGNED_INT, c, GL_FALSE});
        stride_ += c * VtxBufferLayout_Elem::GetSizeOfType(GL_UNSIGNED_INT);
    }

    template<>
    void Push<unsigned char>(unsigned int c)
    {
        elements_.push_back({GL_UNSIGNED_BYTE, c, GL_TRUE});
        stride_ += c * VtxBufferLayout_Elem::GetSizeOfType(GL_UNSIGNED_BYTE);
    }

    inline unsigned int GetStride() const { return stride_; }
    inline const std::vector<VtxBufferLayout_Elem>& GetElements() const { return elements_; }
private:
    std::vector<VtxBufferLayout_Elem> elements_;
    unsigned int stride_;
};
