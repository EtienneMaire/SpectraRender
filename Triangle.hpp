#pragma once

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

class Triangle
{
public:
	Triangle()
	{
		a = b = c = glm::vec3(0);
	}

	Triangle(glm::vec3 _a, glm::vec3 _b, glm::vec3 _c)
	{
		a = _a;
		b = _b;
		c = _c;
	}

	bool intersection(glm::vec3 rayOrigin, glm::vec3 rayDirection, 
		float& t, glm::vec3& X);

public:
	glm::vec3 a, b, c;
};