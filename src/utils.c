/**
* @file src/utils.c
* @brief Miscellaneous utilities for sandbox
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

void initEnv(void)
{
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(WINDOW_SIZE_PIXELS, WINDOW_SIZE_PIXELS, "Sandbox");
	SetTargetFPS(TARGET_FPS);
}

void drawTitleScreen(void)
{
    int titleWidth = MeasureText("SANDBOX", 40);
	DrawRectangle(0, 0, WINDOW_SIZE_PIXELS, WINDOW_SIZE_PIXELS, DARKBLUE);
	DrawText("SANDBOX", (WINDOW_SIZE_PIXELS-titleWidth)/2, 20, 40, WHITE);
	int controlsWidth = MeasureText("Controls", 30);
	DrawText("Controls", (WINDOW_SIZE_PIXELS-controlsWidth)/2, 100, 30, WHITE);
	DrawText("Left click to spawn sand", 25, 150, 30, WHITE);
	int startGameWidth = MeasureText("Press Space to start!", 30);
	DrawText("Press Space to start!", (WINDOW_SIZE_PIXELS-startGameWidth)/2, 400, 30, WHITE);
}