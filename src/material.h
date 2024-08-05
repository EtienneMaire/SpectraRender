#pragma once

typedef struct IOR
{
    real_t η;             // {
    real_t k;             // } -> IOR = η - ki
} IOR;

typedef struct Material
{
    vec3 albedo;        // {
    vec3 emission;      // } -> As an RGB color to save memory

    real_t roughness;   // 0: perfectly smooth -> +∞ infinitely rough
    bool metallic;      // 0: dielectric -> 1: conductor
    bool opaque;        
    
    IOR ior;

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
    printf("Loading material library \"%s\" ...", path);

    MaterialLibrary mtllib = MaterialLibrary_CreateEmpty();

    FILE* f = fopen(path, "r");

    if(!f)
    {
        printf(" | Error: No such path or directory\n");
        return mtllib;
    }
    
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
                double X, Y, Z;
                sscanf(line, "%*s %lf %lf %lf", &X, &Y, &Z);
                currentMat.albedo.x = X;
                currentMat.albedo.y = Y;
                currentMat.albedo.z = Z;
            }
            else if(strcmp(keyword, "Ke") == 0)
            {
                double X, Y, Z;
                sscanf(line, "%*s %lf %lf %lf", &X, &Y, &Z);
                currentMat.emission.x = X;
                currentMat.emission.y = Y;
                currentMat.emission.z = Z;
            }
            else if(strcmp(keyword, "Ni") == 0)
            {
                double η;
                sscanf(line, "%*s %lf", &η);
                currentMat.ior.η = η;
                currentMat.ior.k = 0;   // Sadly not supported by most 3D softwares
            }
            else if(strcmp(keyword, "Pr") == 0)
            {
                double α;
                sscanf(line, "%*s %lf", &α);
                currentMat.roughness = α;
            }
            else if(strcmp(keyword, "Pm") == 0)
            {
                double metallic;
                sscanf(line, "%*s %lf", &metallic);
                currentMat.metallic = metallic == 1;
            }
            else if(strcmp(keyword, "Tf") == 0)
            {
                double transmission;
                sscanf(line, "%*s %lf", &transmission);
                currentMat.opaque = transmission < 0.5f;
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

    printf(" | Done\n");
    return mtllib;
}

void MaterialLibrary_free(MaterialLibrary* lib)
{
    free(lib->mat);
    lib->matCount = 0;
}