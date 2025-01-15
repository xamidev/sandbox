/**
* @file src/cells.h
* @brief Cell logic header
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

#ifndef CELLS_H
#define CELLS_H

#define TARGET_FPS          60

#define CELL_SIZE_PIXELS    10
#define WINDOW_SIZE_PIXELS  800

#define CELL_AMOUNT         (WINDOW_SIZE_PIXELS/CELL_SIZE_PIXELS)
#define DEFAULT_FONT_SIZE   20

#define YELLOW_SAND         CLITERAL(Color){222, 233, 129, 255}
#define YELLOW_SAND_ALT     CLITERAL(Color){166, 172, 116, 255}

typedef enum GameScreen 
{
    TITLE,
    GAME
} GameScreen;

typedef enum CellType
{
    VOID,
    SAND,
    STONE,
    WATER,
    CELL_TYPE_MAX
} CellType;

void drawGrid(int grid[CELL_AMOUNT][CELL_AMOUNT]);
void putCell(int grid[CELL_AMOUNT][CELL_AMOUNT], int posX, int posY, CellType brush, int brushSize);
void updateGrid(int grid[CELL_AMOUNT][CELL_AMOUNT]);
void clearGrid(int grid[CELL_AMOUNT][CELL_AMOUNT]);

#endif // CELLS_H