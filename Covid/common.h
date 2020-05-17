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

constexpr f32 t_05_5 = 2.571f;
constexpr f32 t_05_100 = 1.982f;
/*MATH CONSTANTS*/

/*MOVEMENT CONSTANTS*/
constexpr f32 MAX_MAGNITUDE = 0.004f;			//Max movement
constexpr f32 CHANGE_DIR = .01f;				//Probability of changin dir
constexpr f32 TELEPORT = .01f;					//Probability of teleport

constexpr f32 MAX_CHARGE_DIST = 1.0f;			//Maximum distance social-distance force 
constexpr f32 MAX_CHARGE = .02f;				//Max Social-distance force
constexpr f32 CHARGE_CONSTANT = .00002f;		//Repeling force constant
/*MOVEMENT CONSTANTS*/

/*INFECTION RATE*/
constexpr f32 BETA = 0.05f;						//Infection Rate
constexpr f32 GAMMA = 0.001f;					//Recovary Rate

constexpr f32 RADIUS = .25f;					//Infection Radius
constexpr f32 RADIUS2 = RADIUS * RADIUS;		//Radius Squared
/*INFECTION RATE*/

/*AGENT PARAMETERS*/
constexpr i32 SUSCEPTIBLE = 5000;				//Initial population Susceptible
constexpr i32 INFECTED = 50;					//Initial population infected
constexpr f32 BAD_ACTOR = 0.00f;				//Proportion of population who are bad bois
constexpr f32 TEST_ACCURACY_RATE = 0.000f;		//Testing accuracy rate for covid test
constexpr i32 MAX_SHOP = 0;						//Maximum occupancy in hub zones
/*AGENT PARAMETERS*/

/*DETAIL*/
constexpr int NUM_GRIDS = 25;
constexpr int NUM_EXPERIMENTS = 101;
constexpr int NUM_THREADS = 8;

constexpr i32 SCREEN_WIDTH = 1024 / 2;
constexpr i32 SCREEN_HEIGHT = 1024 / 2;
/*DETAIL*/