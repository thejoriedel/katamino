#include "defs.h"
#include "graphics.h"


#ifndef _GAME_CONSTANTS
#define _GAME_CONSTANTS

typedef struct {
    // Array of hexadecimal representations of rotations
    uint16_t rotation[4];
    // RGBA convention: 0xAABBGGRR
    uint32_t color;

} Pentamino;

typedef struct {
	// Type of pentamino
    Pentamino type;
    // Index of rotation scheme
    uint8_t rotation;
	// X coorrdinate
    uint8_t x;
	// Y coordinate
    uint8_t y;

} Pentamino_Movement;

typedef struct {
	// Pentamino type, rotation, and coordinates
    Pentamino_Movement mino;
	// Current coordinates of the pentamino
    uint16_t current_coords[10];

} Mino;

typedef enum {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SPACE,
    TAB,
    RESTART,
    MOUSEMOTION,
    MOUSEUP,
    MOUSEDOWN
} Action;

typedef enum {
    EMPTY = 0xFFF5F5F5,
    TEAL = 0xFFD97400,
    BLUE = 0xFFFFDB7F,
    ORANGE = 0XFF1B85FF,
    YELLOW = 0xFF00DCFF,
    GREEN = 0xFF40CC2E,
    PURPLE = 0xFF4B1485,
	GRAY = 0xFFA0A0A0,
	PINK = 0xFFE97CC9,
	BROWN = 0xFF9E6230

} Color_Block;

// SDL_Point mousePos;
// SDL_Point clickOffset;
static bool leftMouseButtonDown = false;
static Mino *SELECTED_MINO = NULL;

static Action USER_EVENT;

// Mino rotation and color data
// Values are stored as hexadecimal representations of binary digits,
// i.e., 0xEC0 = 0000111011000000 which represents the below pentamino
// [[0000]
//  [0011]
//  [0111]
//  [0000]]

const static Pentamino PENTA_G = {
	{0x2E4, 0xC64, 0x4E8, 0x4C6},
	GRAY
};

const static Pentamino PENTA_U = {
  	{0xC8C, 0xEA0, 0x626, 0xAE},
	YELLOW
};

const static Pentamino PENTA_P = {
	{0x662, 0x6E, 0x8CC, 0xEC0},
	PINK
};

const static Pentamino PENTA_B = {
	{0x4F0, 0x2262, 0xF20, 0x4644},
	BROWN
};

const static Pentamino PENTA_T = {
    {0x44E0, 0x4740, 0x7220, 0x2E20},
    GREEN
};

const static Pentamino PENTA_L = {
	{0xE88, 0xE22, 0x22E, 0x88E},
    BLUE
};

const static Pentamino PENTA_J = {
	{0x4446, 0xF80, 0x6222, 0x1F0},
    ORANGE
};

// Pointer to the current pentamino
static Mino *current_mino;
// Current pentamino index in game set of minos
static uint8_t current_mino_index = 0;
// Game set of pentaminos
static Mino penta[3];
// Board array
static Color_Block board[BOARD_HEIGHT * BOARD_WIDTH];

#endif

void draw_game();
Color_Block get_board(uint8_t x, uint8_t y);
void set_board(uint8_t x, uint8_t y, Color_Block color);

void init_game();
void update_game();

bool render_current_mino();
bool mouse_in_mino(SDL_Point mouse, uint8_t mino_coords[]);
bool can_render_mino(uint16_t render_queue[]);
void handle_user_events();


