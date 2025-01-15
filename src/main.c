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
	int brushSize = 1;
	int brushTextOpacity = 255;
	int brushSizeOpacity = 255;
	char blankStr[10] = {0};

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
					putCell(grid, i, j, brush, brushSize);
				}
				if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
					// spawn some text corresponding to Brush Type, fading
					if (brush < CELL_TYPE_MAX-1)
					{
						brush++;
					} else {
						brush = VOID;
					}
					brushTextOpacity = 255;
				}
				if (IsKeyPressed(KEY_UP) && brushSize < CELL_AMOUNT) {
					brushSize++;
					brushSizeOpacity = 255;
				}
				if (IsKeyPressed(KEY_DOWN) && brushSize > 1) {
					brushSize--;
					brushSizeOpacity = 255;
				}
				if (IsKeyPressed(KEY_C)) {
					clearGrid(grid);
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
				Vector2 mousePos = GetMousePosition();
				DrawText(enumToString(brush), mousePos.x+15, mousePos.y+15, DEFAULT_FONT_SIZE, (Color){255, 255, 255, brushTextOpacity});
				DrawText(intToString(blankStr, brushSize), mousePos.x-15, mousePos.y-15, DEFAULT_FONT_SIZE, (Color){255, 255, 255, brushSizeOpacity});
				if (brushTextOpacity-4 > 0) brushTextOpacity-= 4;
				if (brushSizeOpacity-4 > 0) brushSizeOpacity-= 4;
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
