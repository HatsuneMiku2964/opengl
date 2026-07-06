#pragma once

#include <string>
#include <sstream>
#include <unordered_map>

struct ShaderSrcContainer
{
    std::string VtxSrc;
    std::string FrgmSrc;
};

class Shader
{
public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    // SUGGEST: change these four floats into a vec4
    void SetUniform1f(const std::string& name, float value);
    void SetUniform1i(const std::string& name, int value);
    void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
private:
    int GetUniformLoc(const std::string& name);

    ShaderSrcContainer ParseShader(const std::string& path);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vtxShader, const std::string& frgmShader);

private:
    std::string filepath_;
    unsigned int rendererid_;
    std::unordered_map<std::string, int> unif_loc_cache_;
};