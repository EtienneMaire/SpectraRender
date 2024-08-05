#pragma once

typedef struct Triangle
{
    vec3 a, b, c;
} Triangle;

typedef struct Mesh
{
    Triangle* data;
    uint64_t triangleCount;
    Material* mat;

    char name[64];
} Mesh;

typedef struct Scene
{
    Mesh* meshes;
    uint32_t meshCount;

    MaterialLibrary mtllib;
} Scene;

Mesh Mesh_CreateEmpty()
{
    Mesh mesh;
    mesh.data = NULL;
    mesh.triangleCount = 0;
    mesh.mat = NULL;
    return mesh;
}

Scene Scene_CreateEmpty()
{
    Scene scene;
    scene.meshes = NULL;
    scene.meshCount = 0;
    scene.mtllib = MaterialLibrary_CreateEmpty();
    return scene;
}

Scene Scene_LoadFromOBJ(char* fullpath)
{
    char* filename;
    char* path;
    Separate_Path_Filename(&path, &filename, fullpath);

    printf("Loading scene \"%s\" ...", filename);

    Scene scene = Scene_CreateEmpty();

    if(chdir(path))
    {
        printf(" | Error: No such path or directory\n");
        return scene;
    }

    FILE* f = fopen(fullpath, "r");     

    if(!f)
    {
        printf(" | Error: No such path or directory\n");
        return scene;
    }

    char mtllibName[64 - 7];

    char line[64];
    while(fgets(line, 64, f))
    {
        char keyword[8];
        sscanf(line, "%8s", keyword);           

        if(strcmp(keyword, "mtllib") == 0)
        {
            sscanf(line, "%*s %64s", mtllibName);
        }
    }

    fclose(f);

    vec3_vector vertices = vec3_vector_CreateEmpty();

    vec3_vector_Free(&vertices); 
    free(filename);
    free(path);

    printf(" | Done\n");

    scene.mtllib = MaterialLibrary_LoadFromMTL((char*)&mtllibName);
    return scene;
}

void Scene_free(Scene* scene)
{
    free(scene->meshes);
    scene->meshCount = 0;
    MaterialLibrary_free(&scene->mtllib);
}