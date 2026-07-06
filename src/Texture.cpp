#include "Texture.h"

#include "vendor/stb_image/stb_image.h"

Texture::Texture(const std::string& filepath)
    :filepath_(filepath), rendererid_(0),
    local_buffer_(nullptr), width_(0), height_(0), bpp_(0)
{
    stbi_set_flip_vertically_on_load(1);
    local_buffer_ = stbi_load(filepath.c_str(), &width_, &height_, &bpp_, 4);

    GLCALL(glGenTextures(1, &rendererid_));
    GLCALL(glBindTexture(GL_TEXTURE_2D, rendererid_));

    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_,
                        0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer_));
    GLCALL(glBindTexture(GL_TEXTURE_2D, 0)); // unbind

    if (local_buffer_) stbi_image_free(local_buffer_);
}
Texture::~Texture() { GLCALL(glDeleteTextures(1, &rendererid_)); }

void Texture::Bind(unsigned int slot) const
{
    GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
    GLCALL(glBindTexture(GL_TEXTURE_2D, rendererid_));
}
void Texture::Unbind() const
{
    GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}
