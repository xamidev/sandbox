/**
* @file src/main.c
* @brief Sandbox game in Raylib
* 
* @copyright
* Anyone is free to copy, modify, publish, use, compile, sell, or
* distribute this software, either in source code form or as a compiled
* binary, for any purpose, commercial or non-commercial, and by any
* means.
* 
* In jurisdictions that recognize copyright laws, the author or authors
* of this software dedicate any and all copyright interest in the
* software to the public domain. We make this dedication for the benefit
* of the public at large and to the detriment of our heirs and
* successors. We intend this dedication to be an overt act of
* relinquishment in perpetuity of all present and future rights to this
* software under copyright law.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
* 
* For more information, please refer to <https://unlicense.org/>
*/

#include "raylib.h"
#include "cells.h"
#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "utils.h"

/* TODO
- Changing brush size
- Add more elements
- Add an interface
- Saving and loading world (+ better title screen)
*/

int main ()
{
	srand(time(NULL));
	int grid[CELL_AMOUNT][CELL_AMOUNT] = {0};
	GameScreen currentScreen = TITLE;
	CellType brush = SAND;

	initEnv();
	
	// game loop
	while (!WindowShouldClose())
	{
		/* Update */
		switch (currentScreen)
		{
			case TITLE:
				if (IsKeyPressed(KEY_SPACE)) {
					currentScreen = GAME;
					ClearBackground(BLACK);
				}
				break;
			case GAME:
				if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
					Vector2 cellPosition = GetMousePosition();
					int i = cellPosition.y/CELL_SIZE_PIXELS;
					int j = cellPosition.x/CELL_SIZE_PIXELS;
					putCell(grid, i, j, brush);
				}
				if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
					// spawn some text corresponding to Brush Type, fading
					if (brush < CELL_TYPE_MAX-1)
					{
						brush++;
					} else {
						brush = VOID;
					}
					printf("Brush changed for %d\n", brush);
				}
				break;
			default:
				break;
		}

		/* Drawing */
		BeginDrawing();
		ClearBackground(BLACK);
		switch (currentScreen)
		{
			case TITLE:
				drawTitleScreen();
				break;
			case GAME:
				updateGrid(grid);
				drawGrid(grid);
				break;
			default:
				break;
		}
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
