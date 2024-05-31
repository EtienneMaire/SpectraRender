#pragma once

#include "Image.hpp"
#include <string>
#include "Spectrum.hpp"
#include "SpectrumDefs.hpp"

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
		for (uint16_t i = 0; i < render.height; i++)
		{
			for (uint16_t j = 0; j < render.width; j++)
			{
				/*glm::vec3 rgb(j / (float)render.width, 
					i / (float)render.height, 0);
				render.setPixel(j, i, rgb);
				Spectrum color(rgb);
				render.setPixel(j, i, color.toRGB(Eye));*/
				render.setPixel(j, i, cyanSpectrum.toRGB(Eye));
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