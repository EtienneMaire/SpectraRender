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
		glm::vec3( 0.4887180, 0.3106803, 0.2006017 ),
		glm::vec3( 0.1762044, 0.8129847, 0.0108109 ),
		glm::vec3( 0.0000000, 0.0102048, 0.9897952 ));
	glm::mat3 XYZ_To_RGB_matrix(
		glm::vec3(  2.3706743, -0.9000405, -0.4706338 ),
		glm::vec3( -0.5138850,  1.4253036,  0.0885814 ),
		glm::vec3(  0.0052982, -0.0146949,  1.0093968 ));

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
		return xyz * XYZ_To_RGB_matrix;
	} 

	glm::vec3 RGB_To_XYZ(glm::vec3 rgb)
	{
		return rgb * RGB_To_XYZ_matrix;
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