#pragma once
#include <vector>
#include <iostream>

class Texture
{
private:
	unsigned int texName;
	unsigned char* data;

public:

	Texture();

	Texture(unsigned int _texName);

	void LoadTexture(const char* _path);

	unsigned int loadCubemap(std::vector<std::string> faces);

	unsigned int GetTextureName();

	void Bind();
};