#include <stb_image.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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