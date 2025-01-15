/**
* @file src/cells.c
* @brief Cell logic implementation
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

#include <stdio.h>
#include "cells.h"
#include "raylib.h"

void drawGrid(int grid[CELL_AMOUNT][CELL_AMOUNT])
{
    for (size_t i=0; i<CELL_AMOUNT; i++)
    {
        for (size_t j=0; j<CELL_AMOUNT; j++)
        {
            switch(grid[i][j])
            {
                case VOID:
                    DrawRectangle(CELL_SIZE_PIXELS*j, CELL_SIZE_PIXELS*i, CELL_SIZE_PIXELS, CELL_SIZE_PIXELS, BLACK);
                    break;
                case SAND:
                    DrawRectangle(CELL_SIZE_PIXELS*j, CELL_SIZE_PIXELS*i, CELL_SIZE_PIXELS, CELL_SIZE_PIXELS, YELLOW_SAND);
                    break;
                case STONE:
                    DrawRectangle(CELL_SIZE_PIXELS*j, CELL_SIZE_PIXELS*i, CELL_SIZE_PIXELS, CELL_SIZE_PIXELS, DARKGRAY);
                default:
                    break;
            }
        }
    }
}

void putCell(int grid[CELL_AMOUNT][CELL_AMOUNT], int posX, int posY, CellType brush)
{
    if (grid[posX][posY] == VOID)
    {
        grid[posX][posY] = brush;
    }
}

void updateGrid(int grid[CELL_AMOUNT][CELL_AMOUNT])
{
    for (int i=CELL_AMOUNT-1; i>=0; i--)
    {
        for (int j=0; j<CELL_AMOUNT; j++)
        {
            switch (grid[i][j])
            {
                case VOID:
                    break;
                case SAND:
                    if (i+1 < CELL_AMOUNT && grid[i+1][j] == VOID) {
                        grid[i][j] = VOID;
                        grid[i+1][j] = SAND; // falling downwards
                    } else if (i+1 < CELL_AMOUNT && j+1 < CELL_AMOUNT && grid[i+1][j+1] == VOID) {
                        grid[i][j] = VOID;
                        grid[i+1][j+1] = SAND; // falling down-right
                    }
                    else if (i+1 < CELL_AMOUNT && j-1 >= 0 && grid[i+1][j-1] == VOID) {
                        grid[i][j] = VOID;
                        grid[i+1][j-1] = SAND; // falling down-left
                    }
                    break;
                default:
                    break;
            }
        }
    }
}