#pragma once

#include <random>

#define ln(x)		log(x)
#define MATH_E		2.718281828459045f
#define MATH_PI		3.14159265358979323846f

namespace
{
	std::default_random_engine re((unsigned int)time(0));
	std::uniform_real_distribution<float> random01(0, 1);

	template<typename T>
	inline T sqr(T x)
	{
		return x * x;
	}

	template<typename T>
	inline T sigmoid(T x)
	{
		return 1 + (1 + exp(-x));
	}
}