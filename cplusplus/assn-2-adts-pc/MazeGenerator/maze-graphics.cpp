/**
 * File: maze-graphics.cpp
 * -----------------------
 * Provides the implementation of the (very primitive)
 * graphics routines needed to help animate the construction
 * of a maze.
 */

#include "maze-graphics.h"
#include "extgraph.h"

/**
 * Global constants that help provide more 
 * meaningful names for what will otherwise be
 * magic values.
 */

static const string kMazeVisibleColor("Blue");
static const string kMazeInvisibleColor("White");
static const double kMazeDimension = 3.75;

/**
 * Internal global variables that help maintain information
 * about the most recently set maze dimension.
 */

static int gDimension;
static double gWallLength;

static double GetMazeLowerLeftX()
{
	double cx = GetWindowWidth()/2;
	return cx - kMazeDimension/2;
}


static double GetMazeLowerLeftY()
{
	double cy = GetWindowHeight()/2;
	return cy - kMazeDimension/2;	
}

void InitMazeGraphics()
{
	SetWindowSize(14.0, 8.0);
	InitGraphics();
}

void SetMazeDimension(int dimension)
{
	gDimension = dimension;
	gWallLength = kMazeDimension / dimension;
}

static void DrawWallUsingColor(wall w, string color)
{
	double startx = GetMazeLowerLeftX() + w.one.col * gWallLength;
	double starty = GetMazeLowerLeftY() + w.one.row * gWallLength;
	
	double wallLength = gWallLength;
	if (color == kMazeInvisibleColor) {
		wallLength *= 0.6;
	}
	
	SetPenColor(color);
	if (w.one.row == w.two.row) {
		startx += gWallLength;
		if (color == kMazeInvisibleColor) 
			starty += gWallLength / 5;
		MovePen(startx, starty);
		DrawLine(0, wallLength);
	} else {
		starty += gWallLength;
		if (color == kMazeInvisibleColor) 
			startx += gWallLength / 5;
		MovePen(startx, starty);
		DrawLine(wallLength, 0);
	}
}

static void DrawLine(double dx, double dy, string color)
{
	SetPenColor(color);
	DrawLine(dx, dy);
}

void DrawMazeBorder()
{
	double llx = GetMazeLowerLeftX();
	double lly = GetMazeLowerLeftY();
	
	MovePen(llx, lly);
	DrawLine(0, kMazeDimension, kMazeVisibleColor);
	DrawLine(gWallLength, 0, kMazeInvisibleColor);
	DrawLine(kMazeDimension - gWallLength, 0, kMazeVisibleColor);
	DrawLine(0, -kMazeDimension, kMazeVisibleColor);
	DrawLine(- gWallLength, 0, kMazeInvisibleColor);
	DrawLine(- kMazeDimension + gWallLength, 0, kMazeVisibleColor);	
}

void DrawCell(cell c, string color)
{
	double inset = gWallLength / 5;
	double startx = GetMazeLowerLeftX() + c.col * gWallLength + inset;
	double starty = GetMazeLowerLeftY() + c.row * gWallLength + inset;
	SetPenColor(color);
	MovePen(startx, starty);
	StartFilledRegion(0.9);
	double insetWallLength = gWallLength - 2 * inset;
	DrawLine(insetWallLength, 0);
	DrawLine(0, insetWallLength);
	DrawLine(-insetWallLength, 0);
	DrawLine(0, -insetWallLength);
	EndFilledRegion();
}

void DrawWall(wall w)
{
	DrawWallUsingColor(w, kMazeVisibleColor);
}

void RemoveWall(wall w)
{
	DrawWallUsingColor(w, kMazeInvisibleColor);
}
