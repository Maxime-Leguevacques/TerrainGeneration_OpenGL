#pragma once

#include <vector>
#include "Float/float3.hpp"
#include "Float/float2.hpp"


struct Pixel
{
	float2 pos;
	int R, G, B, A;
};


class Terrain {
private:
	int width, height, nChannel;
	unsigned char* heightmap;
	std::vector<Pixel> pixels;

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
	void GetVertexHeight(const char* _imagePath, float _heightmapSizeMult, float _verticesSeperationDist = 0.1f);
};