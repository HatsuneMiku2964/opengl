#pragma once
class VtxBuffer
{
public:
	VtxBuffer(const void* data, unsigned int size);
	~VtxBuffer( );

	void Bind( ) const;
	void Unbind( ) const;
private:
	unsigned int rendererID_;
};