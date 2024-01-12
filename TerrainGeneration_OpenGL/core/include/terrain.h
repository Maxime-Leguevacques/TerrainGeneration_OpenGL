#pragma once

#include <vector>
#include "Float/float3.hpp"



class Terrain {
private:
	int width, height, nChannel;
	unsigned char* heightmap;

public:
	std::vector<float> vertices;
	std::vector<int> indices;
	int rows, cols;

public:
	Terrain();
	~Terrain();

	Terrain(const char* _imagePath);

	void SetHeightmap(const char* _imagePath);
	void GenerateVertexData(float _heightmapSizeMult, float _verticesSeperationDist = 0.1f);
	void GenerateIndexData();
};