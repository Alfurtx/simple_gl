/* date = August 31st 2022 11:03 am */

#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <stdint.h>

// NOTE(fonsi): Graphics library includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef float  float32;
typedef double float64;

typedef int bool32;

typedef unsigned int uint;

#define internal static
#define local_persist static
#define global_file static

#define NDEBUG
#include <assert.h>
#undef assert
#define assert(E, M) (void)( (E) || (_assert(#E, __LINE__, __FILE__, M), 0) )

void
_assert(const char* expr, const int line, const char* file, char* custom_msg)
{
    if(custom_msg != 0) {
        fprintf(stderr, "[ERROR][%s:%d][%s] %s\n", file, line, expr, custom_msg);
    } else {
        fprintf(stderr, "[ERROR][%s:%d] %s\n", file, line, expr);
    }
    
    exit(EXIT_FAILURE);
}

#endif //COMMON_H
