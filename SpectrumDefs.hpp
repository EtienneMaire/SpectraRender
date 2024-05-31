#pragma once

#include "Spectrum.hpp"

namespace
{
	float whiteSpectrumData[10] = {
		1.f,
		1.f,
		0.9999f,
		0.9993f,
		0.9992f,
		0.9998f,
		1.f,
		1.f,
		1.f,
		1.f
	};

	float cyanSpectrumData[10] = {
		0.971f,
		0.9426f,
		1.0007f,
		1.0007f,
		1.0007f,
		1.0007f,
		0.1564f,
		0.f,
		0.f,
		0.f
	};

	float magentaSpectrumData[10] = {
		1.f,
		1.f,
		0.9685f,
		0.2229f,
		0.f,
		0.0458f,
		0.8369f,
		1.f,
		1.f,
		0.9959f
	};

	float yellowSpectrumData[10] = {
		0.0001f,
		0.f,
		0.1088f,
		0.6651f,
		1.f,
		1.f,
		0.9996f,
		0.9586f,
		0.9685f,
		0.984f
	};

	Spectrum whiteSpectrum, cyanSpectrum, magentaSpectrum, yellowSpectrum;

	void initSpectrums()
	{
		whiteSpectrum.fromData(&whiteSpectrumData[0], 10);
		cyanSpectrum.fromData(&cyanSpectrumData[0], 10);
		magentaSpectrum.fromData(&magentaSpectrumData[0], 10);
		yellowSpectrum.fromData(&yellowSpectrumData[0], 10);
	}
}