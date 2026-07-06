#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCALL(x)	GLClearErrors ( );\
					x;\
					ASSERT(GLLogCall ( __FILE__, #x, __LINE__ ))

void GLClearErrors( );
bool GLLogCall(const char* file, const char* func, int line);

class Renderer
{
public:
	void Clear() const;
	void Draw(const VtxArray& vao, const IdxBuffer& ibo, const Shader& shader) const;
};