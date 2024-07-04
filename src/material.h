#pragma once

typedef struct Material
{
    vec3 albedo;        // {
    vec3 emission;      // } -> As an RGB color to save memory

    real roughness;     // 0: perfectly smooth -> +∞ infinitely rough
    bool metallic;      // 0: dielectric -> 1: conductor
    bool transmission;  // 0: opaque -> 1: transparent
    
    real η;             // {
    real k;             // } -> IOR = η + ki

    char name[64];
} Material; 

typedef struct MaterialLibrary
{
    Material* mat;
    uint8_t matCount;
} MaterialLibrary;

MaterialLibrary MaterialLibrary_LoadFromMTL(const char* path)
{
    MaterialLibrary mtllib;
    mtllib.mat = NULL;
    mtllib.matCount = 0;

    FILE* f = fopen(path, "r");

    if(!f)
        return mtllib;
    
    Material mats[MAX_MTLLIB_SIZE];
    uint8_t matCount = 0xff;
    Material currentMat;

    char line[64];
    while(fgets(line, 64, f))
    {
        char keyword[8];
        sscanf(line, "%8s", keyword);

        if(strcmp(keyword, "newmtl") == 0)
        {
            if(matCount != 0xff)
                mats[matCount] = currentMat;
            sscanf(line, "%64s", currentMat.name);
            matCount++;
        }
        else
        {
            if(strcmp(keyword, "Kd") == 0)
            {
                real X, Y, Z;
                sscanf(line, "%f", &X);
                sscanf(line, "%f", &Y);
                sscanf(line, "%f", &Z);
                currentMat.albedo.x = X;
                currentMat.albedo.y = Y;
                currentMat.albedo.z = Z;
            }
            else if(strcmp(keyword, "Ke") == 0)
            {
                real X, Y, Z;
                sscanf(line, "%f", &X);
                sscanf(line, "%f", &Y);
                sscanf(line, "%f", &Z);
                currentMat.emission.x = X;
                currentMat.emission.y = Y;
                currentMat.emission.z = Z;
            }
            else if(strcmp(keyword, "Ni") == 0)
            {
                real η;
                sscanf(line, "%f", &η);
                currentMat.η = η;
                currentMat.k = 0;   // Sadly not supported by most 3D softwares
            }
            else if(strcmp(keyword, "Pr") == 0)
            {
                real α;
                sscanf(line, "%f", &α);
                currentMat.roughness = α;
            }
            else if(strcmp(keyword, "Pm") == 0)
            {
                real metallic;
                sscanf(line, "%f", &metallic);
                currentMat.metallic = metallic;
            }
            else if(strcmp(keyword, "Tf") == 0)
            {
                real transmission;
                sscanf(line, "%f", &transmission);
                currentMat.transmission = transmission;
            }
        }
    }

    mtllib.matCount = matCount;
    mtllib.mat = (Material*)malloc(matCount * sizeof(Material));
    memcpy(mtllib.mat, mats, matCount * sizeof(Material));

    fclose(f);

    return mtllib;
}

void MaterialLibrary_free(MaterialLibrary* lib)
{
    free(lib->mat);
    lib->matCount = 0;
}