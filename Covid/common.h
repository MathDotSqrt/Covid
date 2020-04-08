#pragma once

typedef unsigned char u8;
typedef signed char i8;

typedef unsigned short u16;
typedef signed short i16;

typedef unsigned int u32;
typedef signed int i32;

typedef unsigned long u64;
typedef signed long i64;

typedef float f32;
typedef double f64;

constexpr f32 MAX_MAGNITUDE = 0.1f;
constexpr f32 PI = 3.14159265359f;
constexpr f32 EPSILON = 0.001f;

constexpr f32 RADIUS = .5f;
constexpr f32 RADIUS2 = RADIUS * RADIUS;

constexpr f32 BETA = 0.1f;
constexpr f32 GAMMA = 0.03f;