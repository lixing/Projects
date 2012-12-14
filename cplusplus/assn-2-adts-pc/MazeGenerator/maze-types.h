/**
 * File: maze-types.h
 * ------------------
 * Provides the definitions of the cell and wall types used in the 
 * code base.  They're defined here in a separate file so that they
 * can shared by the system.
 */

#ifndef __maze_types__
#define __maze_types__
#include "genlib.h"

/**
 * Defines a positive integer coordinate in 2D space, where we
 * (arbitrarily) impose the requirement that (0, 0)
 * is below and/or to the left of all others.
 */

struct cell {
	int row;
	int col;
	
	// you can ignore these two lines... they're advanced C++ that allows a programmer to
	// compare two cells using == and <.
	friend bool operator==(const cell& one, const cell& two) { return one.row == two.row && one.col == two.col; }
	friend bool operator<(const cell& one, const cell& two) { return one.row < two.row || (one.row == two.row && one.col < two.col); }
};

/**
 * A wall within a maze is described by the two cells
 * it separates.  It's the responsibility of the programmer
 * to ensure that the two cells are really next to one another,
 * and that the two cells are sensibly ordered.
 */

struct wall {
	cell one;
	cell two;
};

#endif
