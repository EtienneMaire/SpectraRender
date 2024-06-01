#pragma once

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include "Material.hpp"

class Triangle
{
public:
	Triangle() : mat(&defaultMat)
	{
		a = b = c = glm::vec3(0);
	}

	Triangle(glm::vec3 _a, glm::vec3 _b, glm::vec3 _c, Material* _mat = &defaultMat)
	{
		a = _a;
		b = _b;
		c = _c;
		mat = _mat;
	}

	bool intersect(glm::vec3 rayOrigin, glm::vec3 rayDirection, 
		float& t, glm::vec3& X, glm::vec3& N);

public:
	glm::vec3 a, b, c;
	Material* mat;
};