#pragma once

#include <cstdint>
#include <cmath>
#include <glm/vec3.hpp>

#include "CIE.hpp"
#include "CameraDefs.hpp"
#include "ColorSpaces.hpp"

class Spectrum
{
public:
	Spectrum(uint8_t _sampleCount = 16)
	{
		sampleCount = _sampleCount;
		samples = new float[sampleCount];
		for (uint8_t i = 0; i < sampleCount; i++)
			samples[i] = 0;
	}

	~Spectrum()
	{
		if (samples)
			delete[] samples;
	}

	float& getSample(uint8_t sample)
	{
		return samples[sample % sampleCount];
	}

	float getPower(float lambda)	// nm
	{
		if (lambda < 380)
			return 0;
		if (lambda >= 700)
			return 0;

		float sample = float(sampleCount - 1) * float(lambda - 380) / float(700 - 380);
		uint8_t lowerSample = uint8_t(sample);
		uint8_t higherSample = lowerSample + 1;

		float a = getSample(lowerSample),
			  b = getSample(higherSample);
		float t = sample - floor(sample);

		return std::lerp(a, b, t);
	}

	glm::vec3 toRGB(CameraType cam)
	{
		if(cam == Eye)
		{
			glm::vec3 xyz(0);
			//for (uint16_t i = 380; i < 700; i++)
			for (uint16_t i = 380; i < 700; i += (700 - 380) / sampleCount)
			{
				// float dx = 1;
				float power = getPower(i);
				xyz += glm::vec3(power * CIE_1931_X(i),
					power * CIE_1931_Y(i),
					power * CIE_1931_Z(i));
			}
			return XYZ_To_RGB(xyz / CIE_Y_Integral);
		}

		return glm::vec3(0);
	}

private:
	uint8_t sampleCount;
	float* samples;
};