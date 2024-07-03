#pragma once

mat3 XYZ_To_RGB_matrix = 
{
    {
        {  2.3706743, -0.9000405, -0.4706338 },
        { -0.5138850,  1.4253036,  0.0885814 },
        {  0.0052982, -0.0146949,  1.0093968 }
    }
};

mat3 RGB_To_XYZ_matrix = 
{
    {
        {  0.4887180,  0.3106803,  0.2006017 },
        {  0.1762044,  0.8129847,  0.0108109 },
        {  0.0000000,  0.0102048,  0.9897952 }
    }
};

vec3 XYZ_To_RGB(vec3 xyz)
{
    return mul_vec3_mat3(xyz, XYZ_To_RGB_matrix);
}

vec3 RGB_To_XYZ(vec3 rgb)
{
    return mul_vec3_mat3(rgb, RGB_To_XYZ_matrix);
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