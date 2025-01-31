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
#include <stdlib.h>

void drawGrid(int grid[CELL_AMOUNT][CELL_AMOUNT])
{
    for (size_t i=0; i<CELL_AMOUNT; i++)
    {
        for (size_t j=0; j<CELL_AMOUNT; j++)
        {
            switch(grid[i][j])
            {
                /* Cell drawing colors */
                case VOID:
                    DrawRectangle(CELL_SIZE_PIXELS*j, CELL_SIZE_PIXELS*i, CELL_SIZE_PIXELS, CELL_SIZE_PIXELS, BLACK);
                    break;
                case SAND:
                    DrawRectangle(CELL_SIZE_PIXELS*j, CELL_SIZE_PIXELS*i, CELL_SIZE_PIXELS, CELL_SIZE_PIXELS, YELLOW_SAND);
                    break;
                case STONE:
                    DrawRectangle(CELL_SIZE_PIXELS*j, CELL_SIZE_PIXELS*i, CELL_SIZE_PIXELS, CELL_SIZE_PIXELS, DARKGRAY);
                    break;
                case WATER:
                    DrawRectangle(CELL_SIZE_PIXELS*j, CELL_SIZE_PIXELS*i, CELL_SIZE_PIXELS, CELL_SIZE_PIXELS, BLUE);
                    break;
                case VIRUS:
                    DrawRectangle(CELL_SIZE_PIXELS*j, CELL_SIZE_PIXELS*i, CELL_SIZE_PIXELS, CELL_SIZE_PIXELS, VIOLET);
                    break;
                case PLANT:
                    DrawRectangle(CELL_SIZE_PIXELS*j, CELL_SIZE_PIXELS*i, CELL_SIZE_PIXELS, CELL_SIZE_PIXELS, DARKGREEN);
                    break;
                default:
                    break;
            }
        }
    }
}

void putCell(int grid[CELL_AMOUNT][CELL_AMOUNT], int posX, int posY, CellType brush, int brushSize)
{
    if (grid[posX][posY] == VOID || grid[posX][posY] == brush)
    {
        for (int i=0; i<brushSize; i++)
        {
            for (int j=0; j<brushSize; j++)
            {
                if (posX+i < CELL_AMOUNT && posY+j < CELL_AMOUNT) {
                    grid[posX+i][posY+j] = brush;
                }
            }
        }
    }
    else if (brush == VOID) {
        for (int i=0; i<brushSize; i++)
        {
            for (int j=0; j<brushSize; j++)
            {
                if (posX+i < CELL_AMOUNT && posY+j < CELL_AMOUNT) {
                    grid[posX+i][posY+j] = brush;
                }
            }
        }
    }
}

void updateGrid(int grid[CELL_AMOUNT][CELL_AMOUNT]) {
    for (int i = CELL_AMOUNT - 1; i >= 0; i--) {
        for (int j = 0; j < CELL_AMOUNT; j++) {
            switch (grid[i][j]) {
                /* Cell type behavior */
                case VOID:
                    break;
                case SAND:
                    if (i + 1 < CELL_AMOUNT && grid[i + 1][j] == VOID) {
                        grid[i][j] = VOID;
                        grid[i + 1][j] = SAND;
                    } else if (i + 1 < CELL_AMOUNT && j + 1 < CELL_AMOUNT && grid[i + 1][j + 1] == VOID) {
                        grid[i][j] = VOID;
                        grid[i + 1][j + 1] = SAND;
                    } else if (i + 1 < CELL_AMOUNT && j - 1 >= 0 && grid[i + 1][j - 1] == VOID) {
                        grid[i][j] = VOID;
                        grid[i + 1][j - 1] = SAND;
                    } else if (i + 1 < CELL_AMOUNT && grid[i + 1][j] == WATER) {
                        grid[i][j] = WATER;
                        grid[i + 1][j] = SAND;
                    }
                    break;
                case WATER:
                    if (i + 1 < CELL_AMOUNT && grid[i + 1][j] == VOID) {
                        grid[i][j] = VOID;
                        grid[i + 1][j] = WATER;
                    } else if (i + 1 < CELL_AMOUNT && j + 1 < CELL_AMOUNT && grid[i + 1][j + 1] == VOID) {
                        grid[i][j] = VOID;
                        grid[i + 1][j + 1] = WATER;
                    } else if (i + 1 < CELL_AMOUNT && j - 1 >= 0 && grid[i + 1][j - 1] == VOID) {
                        grid[i][j] = VOID;
                        grid[i + 1][j - 1] = WATER;
                    } else {
                        int direction = rand() % 2 == 0 ? -1 : 1;
                        if (j + direction >= 0 && j + direction < CELL_AMOUNT && grid[i][j + direction] == VOID) {
                            grid[i][j] = VOID;
                            grid[i][j + direction] = WATER;
                        }
                    }
                    break;
                case VIRUS: /* It should not be too powerful. */
                    if (i + 1 < CELL_AMOUNT && grid[i+1][j] != VOID && grid[i+1][j] != VIRUS) {
                        int propagate = rand() % 10 == 0 ? 1 : 0;
                        if (propagate) grid[i+1][j] = VIRUS;
                    }
                    else if (i - 1 >= 0 && grid[i-1][j] != VOID && grid[i-1][j] != VIRUS) {
                        int propagate = rand() % 10 == 0 ? 1 : 0;
                        if (propagate) grid[i-1][j] = VIRUS;
                    }
                    else if (j+1 < CELL_AMOUNT && grid[i][j+1] != VOID && grid[i][j+1] != VIRUS) {
                        int propagate = rand() % 10 == 0 ? 1 : 0;
                        if (propagate) grid[i][j+1] = VIRUS;
                    }
                    else if (j-1 >= 0 && grid[i][j-1] != VOID && grid[i][j-1] != VIRUS) {
                        int propagate = rand() % 10 == 0 ? 1 : 0;
                        if (propagate) grid[i][j-1] = VIRUS;
                    }
                    break;
                    case PLANT:
                        if (i+1 < CELL_AMOUNT && grid[i+1][j] == WATER) {
                            int grow = rand() % 600 == 0 ? 1 : 0;
                            if (grow) grid[i+1][j] = PLANT;
                        }
                        if (i-1 >= 0 && grid[i-1][j] == WATER) {
                            int grow = rand() % 20 == 0 ? 1 : 0;
                            if (grow) grid[i-1][j] = PLANT;
                        }
                        if (j+1 < CELL_AMOUNT && grid[i][j+1] == WATER) {
                            int grow = rand() % 600 == 0 ? 1 : 0;
                            if (grow) grid[i][j+1] = PLANT;
                        }
                        if (j-1 >= 0 && grid[i][j-1] == WATER) {
                            int grow = rand() % 600 == 0 ? 1 : 0;
                            if (grow) grid[i][j-1] = PLANT;
                        }
                        break;
                default:
                    break;
            }
        }
    }
}

void clearGrid(int grid[CELL_AMOUNT][CELL_AMOUNT])
{
    for (size_t i=0; i<CELL_AMOUNT; i++)
    {
        for (size_t j=0; j<CELL_AMOUNT; j++)
        {
            grid[i][j] = VOID;
        }
    }
}