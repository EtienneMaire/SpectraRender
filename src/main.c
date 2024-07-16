#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "util.h"
#include "vector.h"
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

    Scene scene = Scene_LoadFromOBJ("../scenes/cornellbox.obj");

    Image img = Image_Create(256, 256);

    Scene_free(&scene);

    char* fileName = "../out/image.bmp";
    printf("Saving to file \"%s\" ...", fileName);
    Image_SaveToBMP(img, fileName);
    printf(" | Done\n");

    while(true);
}