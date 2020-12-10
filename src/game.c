#include "game.h"

void init_game() {

    USER_EVENT = 0;

    // Empty the board
    int i = BOARD_HEIGHT * BOARD_WIDTH;
    while (i --> 0) {
        board[i] = EMPTY;
    }

    draw_game();

	// TODO: Randomize penta sets on init
	Pentamino_Movement PentaA[] = {
		{PENTA_J,0,10,10},
		{PENTA_B,0,20,15},
		{PENTA_T,0,6,8},
	};

	Pentamino_Movement PentaC[] = {
		{PENTA_J,0,18,12},
		{PENTA_L,0,7,15},
		{PENTA_P,0,3,0},
	};

	Pentamino_Movement PentaD[] = {
		{PENTA_B,0,12,10},
		{PENTA_P,0,20,3},
		{PENTA_U,0,8,8},
	};

	Pentamino_Movement PentaF[] = {
		{PENTA_P,0,7,11},
		{PENTA_U,0,11,15},
		{PENTA_G,0,19,5},
	};

	Pentamino_Movement PentaG[] = {
		{PENTA_J,0,20,10},
		{PENTA_L,0,20,15},
		{PENTA_P,0,6,0},
	};
	// Initialize pentaminos and coordinates
    int k = 3;
	while (k --> 0)
	{
		Mino SetMino = {PentaF[k], {0}};
		penta[k] = SetMino;
	}
	// Render initial pentaminos
	int l = 3;
	while (l --> 0)
	{
		current_mino = &penta[l];
		current_mino_index = l;
		render_current_mino();
	}
}

void handle_user_events() {
    SDL_Event event;
    // Poll for user events
    while (SDL_PollEvent(&event))
	{
        switch (event.type)
		{
            case SDL_QUIT:
                exit(0);
            break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
				{
                    case SDLK_ESCAPE:
                        exit(0);
                    break;

                    case SDLK_s:
                    case SDLK_DOWN:
                        USER_EVENT = DOWN;
                    break;

                    case SDLK_d:
                    case SDLK_RIGHT:
                        USER_EVENT = RIGHT;
                    break;

                    case SDLK_a:
                    case SDLK_LEFT:
                        USER_EVENT = LEFT;
                    break;

                    case SDLK_w:
                    case SDLK_UP:
                        USER_EVENT = UP;
                    break;

                    case SDLK_r:
                        USER_EVENT = RESTART;
                    break;

                    case SDLK_SPACE:
                        USER_EVENT = SPACE;
                    break;

					case SDLK_TAB:
						USER_EVENT = TAB;
					break;

                    default:
                    break;
                }
            break;

            case SDL_KEYUP:
                USER_EVENT = NONE;
            break;

            case SDL_MOUSEMOTION:
				USER_EVENT = MOUSEMOTION;
				// mousePos.x = event.motion.x;
				// mousePos.y = event.motion.y;
			break;

			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					USER_EVENT = MOUSEUP;
				}
			break;

			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					USER_EVENT = MOUSEDOWN;
				}
			break;

            default:
            break;
        }
    }
}

void draw_game() {
    // Set rendering clear background color
    SDL_SetRenderDrawColor(render, 245, 245, 245, SDL_ALPHA_OPAQUE);
    // Clear render, set background color defined in SDL_SetRenderDrawColor
    SDL_RenderClear(render);

    int i = BOARD_HEIGHT * BOARD_WIDTH;
    while (i --> 0)
        set_board(i % BOARD_WIDTH, i / BOARD_WIDTH, board[i]);

    // Update the screen
    set_render_changed();
}

void update_game() {
    // Check user action
    switch(USER_EVENT) {

		case NONE:
		break;

        case LEFT:
			// Decrement pentamino y
            current_mino->mino.x -= 1;
            render_current_mino();
        break;

        case RIGHT:
			// Increment pentamino x
            current_mino->mino.x += 1;
            render_current_mino();
        break;

		case UP:
			// Decrement pentamino y
            current_mino->mino.y -= 1;
            render_current_mino();
        break;

        case DOWN:
			// Increment pentamino y
            current_mino->mino.y += 1;
            render_current_mino();
        break;

        case SPACE:
			// Set rotation to next in array
			current_mino->mino.rotation = (current_mino->mino.rotation + 1) % 4;
            render_current_mino();
        break;

        case RESTART:
			// Restart the game
            init_game();
        break;

		case TAB:
			// Increment current mino index
			current_mino_index++;
			if (current_mino_index > 2)
			{
				current_mino_index = 0;
			}
			// Assign next pentamino in set as current
			current_mino = &penta[current_mino_index];
		break;
		// TODO: Explore adding mouse events
		case MOUSEMOTION:
			// if (leftMouseButtonDown && SELECTED_MINO != NULL)
			// {
			// 	SELECTED_MINO->mino.x = mousePos.x - clickOffset.x;
			// 	SELECTED_MINO->mino.y = mousePos.y - clickOffset.y;
			// 	render_current_mino(*SELECTED_MINO, current_mino_index);
			// }
		break;

		case MOUSEUP:
			leftMouseButtonDown = false;
			SELECTED_MINO = NULL;
		break;

		case MOUSEDOWN:
			// if (!leftMouseButtonDown)
			// {
			// 	leftMouseButtonDown = true;
			// 	if (mouse_in_mino(mousePos, CURRENT_MINO_COORDS))
			// 	{
			// 		SELECTED_MINO = &current_mino;
			// 		clickOffset.x = mousePos.x - current_mino.mino.x;
			// 		clickOffset.y = mousePos.y - current_mino.mino.y;
			// 		break;
			// 	}
			// }
		break;
    }
    USER_EVENT = 0;
}

bool can_render_mino(uint16_t render_queue[]) {
    uint16_t bit, piece;
    uint16_t row = 0, col = 0;

	piece = current_mino->mino.type.rotation[current_mino->mino.rotation];
    uint16_t x = current_mino->mino.x;
    uint16_t y = current_mino->mino.y;

    // Iterate through pentamino data, get coordinates for rotation
    int i = 0;
    for (bit = 0x8000; bit > 0 && i < 10; bit = bit >> 1) {
        if (piece & bit) {
            uint16_t _x = x + col;
            uint16_t _y = y + row;

			if (get_board(_x, _y) != EMPTY)
			{
				return false;
				break;
			}

			if (render_queue != NULL) {
				render_queue[i * 2] = _x;
				render_queue[i * 2 + 1] = _y;
			}

			i++;
        }
        col++;
        col = col % 4;
        if (col == 0)
		{
            row++;
        }
    }
    return true;
}

bool render_current_mino() {

    uint16_t render_queue[10] = {0};

    if (!can_render_mino(render_queue))
	{
        return false;
	}

    // Clear previous pentamino position
    int i = 5;
    while(i --> 0) {
        uint8_t x_coord = i * 2;
        uint8_t y_coord = x_coord + 1;

        uint8_t _x = current_mino->current_coords[x_coord];
        uint8_t _y = current_mino->current_coords[y_coord];

        draw_block(_x, _y, EMPTY);
    }

    // Draw new pentamino squares
    i = 5;
    while(i --> 0) {

        uint8_t x_coord = i * 2;
        uint8_t y_coord = x_coord + 1;

        // store and draw new Pentamino position
        uint8_t _x = render_queue[x_coord];
        uint8_t _y = render_queue[y_coord];

        current_mino->current_coords[x_coord] = _x;
        current_mino->current_coords[y_coord] = _y;

        draw_block(_x, _y, current_mino->mino.type.color);
    }

    return true;
}

Color_Block get_board(uint8_t x, uint8_t y)
{
    return board[(y * BOARD_WIDTH) + x];
}

void set_board(uint8_t x, uint8_t y, Color_Block color)
{
    board[(y * BOARD_WIDTH) + x] = color;
    draw_block(x, y, color);
}

bool mouse_in_mino(SDL_Point mouse, uint8_t mino_coords[])
{
	// Check if mouse position is within pentamino
    int i = 5;
    while(i --> 0) {
        uint8_t x_coord = i * 2;
        uint8_t y_coord = x_coord + 1;

        uint8_t _x = mino_coords[x_coord];
        uint8_t _y = mino_coords[y_coord];

		uint16_t x_tl = _x * (BLOCK_SIZE + 1) + 1;
		uint16_t y_tl = _y * (BLOCK_SIZE + 1) + 1;

		uint16_t x_tr = x_tl + BLOCK_SIZE;

		uint16_t y_bl = y_tl + BLOCK_SIZE;

		if ((mouse.x > x_tl && mouse.x < x_tr) && (mouse.y > y_tl && mouse.y < y_bl))
		{
			return true;
		}
    }
    return false;
}



