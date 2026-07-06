#pragma once

#include "Renderer.h"

class Texture
{
public:
    Texture(const std::string& filepath);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline unsigned int GetWidth() { return width_; }
    inline unsigned int GetHeight() { return height_; }

private:
    std::string filepath_;

    unsigned int rendererid_;
    unsigned char* local_buffer_;

    int width_, height_, bpp_;

};
