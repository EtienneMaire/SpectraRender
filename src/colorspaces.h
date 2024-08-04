#pragma once

mat3 XYZ_To_RGB_matrix = 
{
    {
        {  2.36461385, -0.89654057, -0.46807328 },
        { -0.51516621,  1.4264081,   0.0887581  },
        {  0.0052037,  -0.01440816,  1.00920446 }
    }
};

mat3 RGB_To_XYZ_matrix = 
{
    {
        {  0.49000, 0.31000, 0.20000 },
        {  0.17697, 0.81240, 0.01063 },
        {  0.00000, 0.01000, 0.99000 } 
    }
};

vec3 D65_XYZ = { 0.9504, 1.0000, 1.0888 };

vec3 XYZ_To_RGB(vec3 xyz)
{
    return mul_mat3_vec3(XYZ_To_RGB_matrix, xyz);
}

vec3 RGB_To_XYZ(vec3 rgb)
{
    return mul_mat3_vec3(RGB_To_XYZ_matrix, rgb);
}

vec3 sRGB_To_RGB(vec3 srgb)
{
    srgb.x = max(0, srgb.x);
    srgb.y = max(0, srgb.y);
    srgb.z = max(0, srgb.z);

    vec3 out = {pow(srgb.x, 1 / 2.2f),
        pow(srgb.y, 1 / 2.2f),
        pow(srgb.z, 1 / 2.2f)};
    return out;
}

vec3 RGB_To_sRGB(vec3 rgb)
{
    rgb.x = max(0, rgb.x);
    rgb.y = max(0, rgb.y);
    rgb.z = max(0, rgb.z);

    vec3 out = {pow(rgb.x, 2.2f),
        pow(rgb.y, 2.2f),
        pow(rgb.z, 2.2f)};
    return out;
}