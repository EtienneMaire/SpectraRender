#pragma once

typedef struct vec3_vector
{
    vec3* data;
    size_t allocated; 
    size_t size;
} vec3_vector;

vec3_vector vec3_vector_CreateEmpty()
{
    vec3_vector vector;
    vector.allocated = 16;
    vector.size = 0;
    vector.data = malloc(sizeof(vec3) * vector.allocated);
    return vector;
}

void vec3_vector_Free(vec3_vector* vec)
{
    free(vec->data);
    vec->data = NULL;
    vec->allocated = vec->size = 0;
}

void vec3_vector_Resize(vec3_vector* vec, uint8_t size)
{
    vec->allocated = size;
    vec->data = realloc(vec->data, size * sizeof(vec3) * vec->allocated);
}

void vec3_vector_PushBack(vec3_vector* vec, vec3 item)
{
    if(vec->size >= vec->allocated)
        vec3_vector_Resize(vec, 2 * vec->size);
    vec->data[vec->size++] = item;
}

void vec3_vector_PopBack(vec3_vector* vec)
{
    if(vec->size < vec->allocated / 2)
        vec3_vector_Resize(vec, 0.5 * vec->size);
    vec->size--;
}

void vec3_vector_Clear(vec3_vector* vec)
{
    vec3_vector_Free(vec);
    *vec = vec3_vector_CreateEmpty();
}