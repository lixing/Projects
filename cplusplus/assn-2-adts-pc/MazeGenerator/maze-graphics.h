/**
 * File: maze-graphics.h
 * ---------------------
 * Last modified: jcain 9/26/09
 */

#ifndef __maze_graphics__
#define __maze_graphics__
#include "maze-types.h"
#include <string>
#include "genlib.h"

/**
 * Function: InitMazeGraphics
 * --------------------------
 * InitMazeGraphics presents a clear graphics window (or clears an existing
 * one) so that calls to DrawMazeBorder and DrawWall can be made to help animate
 * the construction of a simple maze.
 *
 * @return void
 */

void InitMazeGraphics();

/**
 * Sets the dimension of the maze.
 *
 * @param int dimension the number of cells in each dimension.
 *        All mazes are understood to be square, so the supplied
 *        dimension describe both the number of rows and the number
 *        of columns.
 * @return void
 */

void SetMazeDimension(int dimension);

/**
 * DrawMazeBorder draws the circumference of the maze.
 *
 * @return void
 */

void DrawMazeBorder();

/**
 * Draws a wall such that the two cells within w are
 * separated.
 *
 * @param wall w the wall to be drawn.
 * @return void
 */

void DrawWall(wall w);

/**
 * Removes the specified wall so that the two cells
 * within w are part of the same chamber.
 *
 * @param wall the wall to be removed.
 * @return void
 */

void RemoveWall(wall w);

#endif
