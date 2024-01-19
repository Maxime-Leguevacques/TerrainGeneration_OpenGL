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
	heightmap = stbi_load(_imagePath, &width, &height, &nChannel, STBI_grey);
}

void Terrain::GenerateVertexData(float _heightmapSizeMult, float _verticesSeperationDist)
{
	int bytePerPixel = 1;

	// Load the heightmap and store its dimensions
	std::cout << "heightmap dimensions : " << width << " " << height << std::endl;
	rows = width, cols = height;
	rows *= _heightmapSizeMult;
	cols *= _heightmapSizeMult;

	// Initialize a grid of vertices using the heightmap's dimensions
	float z = -50;			// offset for z to see it in scene
	// Make grid
	for (int i = 0; i < rows; i++) {
		float x = -30;		// initialize the start position of a vertex' x 
		for (int j = 0; j < cols; j++) {
			unsigned char heightMapValue = (heightmap + (i + width * j) * bytePerPixel)[0];
			t_Vertex vertex;
			vertex.pos.x = x + i * 60.0f / width;
			vertex.pos.z = z + j * 60.0f / height;
			vertex.pos.y = heightMapValue / 255.0f * 5;
			vertex.texturePos.x = (1.0f / cols * j);
			vertex.texturePos.y = (1 - i * 1.0f / rows);
			vertices.push_back(vertex);
		}
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