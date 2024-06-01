#pragma once

#include <glm/vec3.hpp>

class Material
{
public:

	Material(glm::vec3 _albedo = glm::vec3(0.8f), 
		float _roughness = 0.8f, bool _metallic = false)
	{
		albedo = _albedo;
		roughness = _roughness;
		metallic = _metallic;
	}

public:
	glm::vec3 albedo;	/* Saved as an RGB value bc
	a full spectrum would use too much memory*/
	float roughness;	// TODO: Add roughness map
	bool metallic;		// TODO: Add metallic map
};

namespace
{
	Material defaultMat;
}