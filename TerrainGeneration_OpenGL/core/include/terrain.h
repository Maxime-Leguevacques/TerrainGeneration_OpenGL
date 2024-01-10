#pragma once

#include <vector>
#include "Float/float3.hpp"



class Terrain {
private:
	int width, height, nChannel;
	std::vector<float3> vertices;
	std::vector<int> indices;

private:
	void GenerateVertexData(const char* _imagePath);
	void GenerateVertexData2(const char* _imagePath);
	void GenerateIndexData();

public:
	Terrain();
	~Terrain();

	Terrain(const char* _imagePath);

	void Draw();
};