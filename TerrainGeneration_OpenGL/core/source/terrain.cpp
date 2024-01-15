#include <stb_image.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#include <gl/GLU.h>

#include "terrain.h"



Terrain::Terrain()
{

}

Terrain::~Terrain()
{

}

Terrain::Terrain(const char* _imagePath)
{
	heightmap = stbi_load(_imagePath, &width, &height, &nChannel, 0);
	GetVertexHeight(_imagePath, width, height);
}

void Terrain::SetHeightmap(const char* _imagePath)
{
	heightmap = stbi_load(_imagePath, &width, &height, &nChannel, 0);
}

void Terrain::GenerateVertexData(float _heightmapSizeMult, float _verticesSeperationDist)
{
	// Load the heightmap and store its dimensions
	std::cout << "heightmap dimensions : " << width << " " << height << std::endl;
	rows = width, cols = height;
	rows *= _heightmapSizeMult;
	cols *= _heightmapSizeMult;

	// Initialize a grid of vertices using the heightmap's dimensions
	float z = -50;			// offset for z to see it in scene
	// Make grid
	for (int i = 0; i < rows; i++) {
		float x = -5;		// initialize the start position of a vertex' x 
		for (int j = 0; j < cols; j++) {
			vertices.push_back(x);
			vertices.push_back(0);		// the y coordinate will be calculated in the shader
			vertices.push_back(z);
			// texture positions
			vertices.push_back(1.0f / cols * j);
			vertices.push_back(1 - i * 1.0f / rows);
			x += _verticesSeperationDist;
		}
		z += _verticesSeperationDist;
	}
}

void Terrain::GenerateIndexData() {
	// Indices positions
	for (int i = 1; i < rows; i++) {
		for (int j = 1; j < cols; j++) {
			indices.push_back((i - 1) * cols + j - 1);
			indices.push_back((i - 1) * cols + j);
			indices.push_back(i * cols + j - 1);

			indices.push_back(i * cols + j - 1);
			indices.push_back((i - 1) * cols + j);
			indices.push_back(i * cols + j);
		}
	}
}

void Terrain::GetVertexHeight(const char* _imagePath, float _heightmapSizeMult, float _verticesSeperationDist)
{
	// Load texture
	unsigned int textureID;
	int textureWidth, textureHeight;
	unsigned char* texturePixels = stbi_load(_imagePath, &textureWidth, &textureHeight, NULL, STBI_rgb_alpha);

	// Generate and bind texture
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Set parameters and allocate storage
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texturePixels);

	// Read pixel
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &textureWidth);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &textureHeight);
	
	for (int i = 0; i < textureWidth * textureHeight * 4; i += 4) {
		Pixel pixel;
		pixel.pos = float2(i / 4 % textureWidth, i / 4 / textureWidth);
		pixel.R = static_cast<int>(texturePixels[i]);
		pixel.G = static_cast<int>(texturePixels[i + 1]);
		pixel.B = static_cast<int>(texturePixels[i + 2]);
		pixel.A = static_cast<int>(texturePixels[i + 3]);
		pixels.push_back(pixel);
	}
	stbi_image_free(texturePixels);
}