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

char* strndup(const char *s, size_t n)
{
    char *result;
    size_t len = strnlen(s, n);

    result = (char*)malloc(len + 1);
    if (!result)
    return NULL;

    result[len] = '\0';
    return (char*)memcpy(result, s, len);
}

char* strdup(const char *s)
{
    size_t len = strlen(s) + 1;
    char* result = (char*)malloc(len);
    if (result == (char*)0)
    return NULL;
    return (char*)memcpy(result, s, len);
}

void Separate_Path_Filename(char** p, char** f, char *pf) 
{
    char *slash = pf, *next;
    while ((next = strpbrk(slash + 1, "\\/"))) slash = next;
    if (pf != slash) slash++;
    *p = strndup(pf, slash - pf);
    *f = strdup(slash);
}