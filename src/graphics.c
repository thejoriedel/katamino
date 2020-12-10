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

    if (window == NULL)
	{
        fprintf(stderr, "SDL_CreateWindow Error:  %s\n", SDL_GetError());
        exit(1);
    }

	// Create window renderer
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (render == NULL)
	{
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
    uint16_t x_top_left = x * (BLOCK_SIZE + 1) + 1;
    uint16_t y_top_left = y * (BLOCK_SIZE + 1) + 1;

    uint16_t x_bottom_right = x_top_left + BLOCK_SIZE;
    uint16_t y_bottom_right = y_top_left + BLOCK_SIZE;

    boxColor(render, x_top_left, y_top_left, x_bottom_right, y_bottom_right, color);
    set_render_changed();
}

void cleanup_graphics()
{
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
}
