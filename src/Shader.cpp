#include "Shader.h"

#include <fstream>
#include <iostream>

#include "Renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

Shader::Shader(const std::string& filepath)
    : filepath_(filepath), rendererid_(0)
{
    ShaderSrcContainer src = ParseShader(filepath_);
    rendererid_ = CreateShader(src.VtxSrc, src.FrgmSrc);
}

Shader::~Shader() { GLCALL(glDeleteProgram(rendererid_)); }

void Shader::Bind() const { GLCALL(glUseProgram(rendererid_)); }
void Shader::Unbind() const { GLCALL(glUseProgram(0)); }

void Shader::SetUniform1f(const std::string& name, float value)
{
    GLCALL(glUniform1f(Shader::GetUniformLoc(name), value));
}
void Shader::SetUniform1i(const std::string& name, int value)
{
    GLCALL(glUniform1i(Shader::GetUniformLoc(name), value));
}
void Shader::SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3)
{
    GLCALL(glUniform4f(Shader::GetUniformLoc(name),
                       f0, f1, f2, f3));
}

int Shader::GetUniformLoc(const std::string& name)
{
    if (unif_loc_cache_.find(name) != unif_loc_cache_.end()) return unif_loc_cache_[name];

    GLCALL(int location = glGetUniformLocation(rendererid_, name.c_str()));
    unif_loc_cache_[name] = location;
    return location;
}

ShaderSrcContainer Shader::ParseShader(const std::string& path)
{
    std::ifstream stream(path);

    enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            } else return ShaderSrcContainer();
        } else {
            ss[(int) type] << line << "\n";
        }
    }
    ShaderSrcContainer src;
    src.FrgmSrc = ss[(int) ShaderType::FRAGMENT].str();
    src.VtxSrc = ss[(int) ShaderType::VERTEX].str();
    return src;
}
unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    GLCALL(glShaderSource(id, 1, &src, nullptr));
    GLCALL(glCompileShader(id));

    // handle errors
    {
        int result;
        GLCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
        if (!result) {
            int length;
            GLCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
            char* message = (char*) (malloc(length * sizeof(char)));
            GLCALL(glGetShaderInfoLog(id, length, &length, message));
            std::cout << "Falied to compile " <<
                (type == GL_VERTEX_SHADER ? "vertex" : "fragment") <<
                " shader:\n" << message << "\n";
            GLCALL(glDeleteShader(id));
            free(message);
            return 0;
        }
    }// ~handle errors

    return id;
}
unsigned int Shader::CreateShader(const std::string& vtxShader, const std::string& frgmShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vtxShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, frgmShader);

    GLCALL(glAttachShader(program, vs));
    GLCALL(glAttachShader(program, fs));
    GLCALL(glLinkProgram(program));
    GLCALL(glValidateProgram(program));

    GLCALL(glDeleteShader(vs));
    GLCALL(glDeleteShader(fs));

    return program;
}