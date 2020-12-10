#include "graphics.h"

void init_graphics()
{
    render_changed = false;

	// Init SDL library
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
        printf("SDL_Init Error:  %s\n", SDL_GetError());
        exit(1);
    }

	// Create window
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error:  %s\n", SDL_GetError());
        exit(1);
    }

	// Create window renderer
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (render == NULL) {
        printf("SDL_CreateRenderer Error:  %s\n", SDL_GetError());
        exit(1);
    }

    // Create texture for render context
    display = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (display == NULL)
    {
        printf( "SDL_CreateTexture Error: %s\n", SDL_GetError());
		exit(1);
	}

	// Make self render target
    SDL_SetRenderTarget(render, display);
}

void set_render_changed()
{
    render_changed = true;
}

void prerender()
{
	// Make self render target
    SDL_SetRenderTarget(render, display);
}

void update_render()
{
    if (render_changed)
	{
		// Reset render target
        SDL_SetRenderTarget(render, NULL);
		// Render display, NULL for source and destination to set default
        SDL_RenderCopy(render, display, NULL, NULL);
		// Render paint updates
        SDL_RenderPresent(render);
		// Reset render_changed bool
        render_changed = false;
    }
}

void draw_block(uint8_t x, uint8_t y, uint32_t color)
{
    // assert(x >= 0 && x < WINDOW_WIDTH);
    // assert(y >= 0 && y < WINDOW_HEIGHT);

    // top-left coords of block
    uint16_t x_tl = x * (BLOCK_SIZE + 1) + 1;
    uint16_t y_tl = y * (BLOCK_SIZE + 1) + 1;

    // top-right coords of block
    // uint16_t x_tr = x_tl + BLOCK_SIZE;
    // uint16_t y_tr = y_tl;

    // bottom-right coords of block
    uint16_t x_br = x_tl + BLOCK_SIZE;
    uint16_t y_br = y_tl + BLOCK_SIZE;

    // bottom-left coords of block
    // uint16_t x_bl = x_tl;
    // uint16_t y_bl = y_tl + BLOCK_SIZE;

    boxColor(render, x_tl, y_tl, x_br, y_br, color);

    // draw grid lines

    // if(y <= 0) {
    //     // draw top horizontal grid line (from top-left to top-right)
    //     aalineRGBA(render, x_tl, y_tl, x_tr, y_tr, 187, 173, 160, 255);
    // }

    // if(x <= 0) {
    //     // draw left vertical grid line (from top-left to bottom-left)
    //     aalineRGBA(render, x_tl, y_tl, x_bl, y_bl, 187, 173, 160, 255);
    // }

    // // draw bottom horizontal grid line (from bottom-left to bottom-right)
    // aalineRGBA(render, x_bl, y_bl, x_br, y_br, 187, 173, 160, 255);

    // // draw right vertical grid line (from top-right to bottom-right)
    // aalineRGBA(render, x_tr, y_tr, x_br, y_br, 187, 173, 160, 255);

    set_render_changed();

}

void cleanup_graphics()
{
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
}
