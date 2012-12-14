#include "extgraph.h"
#include "gblocky.h"
#include <cmath>

/**
 * Provides the implementation of the UI functions in place 
 * for Blocky to work.  You can ignore more or less everything
 * about this file.  It just needs to be in your XCode project
 * or your Visual Studio solution in order for this all to work.
 */

static const double kFullBlockyWindowWidth = 7.0;
static const double kFullBlockyWindowHeight = 7.0;
static const double kGridWidth = 4.5;
static const double kGridHeight = kGridWidth;
static const double kGridPadding = 0.5;
static const double kGridLowerLeftX = (kFullBlockyWindowWidth - kGridWidth)/2;
static const double kGridLowerLeftY = kFullBlockyWindowHeight - kGridPadding - kGridHeight;
static const double kMessageCenterX = kFullBlockyWindowWidth/2;
static const double kMessageCenterY = kGridLowerLeftY - kGridPadding/2;
static int boardDimension = 5;

static void DrawBox(string color, double llx, double lly, double width, double height)
{
	SetPenColor(color);
	MovePen(llx, lly);
	DrawLine(width, 0);
	DrawLine(0, height);
	DrawLine(-width, 0);
	DrawLine(0, -height);
}

static void DrawFilledBox(string borderColor, string fillColor,
						  double llx, double lly, double width, double height)
{
	StartFilledRegion(1.0);
	DrawBox(fillColor, llx, lly, width, height);
	EndFilledRegion();
	DrawBox(borderColor, llx, lly, width, height);
}

static void DefineColors()
{
	DefineColor("Violet", 0.7, 0.0, 1.0);
	DefineColor("Light Red", 1.0, 0.9, 0.9);
	DefineColor("Light Green", 0.9, 1.0, 0.9);
	DefineColor("Light Blue", 0.9, 0.9, 1.0);
	DefineColor("Light Yellow", 1.0, 1.0, 0.9);
	DefineColor("Light Cyan", 0.9, 1.0, 1.0);
	DefineColor("Light Violet", 0.9, 0.7, 1.0);
	DefineColor("Light White", 1.0, 1.0, 1.0);
}

void InitBlockyGraphics()
{
	SetWindowTitle("Blocky!");
	SetWindowSize(7.0, 7.0);
	InitGraphics();
	DefineColors();
	SetFont("Palatino");
	SetPointSize(14);
	SetStyle(Bold);
}

void SetBlockyDimension(int dimension)
{
	if (dimension <= 4) Error("Too small a dimension passed to SetBlockyDimension.  Exiting...");
	if (dimension >= 26) Error("Too large a dimension passed to SetBlockyDimension.  Exiting...");
	boardDimension = dimension;
	DrawFilledBox("White", "White", 0.0, 0.0, kFullBlockyWindowWidth, kFullBlockyWindowHeight);
	DrawFilledBox("Gray", "White", kGridLowerLeftX, kGridLowerLeftY, kGridWidth, kGridHeight);
}

static const double kPercentOccupancy = 0.90;
static const double kPercentOccupancyWithinBlock = 0.20;
void DrawBlockAt(string color, int row, int col, bool original)
{
	double blockSize = kGridHeight / boardDimension;
	double llx = kGridLowerLeftX + col * blockSize;
	double lly = kGridLowerLeftY + row * blockSize;
	DrawFilledBox("White", "White", llx, lly, blockSize, blockSize);
	llx += (1.00 - kPercentOccupancy) * blockSize / 2;
	lly += (1.00 - kPercentOccupancy) * blockSize / 2;
	blockSize *= kPercentOccupancy;
	DrawFilledBox("Light Gray", color, llx, lly, blockSize, blockSize);
	if (!original || color == "White") return;
	color = "Light " + color;
	llx += (1.00 - kPercentOccupancyWithinBlock) * blockSize / 2;
	lly += (1.00 - kPercentOccupancyWithinBlock) * blockSize / 2;
	blockSize *= kPercentOccupancyWithinBlock;
	DrawFilledBox("Light Gray", color, llx, lly, blockSize, blockSize);
}

static bool OnGrid(const coord& c)
{
	return ((c.row >= 0) && (c.col >= 0) &&
		    (c.row < boardDimension) && (c.col < boardDimension));
}

static inline int toRow(double y)
{
	return (int)floor((y - kGridLowerLeftY) * boardDimension / kGridHeight);
}

static inline int toCol(double x)
{
	return (int)floor((x - kGridLowerLeftX)  * boardDimension / kGridWidth);
}

static inline int inRange(int value)
{
	if (value < 0) return 0;
	if (value >= boardDimension) return boardDimension - 1;
	return value;
}

void SelectRegion(const coord& one, const coord& two)
{
	coord low = { min(one.row, two.row), min(one.col, two.col) };
	coord high = { max(one.row, two.row) + 1, max(one.col, two.col) +1 };
	double blockSize = kGridHeight / boardDimension;
	double llx = kGridLowerLeftX + low.col * blockSize;
	double lly = kGridLowerLeftY + low.row * blockSize;	
	DrawBox("Black", llx, lly, blockSize * (high.col - low.col), blockSize * (high.row - low.row));
	Pause(0.01);
}

void DeselectRegion(const coord& one, const coord& two)
{
	coord low = { min(one.row, two.row), min(one.col, two.col) };
	coord high = { max(one.row, two.row) + 1, max(one.col, two.col) + 1 };
	double blockSize = kGridHeight / boardDimension;
	double llx = kGridLowerLeftX + low.col * blockSize;
	double lly = kGridLowerLeftY + low.row * blockSize;	
	DrawBox("White", llx, lly, blockSize * (high.col - low.col), blockSize * (high.row - low.row));
}

static coord cachedLowerLeft;
static coord cachedUpperRight;
void WaitForUserSelection(coord& lowerLeft, coord& upperRight)
{
	coord down, up;
	while (true) {
		WaitForMouseDown();
		up.row = down.row = toRow(GetMouseY());
		up.col = down.col = toCol(GetMouseX());
		if (OnGrid(down)) break;
		WaitForMouseUp();
	}
	
	SelectRegion(down, up);
	do {
		DeselectRegion(down, up);
		up.row = inRange(toRow(GetMouseY()));
		up.col = inRange(toCol(GetMouseX()));
		SelectRegion(down, up);
	} while (MouseButtonIsDown());
	
	cachedLowerLeft.row = lowerLeft.row = min(up.row, down.row);
	cachedUpperRight.row = upperRight.row = max(up.row, down.row);	
	cachedLowerLeft.col = lowerLeft.col = min(up.col, down.col);
	cachedUpperRight.col = upperRight.col = max(up.col, down.col);
}

void ClearUserSelection()
{
	DeselectRegion(cachedLowerLeft, cachedUpperRight);
	UpdateDisplay();
}

static void DrawCenteredString(string message, double cx, double cy, string fontColor)
{
	double llx = cx - TextStringWidth(message)/2;
	double lly = cy - GetFontAscent()/2;
	DrawFilledBox("White", "White", llx, lly, TextStringWidth(message), (GetFontAscent() + GetFontHeight())/1.5);
	SetPenColor(fontColor);
	MovePen(llx, lly);
	DrawTextString(message);
}

static string previousMessage;
void DrawStatusMessage(string message)
{
	
	DrawCenteredString(previousMessage, kMessageCenterX, kMessageCenterY, "White");
	if (message.size() > 64) message = message.substr(0, 64);
	DrawCenteredString(message, kMessageCenterX, kMessageCenterY, "Black");	
	previousMessage = message;
}