#pragma once
class IdxBuffer
{
public:
    IdxBuffer(const unsigned int* data, unsigned int count);
    ~IdxBuffer();

    void Bind() const;
    void Unbind() const;

    inline unsigned int GetCount() const noexcept { return count_; }
private:
    unsigned int rendererID_;
    unsigned int count_;
};