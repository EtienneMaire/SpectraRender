#pragma once

typedef struct mat3 
{
    real data[3][3];
} mat3;

vec3 mul_vec3_mat3(vec3 u, mat3 mat)
{
    vec3 out;
    vec3 column0 = { mat.data[0][0], mat.data[1][0], mat.data[2][0] };
    out.x = dot(u, column0);
    vec3 column1 = { mat.data[0][1], mat.data[1][1], mat.data[2][1] };
    out.y = dot(u, column1);
    vec3 column2 = { mat.data[0][2], mat.data[1][2], mat.data[2][2] };
    out.z = dot(u, column2);
    return out;
}