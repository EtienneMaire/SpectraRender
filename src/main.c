#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "util.h"
#include "cameradefs.h"
#include "vec3.h"
#include "vector.h"

#include "image.h"
#include "SPDdefs.h"
#include "mat3.h"
#include "colorspaces.h"
#include "SPD.h"
#include "material.h"

#include "mesh.h"
#include "renderer.h"

void __attribute__ ((constructor)) Init()
{
    initSPDs();
}

int main()
{
    Scene scene = Scene_LoadFromOBJ("../scenes/cornellbox.obj");

    Image img = Image_Create(256, 256);

    vec3 rgb = {1, 1, 1};
    SPD spd = SPD_FromRGB(rgb);
    rgb = RGB_FromSPD(spd, Human_Eye);

    for(uint32_t i = 0; i < img.width * img.height; i++)
        img.data[i] = rgb;

    Scene_free(&scene);

    char* fileName = "../out/image.bmp";
    printf("Saving to file \"%s\" ...", fileName);
    Image_SaveToBMP(img, fileName);
    printf(" | Done\n");

    while(true);
}