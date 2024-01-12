#pragma once
#include <vector>

class Texture
{
private:
	unsigned int texName;
	unsigned char* data;

public:

	Texture();

	Texture(unsigned int _texName);

	void LoadTexture(const char* _path);

	unsigned int GetTextureName();
};