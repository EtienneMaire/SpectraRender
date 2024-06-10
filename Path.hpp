#pragma once

#include "Material.hpp"
//#include "util.hpp"
#include "Scene.hpp"
#include "Spectrum.hpp"

#include <glm/vec3.hpp>
#include <vector>

class Path
{
public:
	Path() {}

	void create(Scene scene, uint8_t length, glm::vec3 pos, glm::vec3 dir);
	Spectrum evaluate();

public:
	std::vector<PathNode> data;
};