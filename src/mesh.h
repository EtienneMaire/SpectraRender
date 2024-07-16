#pragma once

typedef struct Triangle
{
    vec3 a, b, c;
    Material* mat;
} Triangle;

typedef struct Mesh
{
    Triangle* data;
    uint64_t triangleCount;

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

Scene Scene_LoadFromOBJ(const char* path)
{
    Scene scene = Scene_CreateEmpty();
    vec3_vector vertices = vec3_vector_CreateEmpty();
    vec3_vector_Free(&vertices); 
    return scene;
}

void Scene_free(Scene* scene)
{
    free(scene->meshes);
    scene->meshCount = 0;
    MaterialLibrary_free(&scene->mtllib);
}