#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "Mesh.hpp"

namespace
{
	struct PathNode
	{
		glm::vec3 X, N;
		Material* mat;
	};
}

class Scene
{
public:
    Scene() {}

    void loadFromOBJ(std::string path);
	bool intersect(glm::vec3 rayOrigin, glm::vec3 rayDirection,
		float& t, PathNode& node)
	{
		bool intersection = false;
		t = 0;
		for (uint64_t i = 0; i < objects.size(); i++)
		{
			float _t;
			glm::vec3 _X, _N;
			Material* _mat;
			if (objects[i].intersect(rayOrigin, rayDirection, _t, _X, _N, _mat))
			{
				if (_t < t || intersection == false)
				{
					intersection = true;
					t = _t;
					node.X = _X;
					node.N = _N;
					node.mat = _mat;
				}
			}
		}
		return intersection;
	}

public:
    std::vector<Mesh> objects;
    std::vector<Material> materials;
};