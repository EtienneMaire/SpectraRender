#pragma once

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include "Material.hpp"

class Triangle
{
public:
	Triangle() : mat(&defaultMat)
	{
		a = b = c = normal = glm::vec3(0);
		area = 0;
	}

	Triangle(glm::vec3 _a, glm::vec3 _b, glm::vec3 _c, Material* _mat = &defaultMat)
	{
		a = _a;
		b = _b;
		c = _c;
		mat = _mat;
		computeNormal();
		computeArea();
	}

	void computeNormal()
	{
		normal = normalize(cross(b - a, c - a));
	}

	void computeArea()
	{
		glm::vec3 AB = b - a, AC = c - a;
		float theta = acos(dot(AB, AC));
		area = 0.5f * sqrt(dot(AB, AB)) * sqrt(dot(AC, AC)) * sin(theta);
	}

	bool intersect(glm::vec3 rayOrigin, glm::vec3 rayDirection, 
		float& t, glm::vec3& X, glm::vec3& N);

public:
	glm::vec3 a, b, c;
	glm::vec3 normal;
	float area;
	Material* mat;
};