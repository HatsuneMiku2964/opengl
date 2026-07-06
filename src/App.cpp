#include <iostream>
#include <fstream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

int main()
{
    GLFWwindow* window;

    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window) { glfwTerminate(); return -1; }
    

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) return -1;

    GLCALL(glEnable(GL_BLEND));
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    float verticies[] = {
        -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,   0.f, 0.f, 
         0.5f, -0.5f,	0.0f, 1.0f, 0.0f,   1.f, 0.f,
         0.5f,  0.5f,	0.0f, 0.0f, 1.0f,   1.f, 1.f,
        -0.5f,  0.5f,	1.0f, 0.0f, 0.0f,   0.f, 1.f,
    };
    unsigned int indicies[] = {
        3, 2, 0, // index of first triangle
        2, 0, 1, // index of second triangle
    };

    VtxArray* vao = new VtxArray();
    VtxBuffer* vbo = new VtxBuffer(verticies, 4 * 7 * sizeof(float));
    VtxBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(3);
    layout.Push<float>(2);

    vao->ConfigVtxLayout(*vbo, layout);
    IdxBuffer* ibo = new IdxBuffer(indicies, 6);
    Shader shader("res/shaders/Basic.shader");
    shader.Bind();

    Texture texture("res/textures/images.png");
    texture.Bind();
    shader.SetUniform1i("u_texture", 0);

    vao->Unbind();
    vbo->Unbind();
    ibo->Unbind();
    shader.Unbind();

    Renderer renderer;

    while (!glfwWindowShouldClose(window)) {
        renderer.Clear();
        renderer.Draw(*vao, *ibo, shader);

        GLCALL(glfwSwapBuffers(window));
        GLCALL(glfwPollEvents());
    }

    delete vao;
    delete vbo;
    delete ibo;

    glfwTerminate();
    return 0;
}