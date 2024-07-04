#pragma once

typedef struct Material
{
    vec3 albedo;    // As an RGB color to save memory
    real roughness; // 0: perfectly smooth -> +∞
    bool metallic;  // 0: dielectric -> 1: conductor
    
    real eta;       // {
    real k;         // } -> IOR

    char name[64];
} Material; 

typedef struct MaterialLibrary
{
    Material* mat;
    uint8_t matCount;
} MaterialLibrary;

MaterialLibrary MaterialLibrary_LoadFromMTL(const char* path)
{
    FILE* f = fopen(path, "r");
    
    Material mats[MAX_MTLLIB_SIZE];
    uint8_t matCount = 0xff;
    Material currentMat;

    char* keyword;
    while(fscanf(f, "%s", keyword) != EOF)
    {
        printf("%s\n", keyword);
        if(strcmp(keyword, "newmtl") == 0)
        {
            if(matCount != 0xff)
                mats[matCount] = currentMat;
            matCount++;
        }
        else
        {

        }
    }

    fclose(f);

    MaterialLibrary mtllib;
    mtllib.mat = NULL;
    mtllib.matCount = 0;
    return mtllib;
}