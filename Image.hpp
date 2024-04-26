#pragma once

#include <glm/vec3.hpp>
#include <fstream>

#define PACK(__Declaration__) __pragma(pack(push, 1)) __Declaration__ __pragma(pack(pop))

class Image
{
public:
	Image()
	{
		data = NULL;
		width = 0;
		height = 0;
	}

	Image(uint16_t _width, uint16_t _height)
	{
		create(_width, _height);
	}

	~Image()
	{
		if (data)
			delete[] data;
	}

	void create(uint16_t _width, uint16_t _height)
	{
		if (data)
			delete[] data;
		width = _width;
		height = _height;
		data = new glm::vec3[width * height];
	}

	void setPixel(uint16_t x, uint16_t y, glm::vec3 color)
	{
		if (x >= width || y >= height)
			return;
		data[uint32_t(y) * uint32_t(width) + uint32_t(x)] = color;
	}

	glm::vec3 getPixel(uint16_t x, uint16_t y)
	{
		if (x >= width || y >= height)
			return glm::vec3(0);
		return data[uint32_t(y) * uint32_t(width) + uint32_t(x)];
	}

	void saveToBMP(std::string path)
	{
		PACK(struct BMPHeader
		{
			uint8_t  signature[2];
			uint32_t fileSize;
			uint32_t reservedBytes;
			uint32_t pixelDataOffset;
		});

		PACK(struct BMPInfoHeader
		{
			uint32_t headerSize;
			int32_t width;
			int32_t height; 
			uint16_t colorPlanes;
			uint16_t colorDepth;
			uint32_t compressionMethod;
			uint32_t dataSize;
			int32_t resX;
			int32_t resY;
			uint32_t colorTableEntries;
			uint32_t importantColors;
		});


		BMPHeader header;
		BMPInfoHeader infoHeader;

		infoHeader.headerSize = 40;
		infoHeader.width = width;
		infoHeader.height = height;
		infoHeader.colorPlanes = 1;
		infoHeader.colorDepth = 24;
		infoHeader.compressionMethod = 0;
		infoHeader.dataSize = 0;
		infoHeader.resX = 3780;
		infoHeader.resY = 3780;
		infoHeader.colorTableEntries = 0;
		infoHeader.importantColors = 0;

		header.signature[0] = 'B';
		header.signature[1] = 'M';

		header.pixelDataOffset = 54; // sizeof(BMPHeader) + infoHeader.headerSize

		header.fileSize = header.pixelDataOffset + (width * height * 3);

		std::ofstream f(path, std::ios::binary);

		f.write((char*)&header, sizeof(BMPHeader));
		f.write((char*)&infoHeader, sizeof(BMPInfoHeader));
		
		PACK(struct BGR
		{
			uint8_t b;
			uint8_t g;
			uint8_t r;
		});

		for (uint32_t i = 0; i < uint32_t(width) * uint32_t(height); i++)
		{
			BGR color;
			color.r = uint8_t(255 * std::max(std::min(data[i].r, 1.f), 0.f));
			color.g = uint8_t(255 * std::max(std::min(data[i].g, 1.f), 0.f));
			color.b = uint8_t(255 * std::max(std::min(data[i].b, 1.f), 0.f));
			f.write((char*)&color, sizeof(BGR));
		}

		f.close();
	}

public:
	glm::vec3* data;
	uint16_t width, height;
};