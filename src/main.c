#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
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
#include "renderer.h"

int main()
{
    initSPDs();
    vec3 rgb = {1, 0, 0};
    SPD color = SPD_FromRGB(rgb);
    rgb = sRGB_To_RGB(RGB_FromSPD(color, Human_Eye));
    Image img = Image_Create(256, 256);
    for(uint32_t i = 0; i < img.width * img.height; i++)
        img.data[i] = rgb;
    Image_SaveToBMP(img, "image.bmp");
    // while(true);
}