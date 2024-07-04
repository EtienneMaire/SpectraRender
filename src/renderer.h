#pragma once

typedef struct PathNode
{
    Material mat;
    vec3 N, X;
} PathNode;

typedef struct Path
{
    PathNode nodes[MAX_RAY_DEPTH];
    SPD T[MAX_RAY_DEPTH];
    uint8_t depth;
} Path;