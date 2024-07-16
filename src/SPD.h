#pragma once

typedef struct SPD
{
    real_t samples[SPD_SAMPLE_COUNT];
} SPD;

typedef struct SPD_Mask
{
    bool samples[SPD_SAMPLE_COUNT];
    uint8_t sampleCount;
} SPD_Mask;

SPD_Mask SPD_Mask_Init()
{
    SPD_Mask mask;
    for(uint8_t i = 0; i < SPD_SAMPLE_COUNT; i++)
        mask.samples[i] = true;
    mask.sampleCount = SPD_SAMPLE_COUNT;
    return mask;
}

SPD whiteSpectrum, cyanSpectrum, magentaSpectrum, yellowSpectrum,
	redSpectrum, greenSpectrum, blueSpectrum;

SPD SPD_FromSamples(real_t* data, uint8_t nbSamples)
{
    SPD spd;
    if (nbSamples == SPD_SAMPLE_COUNT)
    {
        for(uint8_t i = 0; i < SPD_SAMPLE_COUNT; i++)
            spd.samples[i] = data[i];
    }
    else
    {
        uint8_t lastSample = 0xff;
        for(uint8_t i = 0; i < nbSamples; i++)
        {
            uint8_t sample = i * SPD_SAMPLE_COUNT / nbSamples;
            if(sample != lastSample)
                spd.samples[sample] = data[i];
        }
    }
    return spd;
}

real_t SPD_GetPower(SPD spd, real_t λ)
{
    if (λ < LAMBDA_MIN)
	    return 0;
    if (λ >= LAMBDA_MAX)
        return 0;

    real_t sample = ((real_t)SPD_SAMPLE_COUNT - 1) * (real_t)(λ - LAMBDA_MIN) / (real_t)(LAMBDA_MAX - LAMBDA_MIN);
    uint8_t lowerSample = (uint8_t)sample;
    uint8_t higherSample = lowerSample + 1;

    real_t a = spd.samples[lowerSample],
         b = spd.samples[higherSample];
    real_t t = sample - floor(sample);

    return lerp(a, b, t);
}

SPD SPD_FromRGB(vec3 rgb)
{
    SPD spd;
    real_t R = rgb.x, G = rgb.y, B = rgb.z;
	for (uint8_t i = 0; i < SPD_SAMPLE_COUNT; i++)
	{
		real_t val = 0;
		real_t λ = (real_t)i * (LAMBDA_MAX - LAMBDA_MIN) / ((real_t)SPD_SAMPLE_COUNT) + LAMBDA_MIN;
		if (R <= G && R <= B)
		{
			val += R * SPD_GetPower(whiteSpectrum, λ);
			if (G <= B)
			{
				val += (G - R) * SPD_GetPower(cyanSpectrum, λ);
				val += (B - G) * SPD_GetPower(blueSpectrum, λ);
			}
			else
			{
				val += (B - R) * SPD_GetPower(cyanSpectrum, λ);
				val += (G - B) * SPD_GetPower(greenSpectrum, λ);
			}
		}
		else if (G <= R && G <= B)
		{
			val += G * SPD_GetPower(whiteSpectrum, λ);
			if (R <= B)
			{
				val += (R - G) * SPD_GetPower(magentaSpectrum, λ);
				val += (B - R) * SPD_GetPower(blueSpectrum, λ);
			}
			else
			{
				val += (B - G) * SPD_GetPower(magentaSpectrum, λ);
				val += (R - B) * SPD_GetPower(redSpectrum, λ);
			}
		}
		else // B <= R && B <= G
		{
			val += B * SPD_GetPower(whiteSpectrum, λ);
			if (R <= G)
			{
				val += (R - B) * SPD_GetPower(yellowSpectrum, λ);
				val += (G - R) * SPD_GetPower(greenSpectrum, λ);
			}
			else
			{
				val += (G - B) * SPD_GetPower(yellowSpectrum, λ);
				val += (R - G) * SPD_GetPower(redSpectrum, λ);
			}
		}

		val = max(min(val, 1.), 0.);

        spd.samples[i] = val;
	}

    return spd;
}

void initSPDs()
{
    whiteSpectrum = SPD_FromSamples(&whiteSpectrumData[0], 10);
    cyanSpectrum = SPD_FromSamples(&cyanSpectrumData[0], 10);
    magentaSpectrum = SPD_FromSamples(&magentaSpectrumData[0], 10);
    yellowSpectrum = SPD_FromSamples(&yellowSpectrumData[0], 10);
    redSpectrum = SPD_FromSamples(&redSpectrumData[0], 10);
    greenSpectrum = SPD_FromSamples(&greenSpectrumData[0], 10);
    blueSpectrum = SPD_FromSamples(&blueSpectrumData[0], 10);
}

vec3 XYZ_FromSPD(SPD spd, CameraType cam)
{
    vec3 xyz = {0, 0, 0};
    if (cam == Human_Eye)
    {
        //for (uint16_t i = LAMBDA_MIN; i < LAMBDA_MAX; i++)
        for (uint16_t i = LAMBDA_MIN; i < LAMBDA_MAX; i += (LAMBDA_MAX - LAMBDA_MIN) / SPD_SAMPLE_COUNT)
        {
            real_t dx = (LAMBDA_MAX - LAMBDA_MIN) / (real_t)SPD_SAMPLE_COUNT;   // 1
            real_t power = SPD_GetPower(spd, i);
            vec3 CIE = {CIE_1931_X(i), CIE_1931_Y(i), CIE_1931_Z(i)};
            xyz = add_vec3(xyz, mul_vec3_k(CIE, power * dx));
        }
        return div_vec3_k(xyz, CIE_Y_Integral);
    }

    return xyz;
}

vec3 RGB_FromSPD(SPD spd, CameraType cam)
{
    return XYZ_To_RGB(XYZ_FromSPD(spd, cam));
}