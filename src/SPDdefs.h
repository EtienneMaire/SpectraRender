#pragma once

#define SPD_SAMPLE_COUNT    10
#define LAMBDA_MIN          380
#define LAMBDA_MAX          720

const real_t CIE_Y_Integral = 106.856895;

real_t CIE_1931_X(real_t λ)
{
	return  1.065 * exp(-0.5 * sqr((λ - 595.8) / 33.33)) +
			0.366 * exp(-0.5 * sqr((λ - 446.8) / 19.44));
}

real_t CIE_1931_Y(real_t λ)
{
	return 1.014 * exp(-0.5 * sqr((ln(λ) - ln(556.3)) / 0.075));
}

real_t CIE_1931_Z(real_t λ)
{
	return 1.839 * exp(-0.5 * sqr((ln(λ) - ln(449.8)) / 0.051));
}

real_t whiteSpectrumData[10] = 
{
    1.,
    1.,
    0.9999,
    0.9993,
    0.9992,
    0.9998,
    1.,
    1.,
    1.,
    1.
};

real_t cyanSpectrumData[10] = 
{
    0.971,
    0.9426,
    1.0007,
    1.0007,
    1.0007,
    1.0007,
    0.1564,
    0.,
    0.,
    0.
};

real_t magentaSpectrumData[10] = 
{
    1.,
    1.,
    0.9685,
    0.2229,
    0.,
    0.0458,
    0.8369,
    1.,
    1.,
    0.9959
};

real_t yellowSpectrumData[10] = 
{
    0.0001,
    0.,
    0.1088,
    0.6651,
    1.,
    1.,
    0.9996,
    0.9586,
    0.9685,
    0.984
};

real_t redSpectrumData[10] = 
{
    0.1012,
    0.0515,
    0.,
    0.,
    0.,
    0.,
    0.8325,
    1.0149,
    1.0149,
    1.0149
};

real_t greenSpectrumData[10] = 
{
    0.,
    0.,
    0.0273,
    0.7937,
    1.,
    0.9418,
    0.1719,
    0.,
    0.,
    0.0025
};

real_t blueSpectrumData[10] = 
{
    1.,
    1.,
    0.8916,
    0.3323,
    0.,
    0.,
    0.0003,
    0.0369,
    0.0483,
    0.0496
};