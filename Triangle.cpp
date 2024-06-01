#include "Triangle.hpp"

//https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution.html
bool Triangle::intersection(glm::vec3 rayOrigin, glm::vec3 rayDirection,
	float& t, glm::vec3& X)
{
    glm::vec3 ab = b - a;
    glm::vec3 ac = c - a;
    glm::vec3 N = cross(ab, ac);
    //float area2 = N.length();

    float N_rayDir = dot(N, rayDirection);
    if (abs(N_rayDir) <= 0.001f) // Ray and triangle plane are parallel
        return false;

    float d = -dot(N, a);

    t = -(dot(N, rayOrigin) + d) / N_rayDir;

    if (t < 0) return false;

    X = rayOrigin + t * rayDirection;

    glm::vec3 C;

    glm::vec3 edge0 = b - a;
    glm::vec3 vp0 = X - a;
    C = cross(edge0, vp0);
    if (dot(N, C) < 0) return false;

    glm::vec3 edge1 = c - b;
    glm::vec3 vp1 = X - b;
    C = cross(edge1, vp1);
    if (dot(N, C) < 0) return false; 

    glm::vec3 edge2 = a - c;
    glm::vec3 vp2 = X - c;
    C = cross(edge2, vp2);
    if (dot(N, C) < 0) return false; 

    return true;
}