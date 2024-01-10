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
	GenerateVertexData(_imagePath);
	GenerateIndexData();
}

void Terrain::GenerateVertexData(const char* _imagePath)
{
	unsigned char* image = stbi_load(_imagePath, &width, &height, &nChannel, 0);
	std::cout << "image width : " << width << " height : " << height << std::endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			float xpos = j / (float)width;
			float ypos = 0;
			float zpos = i / (float)height;
			vertices.push_back(float3(xpos, ypos, zpos));
		}
	}
}

void Terrain::GenerateVertexData2(const char* _imagePath)
{
	unsigned char* image = stbi_load(_imagePath, &width, &height, &nChannel, 0);
	std::cout << "image width : " << width << " height : " << height << std::endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			unsigned char r = image[(j + i * width) * 3 + 0];
			unsigned char g = image[(j + i * width) * 3 + 1];
			unsigned char b = image[(j + i * width) * 3 + 2];
			int gValue = (int)((r + g + b) / 3);
			float xpos = ((float)j / (float)(width - 1)) - 0.5f;
			float ypos = (float)gValue / (float)255;
			float zpos = ((float)i / (float)(height - 1)) - 0.5f;
			vertices.push_back(float3(xpos, ypos, zpos));
		}
	}
	//for (int i = 0; i < vertices.size(); i++) {
		//std::cout << vertices[i].x << " " << vertices[i].y << " " << vertices[i].z << std::endl;
	//}
}

void Terrain::GenerateIndexData() {
	for (int i = 0; i < height - 1; i++) {
		for (int j = 0; j < width - 1; j++) {
			int topLeftIndexNum = (int)(i * width + j);
			int topRightIndexNum = (int)(i * width + j + 1);
			int bottomLeftIndexNum = (int)((i + 1) * width + j);
			int bottomRightIndexNum = (int)((i + 1) * width + j + 1);

			// write out two triangles
			indices.push_back(topLeftIndexNum);
			indices.push_back(bottomLeftIndexNum);
			indices.push_back(topRightIndexNum);

			indices.push_back(topRightIndexNum);
			indices.push_back(bottomLeftIndexNum);
			indices.push_back(bottomRightIndexNum);
		}
	}
}

void Terrain::Draw()
{
	unsigned int terrainVAO, terrainVBO, terrainEBO;
	glGenBuffers(1, &terrainVAO);
	glBindVertexArray(terrainVAO);

	glGenBuffers(1, &terrainVBO);
	glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float3), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &terrainEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
}