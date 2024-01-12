#pragma once

#include <vector>
#include "Float/float3.hpp"



class Terrain {
public:
	int width, height, nChannel;
	int rows, cols;
	unsigned char* heightmap;
	std::vector<float> vertices;
	std::vector<int> indices;


public:
	Terrain();
	~Terrain();

	Terrain(const char* _imagePath);

	void SetHeightmap(const char* _imagePath);
	void Draw();
	void GenerateVertexData(float _heightmapSizeMult, float _verticesSeperationDist = 0.1f);
	void GenerateIndexData();
};