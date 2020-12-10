#include "main.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

bool running = false;

int main (int argc, const char *argv[])
{
	init_graphics();
	init_game();
	running = true;

	#ifdef __EMSCRIPTEN__
		// Implement asynchronous main loop for browser
		// Set fps=0 for browser's "requestAnimationFrame" to call function
		// Set simulate_infinite_loop = 1 (true)
		emscripten_set_main_loop(main_loop, 0, 1);
	#else
		while (running)
		{
			// Invoke main loop
    		main_loop();
		}
	#endif

    atexit(cleanup);
    return 0;
}

void main_loop()
{
	// Set render target to self
	prerender();
	// Poll for user events
	handle_user_events();
	// Update game
	update_game();
	// Render any updates and reset
	update_render();
	// Set SDL delay
	SDL_Delay(16);
}

void cleanup()
{
    cleanup_graphics();
    SDL_Quit();

	#ifdef __EMSCRIPTEN__
		emscripten_cancel_main_loop();
	#endif
}
