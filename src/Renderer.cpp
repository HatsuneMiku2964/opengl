#include "Renderer.h"

#include <iostream>

void GLClearErrors() { while (glGetError() != GL_NO_ERROR); }

bool GLLogCall(const char* file, const char* func, int line)
{
    while (GLenum error = glGetError()) {
        std::cout << "OpenGL error (" << error << ") :\nfile \""
            << file << "\" \nin function \"" << func << "\"" << ": line " << line;
        return false;
    }	return true;
}

void Renderer::Clear() const
{
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VtxArray& vao, const IdxBuffer& ibo, const Shader& shader) const
{
    vao.Bind();
    shader.Bind();
    GLCALL(glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr));

}
