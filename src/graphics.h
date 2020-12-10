#include "defs.h"

extern SDL_Window *window;
extern SDL_Renderer *render;
extern SDL_Texture *display;

extern bool render_changed;

void init_graphics();
void cleanup_graphics();

void draw_block(uint8_t x, uint8_t y, uint32_t color);

void set_render_changed();
void prerender();
void update_render();

