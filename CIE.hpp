#pragma once

#include <cmath>
#include "util.hpp"

namespace
{
	static constexpr float CIE_Y_Integral = 106.856895f;

	float CIE_1931_X(float lambda)
	{
		return  1.065f * exp(-0.5f * sqr((lambda - 595.8f) / 33.33f)) +
				0.366f * exp(-0.5f * sqr((lambda - 446.8f) / 19.44f));
	}

	float CIE_1931_Y(float lambda)
	{
		return 1.014f * exp(-0.5f * sqr((ln(lambda) - ln(556.3f)) / 0.075f));
	}

	float CIE_1931_Z(float lambda)
	{
		return 1.839f * exp(-0.5f * sqr((ln(lambda) - ln(449.8f)) / 0.051f));
	}
}