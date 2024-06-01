#include "Triangle.hpp"

//https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution.html
bool Triangle::intersect(glm::vec3 rayOrigin, glm::vec3 rayDirection,
	float& t, glm::vec3& X, glm::vec3& N)
{
    glm::vec3 ab = b - a;
    glm::vec3 ac = c - a;
    glm::vec3 n = cross(ab, ac);

    float N_rayDir = dot(n, rayDirection);

    N = n;
    if (N_rayDir > 0)
        N = -N;

    if (abs(N_rayDir) <= 0.001f) // Ray and triangle plane are parallel
        return false;

    float d = -dot(n, a);

    t = -(dot(n, rayOrigin) + d) / N_rayDir;

    if (t < 0) return false;

    X = rayOrigin + t * rayDirection;

    glm::vec3 C;

    glm::vec3 edge0 = b - a;
    glm::vec3 vp0 = X - a;
    C = cross(edge0, vp0);
    if (dot(n, C) < 0) return false;

    glm::vec3 edge1 = c - b;
    glm::vec3 vp1 = X - b;
    C = cross(edge1, vp1);
    if (dot(n, C) < 0) return false; 

    glm::vec3 edge2 = a - c;
    glm::vec3 vp2 = X - c;
    C = cross(edge2, vp2);
    if (dot(n, C) < 0) return false; 

    return true;
}