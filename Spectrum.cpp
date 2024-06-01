#include "Spectrum.hpp"
#include "SpectrumDefs.hpp"

#include <iostream>

void Spectrum::fromRGB(glm::vec3 rgb)
{
	float R = rgb.x, G = rgb.y, B = rgb.z;
	for (uint8_t i = 0; i < sampleCount; i++)
	{
		float val = 0;
		float lambda = float(i) * (LAMBDA_MAX - LAMBDA_MIN) / float(sampleCount) + LAMBDA_MIN;
		if (R <= G && R <= B)
		{
			val += R * whiteSpectrum.getPower(lambda);
			if (G <= B)
			{
				val += (G - R) * cyanSpectrum.getPower(lambda);
				val += (B - G) * blueSpectrum.getPower(lambda);
			}
			else
			{
				val += (B - R) * cyanSpectrum.getPower(lambda);
				val += (G - B) * greenSpectrum.getPower(lambda);
			}
		}
		else if (G <= R && G <= B)
		{
			val += G * whiteSpectrum.getPower(lambda);
			if (R <= B)
			{
				val += (R - G) * magentaSpectrum.getPower(lambda);
				val += (B - R) * blueSpectrum.getPower(lambda);
			}
			else
			{
				val += (B - G) * magentaSpectrum.getPower(lambda);
				val += (R - B) * redSpectrum.getPower(lambda);
			}
		}
		else // B <= R && B <= G
		{
			val += B * whiteSpectrum.getPower(lambda);
			if (R <= G)
			{
				val += (R - B) * yellowSpectrum.getPower(lambda);
				val += (G - R) * greenSpectrum.getPower(lambda);
			}
			else
			{
				val += (G - B) * yellowSpectrum.getPower(lambda);
				val += (R - G) * redSpectrum.getPower(lambda);
			}
		}

		val = std::max(std::min(val, 1.f), 0.f);

		setSample(i, val);
	}
}