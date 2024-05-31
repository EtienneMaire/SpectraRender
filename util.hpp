#pragma once

#define ln(x)		log(x)
#define MATH_E		2.718281828459045f
#define MATH_PI		3.14159265358979323846f

namespace
{
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