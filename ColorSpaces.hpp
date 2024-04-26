#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <cmath>
#include <glm/mat3x3.hpp>

namespace
{
	enum ColorSpace
	{
		RGB,
		XYZ,
		xyY,
		sRGB
	};

	glm::mat3 RGB_To_XYZ_matrix(
		glm::vec3( 0.412390799265959, 0.357584339383878, 0.180480788401834 ),
		glm::vec3( 0.212639005871510, 0.715168678767756, 0.072192315360734 ),
		glm::vec3( 0.019330818715592, 0.119194779794626, 0.950532152249661 ));
	glm::mat3 XYZ_To_RGB_matrix(
		glm::vec3(3.240969941904523, -1.537383177570094, -0.498610760293003),
		glm::vec3(-0.969243636280880, 1.875967501507721, 0.041555057407176),
		glm::vec3(0.055630079696994, -0.203976958888977, 1.056971514242879));

	glm::vec3 XYZ_To_xyY(glm::vec3 xyz)
	{
		return glm::vec3(xyz.x / (xyz.x + xyz.y + xyz.z), xyz.y / (xyz.x + xyz.y + xyz.z), xyz.y);
	}

	glm::vec3 xyY_To_XYZ(glm::vec3 xyY)
	{
		return glm::vec3(xyY.x * xyY.y / xyY.z,	// xY/y
						 xyY.z, 				// Y
						(1 - xyY.x - xyY.y) * xyY.z / xyY.y);	// (1 - x - y)Y / y
	}

	glm::vec3 sRGB_To_RGB(glm::vec3 rgb)
	{
		return glm::vec3(std::pow(rgb.r, 1 / 2.2f),
			std::pow(rgb.g, 1 / 2.2f),
			std::pow(rgb.b, 1 / 2.2f));
	}

	glm::vec3 RGB_To_sRGB(glm::vec3 srgb)
	{
		return glm::vec3(std::pow(srgb.r, 2.2f),
			  			 std::pow(srgb.g, 2.2f),
						 std::pow(srgb.b, 2.2f));
	}

	glm::vec3 XYZ_To_RGB(glm::vec3 xyz)
	{
		return XYZ_To_RGB_matrix * xyz;
	}

	glm::vec3 RGB_To_XYZ(glm::vec3 rgb)
	{
		return RGB_To_XYZ_matrix * rgb;
	}

	glm::vec3 convertColorSpace(
	glm::vec3 color, ColorSpace colorSpaceIn, ColorSpace colorSpaceOut)
	{
		if (colorSpaceIn == colorSpaceOut) return color;

		glm::vec3 rgb(0);
		switch (colorSpaceIn)
		{
		case XYZ:
			rgb = XYZ_To_RGB(color);
			break;
		case xyY:
			rgb = XYZ_To_RGB(xyY_To_XYZ(color));// xyY_To_RGB(color);
			break;
		case RGB:
			rgb = color;
			break;
		case sRGB:
			rgb = sRGB_To_RGB(color);
			break;
		}

		switch (colorSpaceOut)
		{
		case XYZ:
			return RGB_To_XYZ(rgb);
		case xyY:
			return XYZ_To_xyY(RGB_To_XYZ(rgb));
		case RGB:
			return rgb;
		case sRGB:
			return RGB_To_sRGB(rgb);
		}
	}
}