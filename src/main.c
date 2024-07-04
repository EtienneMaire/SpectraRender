#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "util.h"
#include "cameradefs.h"
#include "vec3.h"
#include "image.h"
#include "SPDdefs.h"
#include "mat3.h"
#include "colorspaces.h"
#include "SPD.h"
#include "material.h"

#include "mesh.h"
#include "renderer.h"

int main()
{
    initSPDs();

    // MaterialLibrary mtllib = MaterialLibrary_LoadFromMTL("../scenes/cornellbox.mtl");

    vec3 rgb = {1, 0, 0};
    SPD color = SPD_FromRGB(rgb);
    rgb = sRGB_To_RGB(RGB_FromSPD(color, Human_Eye));

    Image img = Image_Create(256, 256);

    for(uint32_t i = 0; i < img.width * img.height; i++)
        img.data[i] = rgb;

    char* fileName = "../out/image.bmp";
    printf("Saving to file \"%s\" ...", fileName);
    Image_SaveToBMP(img, fileName);
    printf(" | Done\n");
    while(true);
}