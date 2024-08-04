#pragma once

typedef struct mat3 
{
    real_t data[3][3];
} mat3;

void mat3_transpose(mat3* mat)
{
    swap(mat->data[0][1], mat->data[1][0]);
    swap(mat->data[0][2], mat->data[2][0]);

    swap(mat->data[2][1], mat->data[1][2]);
}

vec3 mul_mat3_vec3(mat3 mat, vec3 u)
{
    vec3 result = {0, 0, 0};
    vec3 row0 = {mat.data[0][0], mat.data[0][1], mat.data[0][2]};
    result.x = dot(u, row0);
    vec3 row1 = {mat.data[1][0], mat.data[1][1], mat.data[1][2]};
    result.y = dot(u, row1);
    vec3 row2 = {mat.data[2][0], mat.data[2][1], mat.data[2][2]};
    result.z = dot(u, row2);
    return result;
}