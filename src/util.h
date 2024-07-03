#pragma once

#define real            float

#define sqr(x)          (x * x)
#define ln(x)           log(x)

#define lerp(a, b, t)   ((a) * (1 - (t)) + (b) * (t))

#define min(a, b)       (a < b ? a : b)
#define max(a, b)       (a > b ? a : b)