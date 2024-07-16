#pragma once

typedef struct Material
{
    vec3 albedo;        // {
    vec3 emission;      // } -> As an RGB color to save memory

    real_t roughness;     // 0: perfectly smooth -> +∞ infinitely rough
    bool metallic;      // 0: dielectric -> 1: conductor
    bool transmission;  // 0: opaque -> 1: transparent
    
    real_t η;             // {
    real_t k;             // } -> IOR = η - ki

    char name[64];
} Material; 

typedef struct MaterialLibrary
{
    Material* mat;
    uint8_t matCount;
} MaterialLibrary;

MaterialLibrary MaterialLibrary_CreateEmpty()
{
    MaterialLibrary mtllib;
    
    mtllib.mat = NULL;
    mtllib.matCount = 0;

    return mtllib;
}

MaterialLibrary MaterialLibrary_LoadFromMTL(const char* path)
{
    MaterialLibrary mtllib = MaterialLibrary_CreateEmpty();

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
            sscanf(line, "%*s %64s", currentMat.name);
            matCount++;
        }
        else
        {
            if(strcmp(keyword, "Kd") == 0)
            {
                real_t X, Y, Z;
                sscanf(line, "%*s %f %f %f", &X, &Y, &Z);
                currentMat.albedo.x = X;
                currentMat.albedo.y = Y;
                currentMat.albedo.z = Z;
            }
            else if(strcmp(keyword, "Ke") == 0)
            {
                real_t X, Y, Z;
                sscanf(line, "%*s %f %f %f", &X, &Y, &Z);
                currentMat.emission.x = X;
                currentMat.emission.y = Y;
                currentMat.emission.z = Z;
            }
            else if(strcmp(keyword, "Ni") == 0)
            {
                real_t η;
                sscanf(line, "%*s %f", &η);
                currentMat.η = η;
                currentMat.k = 0;   // Sadly not supported by most 3D softwares
            }
            else if(strcmp(keyword, "Pr") == 0)
            {
                real_t α;
                sscanf(line, "%*s %f", &α);
                currentMat.roughness = α;
            }
            else if(strcmp(keyword, "Pm") == 0)
            {
                real_t metallic;
                sscanf(line, "%*s %f", &metallic);
                currentMat.metallic = metallic == 1;
            }
            else if(strcmp(keyword, "Tf") == 0)
            {
                real_t transmission;
                sscanf(line, "%*s %f", &transmission);
                currentMat.transmission = transmission;
            }
        }
    }

    if(matCount != 0xff)
        mats[matCount] = currentMat;
    sscanf(line, "%*s %64s", currentMat.name);
    matCount++;
    
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