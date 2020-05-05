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

/*MATH CONSTANTS*/
constexpr f32 PI = 3.14159265359f;
constexpr f32 EPSILON = 0.1f;

//confidence interval and df
constexpr f32 t_05_5 = 2.571f;
constexpr f32 t_05_100 = 1.982f;
/*MATH CONSTANTS*/

/*MOVEMENT CONSTANTS*/
constexpr f32 MAX_MAGNITUDE = 0.007f;
constexpr f32 CHANGE_DIR = .01f;

constexpr f32 MAX_CHARGE_DIST = 1.0f;
constexpr f32 MAX_CHARGE = .002f;
constexpr f32 CHARGE_CONSTANT = .00001f;
/*MOVEMENT CONSTANTS*/

/*INFECTION RATE*/
constexpr f32 BETA = 0.07f / 4;
constexpr f32 GAMMA = 0.05f / 4;

/*INFECTION RATE*/



constexpr int NUM_GRIDS = 25;


constexpr f32 RADIUS = .4f;
constexpr f32 RADIUS2 = RADIUS * RADIUS;

constexpr int NUM_EXPERIMENTS = 101;

constexpr i32 SCREEN_WIDTH = 1024;
constexpr i32 SCREEN_HEIGHT = 1024;
