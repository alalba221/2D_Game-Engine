#pragma once
// #ifdef ALALBA_PLATFORM_LINUX
	
// 	#ifdef ALALBA_BUILD_DLL
// 		#define ALALBA_API __attribute__((visibility("default")))
// 	#else
// 		#define ALALBA_API
// 	#endif // ALALBA_BUILD_DLL
// #else
// 	#error Alalba only support Linux!
// #endif

// #define ALALBA_APP_ASSERT(x, ...) { if(!(x)) { ALALBA_APP_ERROR("Assertion Failed: {0}", __VA_ARGS__); abort(); } }
// #define ALALBA_CORE_ASSERT(x, ...) { if(!(x)) { ALALBA_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); abort(); } }
#include <cmath>
#define ALALBA_API 
#define BIT(x) (1<<x)

constexpr int FPS = 60;
constexpr int ZOOM = 4;
constexpr int FRAME_DURATION = 1000 / FPS;


constexpr int SNES_RESOLUTION_WIDTH = 256;
constexpr int SNES_RESOLUTION_HEIGHT = 224;

constexpr int TILE_SIZE = 16;
constexpr int DEFAULT_MAP_WIDTH = 230;
constexpr int DEFAULT_MAP_HEIGHT = 14;

constexpr int SKY_RED = 90;
constexpr int SKY_GREEN = 147;
constexpr int SKY_BLUE = 254;

constexpr int INTRO_SCREEN_TIME = 130;

constexpr int EDITOR_CAMERA_PAN_SPEED = 3;

// Instantiate ${CAMERA_WORLD_OFFSET} tiles off camera from the left and right
constexpr int CAMERA_WORLD_OFFSET = 4 * TILE_SIZE;

constexpr float GRAVITY = .040;
constexpr float FRICTION = .94;
constexpr float MAX_SPEED_X = 3;
constexpr float MAX_SPEED_Y = 3;

constexpr float MARIO_ACCELERATION_X = .08f;
constexpr float MARIO_JUMP_ACCELERATION = 0.9f;
constexpr float MARIO_BOUNCE = 4.0f; // when jumping on top of enemies
constexpr int TILE_ROUNDNESS = 4;

constexpr float MUSHROOM_GROW_SPEED = .25f;
constexpr float MUSHROOM_MOVE_SPEED = 0.8f;


constexpr	int Meter2Pix = 40; // 1 meter = 20 pixle
const float RAD2DEG = 180 / M_PI;