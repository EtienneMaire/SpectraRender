#pragma once

#include "Image.hpp"
#include "Spectrum.hpp"
#include "Triangle.hpp"
#include "Scene.hpp"
#include "Path.hpp"

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

	void Render(Scene scene, uint8_t maxBounces, uint16_t samples)
	{
		float AR = render.width / float(render.height);
		float focal = 60 * mm;
		glm::vec3 camPos(0);

#pragma omp parallel for
		for (int16_t i = 0; i < render.height; i++)
		{
			for (uint16_t j = 0; j < render.width; j++)
			{
				float u = j / float(render.width);
				float v = i / float(render.height);
				glm::vec3 rayDir((u - 0.5f) * AR, (v - 0.5f), -focal);
				rayDir = normalize(rayDir);

				Spectrum color(0.f, 32);
				Path path;
				for (uint16_t k = 0; k < samples; k++)
				{
					path.create(scene, maxBounces, camPos, rayDir);
					Spectrum s = path.evaluate();
					for (uint8_t l = 0; l < 32; l++)
						color.setSample(l, color.getSample(l) + s.getSample(l));
				}
				/*for (uint8_t l = 0; l < 32; l++)
					color.setSample(l, color.getSample(l) / samples);*/
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