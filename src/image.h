#pragma once

typedef struct Image
{
    uint16_t width, height;
    vec3* data;
} Image;

Image Image_Create(uint16_t width, uint16_t height)
{
    Image img;
    img.width = width;
    img.height = height;
    img.data = (vec3*)malloc(width * height * sizeof(vec3));
    return img;
}

void Image_SaveToBMP(Image img, const char* path)
{
    uint16_t width = img.width, height = img.height;

	struct BMPHeader
	{
		uint8_t  signature[2];
		uint32_t fileSize;
		uint32_t reservedBytes;
		uint32_t pixelDataOffset;
	} __attribute__((packed));

	struct BMPInfoHeader
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
	} __attribute__((packed));


	struct BMPHeader header;
	struct BMPInfoHeader infoHeader;

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

    FILE* f = fopen(path, "wb");

    fwrite((char*)&header, sizeof(struct BMPHeader), 1, f);
    fwrite((char*)&infoHeader, sizeof(struct BMPInfoHeader), 1, f);
	
	struct BGR
	{
		uint8_t b;
		uint8_t g;
		uint8_t r;
	} __attribute__((packed));

	for (uint32_t i = 0; i < (uint32_t)width * (uint32_t)height; i++)
	{
		struct BGR color;
		color.r = (uint8_t)(255 * max(min(img.data[i].x, 1.f), 0.f));
		color.g = (uint8_t)(255 * max(min(img.data[i].y, 1.f), 0.f));
		color.b = (uint8_t)(255 * max(min(img.data[i].z, 1.f), 0.f));
        
        fwrite((char*)&color, sizeof(struct BGR), 1, f);
	}

	fclose(f);
}