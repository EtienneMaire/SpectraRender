#pragma once

#include "Triangle.hpp"
#include <vector>

class Mesh
{
public:
	Mesh()
	{

	}

	void deleteData()
	{
		data.clear();
	}

	void addTriangle(Triangle tri)
	{
		data.push_back(tri);
	}

	bool intersect(glm::vec3 rayOrigin, glm::vec3 rayDirection,
	float& t, glm::vec3& X, glm::vec3& N, Material*& mat)
	{
		bool intersection = false;
		t = 0;
		for (uint64_t i = 0; i < data.size(); i++)
		{
			float _t;
			glm::vec3 _X, _N;
			if (data[i].intersect(rayOrigin, rayDirection, _t, _X, _N))
			{
				if (_t < t || intersection == false)
				{
					intersection = true;
					t = _t;
					X = _X;
					N = _N;
					mat = data[i].mat;
				}
			}
		}
		return intersection;
	}

	~Mesh()
	{
		data = std::vector<Triangle>();
	}

private:
    std::vector<Triangle> data;
};