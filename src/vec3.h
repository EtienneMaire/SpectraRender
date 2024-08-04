#pragma once

typedef struct vec3
{
    real_t x, y, z;
} vec3;

vec3 mul_vec3(vec3 u, vec3 v)
{
    vec3 out = {u.x * v.x, u.y * v.y, u.z * v.z};
    return out;
}

vec3 add_vec3(vec3 u, vec3 v)
{
    vec3 out = {u.x + v.x, u.y + v.y, u.z + v.z};
    return out;
}

vec3 mul_vec3_k(vec3 u, real_t k)
{
    vec3 out = {u.x * k, u.y * k, u.z * k};
    return out;
}

vec3 mul_vec3_vec3(vec3 u, vec3 v)
{
    vec3 out = {u.x * v.x, u.y * v.y, u.z * v.z};
    return out;
}

vec3 div_vec3_k(vec3 u, real_t k)
{
    vec3 out = {u.x / k, u.y / k, u.z / k};
    return out;
}

vec3 div_vec3_vec3(vec3 u, vec3 v)
{
    vec3 out = {u.x / v.x, u.y / v.y, u.z / v.z};
    return out;
}

real_t dot(vec3 u, vec3 v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

real_t norm2(vec3 u)
{
    return dot(u, u);
}

real_t norm(vec3 u)
{
    return sqrt(norm2(u));
}

vec3 cross(vec3 a, vec3 b)
{
    vec3 out = 
    {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
    return out;
}