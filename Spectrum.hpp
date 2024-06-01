#pragma once

#include <cstdint>
#include <cmath>
#include <glm/vec3.hpp>

#include "CIE.hpp"
#include "CameraDefs.hpp"
#include "ColorSpaces.hpp"

#define LAMBDA_MIN 380
#define LAMBDA_MAX 720

class Spectrum	// SPD
{
public:
	//Spectrum()
	//{
	//	samples = nullptr;
	//	sampleCount = 0;
	//}

	Spectrum(glm::vec3 rgb, uint8_t _sampleCount = 32)
	{
		sampleCount = _sampleCount;
		samples = new float[sampleCount];
		fromRGB(rgb);
	}

	Spectrum(uint8_t _sampleCount = 32)
	{
		sampleCount = _sampleCount;
		samples = new float[sampleCount];
		for (uint8_t i = 0; i < sampleCount; i++)
			samples[i] = 0;
	}

	Spectrum(float* data, uint8_t _sampleCount)
	{
		fromData(data, _sampleCount);
	}

	~Spectrum()
	{
		if (samples)
			delete[] samples;
	}

	void fromData(float* data, uint8_t _sampleCount)
	{
		if (samples)
			delete[] samples;

		sampleCount = _sampleCount;
		samples = new float[sampleCount];
		for (uint8_t i = 0; i < sampleCount; i++)
			samples[i] = data[i];
	}

	void fromXYZ(glm::vec3 xyz)
	{
		glm::vec3 rgb = XYZ_To_RGB(xyz);
		fromRGB(rgb);
	}

	void fromRGB(glm::vec3 rgb);

	inline uint8_t getSampleCount()
	{
		return sampleCount;
	}

	inline float& getSample(uint8_t sample)
	{
		return samples[sample % sampleCount];
	}

	inline void setSample(uint8_t sample, float val)
	{
		samples[sample % sampleCount] = val;
	}

	float getPower(float lambda)	// nm
	{
		if (!samples)
			return 0;

		if (lambda < LAMBDA_MIN)
			return 0;
		if (lambda >= LAMBDA_MAX)
			return 0;

		float sample = float(sampleCount - 1) * float(lambda - LAMBDA_MIN) / float(LAMBDA_MAX - LAMBDA_MIN);
		uint8_t lowerSample = uint8_t(sample);
		uint8_t higherSample = lowerSample + 1;

		//return getSample(lowerSample);

		float a = getSample(lowerSample),
			  b = getSample(higherSample);
		float t = sample - floor(sample);

		return std::lerp(a, b, t);
	}

	glm::vec3 toXYZ(CameraType cam)
	{
		if (!samples)
			return glm::vec3(0);

		if (cam == Eye)
		{
			glm::vec3 xyz(0);
			//for (uint16_t i = LAMBDA_MIN; i < LAMBDA_MAX; i++)
			for (uint16_t i = LAMBDA_MIN; i < LAMBDA_MAX; i += (LAMBDA_MAX - LAMBDA_MIN) / sampleCount)
			{
				float dx = (LAMBDA_MAX - LAMBDA_MIN) / (float)sampleCount;
				float power = getPower(i);
				xyz += glm::vec3(
					power * CIE_1931_X(i),
					power * CIE_1931_Y(i),
					power * CIE_1931_Z(i))
					* dx;
			}
			return xyz / CIE_Y_Integral;
		}

		return glm::vec3(0);
	}

	glm::vec3 toRGB(CameraType cam)
	{
		if (cam == Eye)
			return XYZ_To_RGB(toXYZ(Eye));

		return glm::vec3(0);
	}

private:
	uint8_t sampleCount;
	float* samples;
};

namespace
{
	Spectrum operator*(Spectrum s, float k)
	{
		for (uint8_t i = 0; i < s.getSampleCount(); i++)
			s.setSample(i, k * s.getSample(i));
		return s;
	}

	Spectrum operator*(float k, Spectrum s)
	{
		for (uint8_t i = 0; i < s.getSampleCount(); i++)
			s.setSample(i, k * s.getSample(i));
		return s;
	}

	Spectrum operator*(Spectrum s0, Spectrum s1)
	{
		if (s0.getSampleCount() == s1.getSampleCount())
		{
			for (uint8_t i = 0; i < s0.getSampleCount(); i++)
				s0.setSample(i, s0.getSample(i) * s1.getSample(i));
			return s0;
		}
		else if (s0.getSampleCount() > s1.getSampleCount())
		{
			for (uint8_t i = 0; i < s0.getSampleCount(); i++)
				s0.setSample(i, s0.getSample(i) * s1.getPower(i * (LAMBDA_MAX - LAMBDA_MIN) / float(s0.getSampleCount()) + LAMBDA_MIN));
			return s0;
		}
		else
		{
			for (uint8_t i = 0; i < s1.getSampleCount(); i++)
				s1.setSample(i, s1.getSample(i) * s0.getPower(i * (LAMBDA_MAX - LAMBDA_MIN) / float(s1.getSampleCount()) + LAMBDA_MIN));
			return s1;
		}
	}

	Spectrum operator+(Spectrum s0, Spectrum s1)
	{
		if (s0.getSampleCount() == s1.getSampleCount())
		{
			for (uint8_t i = 0; i < s0.getSampleCount(); i++)
				s0.setSample(i, s0.getSample(i) + s1.getSample(i));
			return s0;
		}
		else if (s0.getSampleCount() > s1.getSampleCount())
		{
			for (uint8_t i = 0; i < s0.getSampleCount(); i++)
				s0.setSample(i, s0.getSample(i) + s1.getPower(i * (LAMBDA_MAX - LAMBDA_MIN) / float(s0.getSampleCount()) + LAMBDA_MIN));
			return s0;
		}
		else
		{
			for (uint8_t i = 0; i < s1.getSampleCount(); i++)
				s1.setSample(i, s1.getSample(i) + s0.getPower(i * (LAMBDA_MAX - LAMBDA_MIN) / float(s1.getSampleCount()) + LAMBDA_MIN));
			return s1;
		}
	}
}