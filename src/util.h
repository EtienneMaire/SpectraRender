#pragma once

#define real_t          float

#define sqr(x)          ((x) * (x))
#define ln(x)           log(x)

#define lerp(a, b, t)   ((a) * (1 - (t)) + (b) * (t))

#define min(a, b)       (a < b ? a : b)
#define max(a, b)       (a > b ? a : b)

#define MAX_RAY_DEPTH   8
#define MAX_MTLLIB_SIZE 64

#define swap(a, b) { real_t tmp = a; a = b; b = tmp; }
