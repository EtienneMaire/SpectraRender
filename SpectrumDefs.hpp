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

	float redSpectrumData[10] = {
		0.1012f,
		0.0515f,
		0.f,
		0.f,
		0.f,
		0.f,
		0.8325f,
		1.0149f,
		1.0149f,
		1.0149f
	};

	float greenSpectrumData[10] = {
		0.f,
		0.f,
		0.0273f,
		0.7937f,
		1.f,
		0.9418f,
		0.1719f,
		0.f,
		0.f,
		0.0025f
	};

	float blueSpectrumData[10] = {
		1.f,
		1.f,
		0.8916f,
		0.3323f,
		0.f,
		0.f,
		0.0003f,
		0.0369f,
		0.0483f,
		0.0496f
	};

	Spectrum whiteSpectrum(&whiteSpectrumData[0], 10),
		cyanSpectrum(&cyanSpectrumData[0], 10),
		magentaSpectrum(&magentaSpectrumData[0], 10),
		yellowSpectrum(&yellowSpectrumData[0], 10),
		redSpectrum(&redSpectrumData[0], 10),
		greenSpectrum(&greenSpectrumData[0], 10),
		blueSpectrum(&blueSpectrumData[0], 10);

	//void initSpectrums()
	//{
	//	whiteSpectrum.fromData(&whiteSpectrumData[0], 10);

	//	cyanSpectrum.fromData(&cyanSpectrumData[0], 10);
	//	magentaSpectrum.fromData(&magentaSpectrumData[0], 10);
	//	yellowSpectrum.fromData(&yellowSpectrumData[0], 10);

	//	redSpectrum.fromData(&redSpectrumData[0], 10);
	//	greenSpectrum.fromData(&greenSpectrumData[0], 10);
	//	blueSpectrum.fromData(&blueSpectrumData[0], 10);
	//}
}