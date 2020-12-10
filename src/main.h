#include "defs.h"
#include "graphics.h"
#include "game.h"

SDL_Window *window;
SDL_Renderer *render;
SDL_Texture *display;

bool render_changed;
void main_loop();
void cleanup();
