#pragma once

//types for integral types
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
constexpr f32 PI = 3.14159265359f;				//Good ole PI
constexpr f32 EPSILON = 0.1f;					//Pretty large epsilon lmao

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
constexpr f32 BAD_ACTOR = 0.01f;				//Proportion of population who are bad bois
constexpr f32 TEST_ACCURACY_RATE = 0.000f;		//Testing accuracy rate for covid test
constexpr i32 MAX_SHOP = 50;					//Maximum occupancy in hub zones
/*AGENT PARAMETERS*/

/*DETAIL*/
constexpr int GRID_WIDTH = 25;					//Spacial Width of entire map
constexpr int NUM_GRIDS = 25;					//Number of spacial partitions in grid. The larger the faster the model computes (Substantially)
constexpr int NUM_EXPERIMENTS = 101;			//Number of experiments to run for our statistical analysis
constexpr int NUM_THREADS = 8;					//Number of worker threads to run. Should be equal to the number of cores on your cpu

constexpr i32 SCREEN_WIDTH = 1024 / 2;			//Size of visual window
constexpr i32 SCREEN_HEIGHT = 1024 / 2;			//Size of visual window
/*DETAIL*/

/*
	NOTE: (GRID_WIDTH / NUM_GRIDS) >= RADIUS or else model is inaccurate for control.
	NOTE: (GRID_WIDTH / NUM_GRIDS) >= MAX_CHARGE_DIST or else social distancing algorithm becomes instable 
	NOTE: GRID_WIDTH affects the size of hub zones so it effects community based models. 
*/