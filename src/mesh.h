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
} Mesh;


Mesh Mesh_CreateEmpty()
{
    Mesh mesh;
    mesh.data = NULL;
    mesh.triangleCount = 0;
    return mesh;
}