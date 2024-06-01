#pragma once

#include "Image.hpp"
#include "Spectrum.hpp"
#include "Triangle.hpp"

#include <glm/vec3.hpp>
#include <glm/gtx/intersect.hpp>

#include <iostream>
#include <string>

class Renderer
{
public:
	Renderer(uint16_t width, uint16_t height)
	{
		render.create(width, height);
	}

	~Renderer()
	{

	}

	void Render()
	{
		float AR = render.width / float(render.height);
		float focal = 60 * mm;
		glm::vec3 camPos(0);

		for (uint16_t i = 0; i < render.height; i++)
		{
			for (uint16_t j = 0; j < render.width; j++)
			{
				float u = j / float(render.width);
				float v = i / float(render.height);
				glm::vec3 rayDir((u - 0.5f) * AR, (v - 0.5f), focal);
				rayDir = normalize(rayDir);

				Triangle T(
					glm::vec3(-1, -1, 1),
					glm::vec3(1, 1, 1),
					glm::vec3(1, -1, 1));

				glm::vec3 rgb(0);
				float t;
				glm::vec3 X;
				if (T.intersection(camPos, rayDir,
					t, X))
					rgb = glm::vec3(1);

				Spectrum color(rgb, 32);
				render.setPixel(j, i, color.toRGB(Eye));
			}
		}
	}

	void saveRender(std::string path)
	{
		render.saveToBMP(path);
	}

	void saveRender()
	{
		saveRender("out/render" + std::to_string(time(0)) + ".bmp");
	}

private:
	Image render;
};