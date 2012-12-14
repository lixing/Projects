/**
 * File: gblocky.h
 * ---------------
 * Provides the collection of functions needed to render a Blocky board.
 */
 
#ifndef __blocky__graphics__
#define __blocky__graphics__

#include "genlib.h" // provides the definition of the string type

/**
 * Convenience struct: coord
 * -------------------------
 * Simple C++ struct (which is like a class, except there are
 * no methods and everything is public) that bundles two related
 * pieces of data together.
 */

struct coord {
	int row;
	int col;
};

/**
 * The one-time initialization routine that should be called up front
 * to bring up a Blocky-specific graphics window.  It's best to call this
 * before you print anything to cout, and before you call getline, GetLine,
 * GetInteger, or GetReal (or any I/O routine, really).
 */

void InitBlockyGraphics();

/**
 * Establishes that the board dimension from this point forward (until
 * another call to SetBlockyDimension comes along) is number specified.
 * Some constraints:
 *
 *     - SetBlockyDimension can only be called if InitBlockyGraphics has
 *       been called previously.
 *     - The specified dimension absolutely must be between 5 and 25, inclusive.
 *
 * If either or both of these requirements aren't met, the full program exits.
 *
 * @param dimension the dimension of the Blocky board.
 * @return void
 */

void SetBlockyDimension(int dimension);

/**
 * Draws a block of the specified color at the specified row, column pair.
 * The original Boolean expresses whether this is the first time a block has
 * been drawn at the specified location since the last time SetBlockDimension
 * was called.
 *
 * @param color the color that should be used to draw the block.  If the string
 *              isn't recognized by the graphics library as the name of a predefined
 *              color, then the full program will exit.
 * @param row the row of the currently displayed board where the block should be drawn.
 *            The supplied number must be nonnegative and less than the current dimension
 *            of the blocky board, or else the full program will exit.
 * @param col the column of the currently displayed board where the block should be drawn.
 *            The supplied number must be nonnegative and less than the current dimension
 *            of the blocky board, or else the full program will exit.
 * @param firstTime true if the visual of the block is being drawn for the first time at
 *                  this location, and false otherwise.
 * @return void
 */

void DrawBlockAt(string color, int row, int col, bool firstTime = true);

/**
 * Waits for the user to click and drag the mouse over a region of the board.
 * The user must first click the mouse somewhere in the game board, and eventually
 * release the mouse after dragging it define a rectangle of blocks.  If the user
 * clicks somewhere off the board, then that click is rejected and the user must
 * click again (and again, and again) until the click is actually somewhere on the
 * board.  From that first legal click, the implementation does the best job it
 * can to track the location of the mouse while it's being dragged--even when dragged
 * outside the board area.  The lower left coordinates and the upper right coordinate
 * of the selected rectangle are placed in the space identified by reference via the
 * lowerLeft and upperRight parameters.
 *
 * @param lowerLeft a reference to the coord struct where the lower left coordinate of the
 *                  selected rectangle should be placed.
 * @param upperRight a reference to the coord struct where the upper right coordinate of the
 *                   selected rectangle should be placed.
 * @return void
 */

void WaitForUserSelection(coord& lowerLeft, coord& upperRight);

/**
 * Clears whatever selection was made by the most recent call to WaitForUserSelection.
 *
 * @return void
 */
 
void ClearUserSelection();

/**
 * Updates the status message appearing just below the game board.  The status message
 * can be cleared by passing in the empty string.
 *
 * @param message the message to be displayed.  The string should be short enough to
 *        fit in on one line in the space provided.
 * @return void
 */

void DrawStatusMessage(string message);

#endif