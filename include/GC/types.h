#ifndef TYPES_H
#define TYPES_H

// Types for Spyro

#define NULL 0

typedef unsigned int size_t;
typedef long int ssize_t;

typedef float f32;
typedef double f64;

typedef struct vec128_t
{
    float x, y, z, w;
} vec128_t __attribute__((aligned(8)));

typedef unsigned char u8;
typedef short unsigned int u16;
typedef unsigned int u32;
typedef long unsigned int u64;
typedef struct u128
{
    u32 w[4];
} u128 __attribute__((aligned(8)));

typedef signed char s8;
typedef short int s16;
typedef int s32;
typedef long int s64;
typedef struct s128
{
    s32 w[4];
} s128 __attribute__((aligned(16)));

typedef signed char Bool;
typedef short unsigned int wchar;

typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef unsigned int size_t;
typedef long unsigned int clock_t;
typedef long int time_t;

// typedef char* __gnuc_va_list;
// typedef __gnuc_va_list va_list;

typedef int _iconVu0IVECTOR[4];
typedef float _iconVu0FVECTOR[4];

#endif // TYPES_H
