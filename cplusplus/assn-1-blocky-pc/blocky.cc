#include "gblocky.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "extgraph.h"
#include "grid.h"
#include "strutils.h"
#include "sound.h"
#include <iostream>

/**
 * Convenience structure used to track information
 * about the color on a particular cell, and whether
 * or not the cell has already been cleared one or 
 * more times.
 */

struct block {
	string color;
	bool original;	
};

/**
 * Small recording bundling information about 
 * a particular game level.  All Blocky boards
 * are sqaure, so we only need to track one dimension.
 * We also need to track the number of possible
 * colors that can appear on any particular level.
 */

struct levelDescription {
	int dimension;
	int numColors;
};


/**
 * Constants used in the master solution.  Feel free
 * to add even more.  These variables are technically
 * globals, but they're different because they're marked
 * as constants.  The 'static const' notation is our C++
 * equivalent of Java's 'static final'.
 */

void blocky(int level, int &score);
int checkWin(Grid<block> &grid);

static const string kLegalMoveSound = "Tink.wav";
static const string kIllegalMoveSound = "Frog.wav";
static const int kNumLevels = 12;
static const levelDescription kLevelDescriptions[]= {{5, 2}, {7, 2}, {9, 2}, 
													 {7, 3}, {9, 3}, {12, 3},
													 {9, 4}, {12, 4}, {15, 4},
													 {12, 5}, {15, 5}, {20, 5}};

/**
 * Randomly returns one of numColors colors, where the color
 * itself is expressed as a string.  C++ (at least the version
 * we're using) doesn't provide a Color class like Java does, so
 * we instead use strings to represent the notion of the color.
 *
 * @param numColors the number of colors that can be considered.
 * @return a string naming some color.
 */

string GetRandomColor(int numColors)
{
	
	int colorIndex = RandomInteger(1, numColors);
	switch (colorIndex) {
		case 1: return "Blue";
		case 2: return "Red";
		case 3: return "Green";
		case 4: return "Yellow";
		case 5: return "Violet";
		default: return "White";
	}
}


void Play(int row1, int row2, int col1, int col2, int &score, Grid<block> &grid, int numColors){

	if(grid[row1][col1].color==grid[row1][col2].color && grid[row1][col1].color==grid[row2][col1].color && grid[row1][col1].color==grid[row2][col2].color){
		PlayNamedSound(kLegalMoveSound);
		for(int i=row2;i<row1+1;i++){
			for(int j=col2;j<col1+1;j++){
				if(grid[i][j].original){
				score=score-1;
                  if(score<0)
					  score=0;
				}

			else{
				score=score+7;
				grid[i][j].original=true;
			}
			grid[i][j].color=GetRandomColor(numColors);
			DrawBlockAt(grid[i][j].color, i, j, false);
			}
		

		}
	}
	else PlayNamedSound(kIllegalMoveSound);



}

/**
 * Manages the details of a single selection.  
 * This function is placeholder and will need to be updated.
 *
 * @return void
 */


void OneTurn(Grid<block> &grid, int &score, int numColors)
{
	coord lowerLeft, upperRight; // coord is defined in gblocky.h

	WaitForUserSelection(lowerLeft, upperRight);
	int numRows = upperRight.row - lowerLeft.row + 1;
	int numCols = upperRight.col - lowerLeft.col + 1;
	int area = numRows * numCols;
	DrawStatusMessage("You made a selection of area " + IntegerToString(area) + ".");

	if(numRows!=1 && numCols!=1)
	Play(upperRight.row, lowerLeft.row, upperRight.col, lowerLeft.col, score, grid, numColors);

	UpdateDisplay();
	ClearUserSelection();
}




/**
 * Placeholder function to populate the display area so that
 * it looks like a real game board.
 *
 * @param dimension the height and width of the game board.
 * @return void
 */

void DisplayPlaceholderBoard(int dimension, int numColors,Grid<block> &grid)
{
	
    
	for (int row = 0; row < dimension; row++) {
		for (int col = 0; col < dimension; col++) {	
			grid[row][col].color=GetRandomColor(numColors);
            grid[row][col].original=false;
			DrawBlockAt(grid[row][col].color, row, col, true);

		}
	}
	
	UpdateDisplay();
}

/**
 * Allows the user to play through a full level of the game, where
 * the dimension of the board and the number of colors are made clear
 * via the specified level description called 'desc'.
 *
 * @param desc a single levelDescription identifying the size
 *        of the board and the number of colors to be used.
 * @return void
 */

void PlayLevel(levelDescription desc, int level, int &score, Grid<block> &grid) 
{	
   
	
	SetBlockyDimension(desc.dimension);
	
	DisplayPlaceholderBoard(desc.dimension, desc.numColors, grid);
	for (int turn = desc.dimension * 2; turn > 0; turn--) {
		string selectionsString = "selection";
		if (turn > 1) selectionsString += "s";
		DrawStatusMessage("Level:" + IntegerToString(level)+ ". You have " + IntegerToString(turn) + " " + 
			selectionsString + " remaining. Your score: "+IntegerToString(score));
		OneTurn(grid, score, desc.numColors);
        if(checkWin(grid)==1)
			return;
	}
}

int checkWin(Grid<block> &grid){

	for(int i=0;i<grid.numRows();i++){
		for(int j=0; j<grid.numCols();j++){
		  if(!grid[i][j].original)
			  return 0;
		}
	
	}
	return 1;

}

void information(int level, int &score){
            string input;
			cout<<"Oops, sorry about that. You can choose one of the following:" <<endl;
			cout<<"1. If you want to restart from the first level, press 1 and enter;" <<endl;
			cout<<"2. If you want to exist, press 2 and enter." <<endl;

			if(level!=0)
            cout<<"3. If you want to restart by the level you lose(you score will not be changed), press 3 and enter;" <<endl;
			
            cin>>input;

			if(input=="1"){
				score=0;
				blocky(0, score);
			}
			else if(input=="2")
			     exit(1);
		
			else if(input=="3" && level!=0)
				blocky(level, score);
				

			else {
				cout<<"Invalid choice!"<<endl;
			    information(level, score);
			}
			
}



void blocky(int level, int &score){

	Grid<block> grid;
	for (; level < kNumLevels; level++) { 
		grid.resize(kLevelDescriptions[level].dimension, kLevelDescriptions[level].dimension);
		PlayLevel(kLevelDescriptions[level],level+1, score, grid);
		
		if(checkWin(grid)==0){
			DrawStatusMessage("Sorry, you are lose. Your final score is:" +IntegerToString(score));
		    information(level, score);
		}
	}

	if(checkWin(grid)==1)
	DrawStatusMessage("Congratulations!  You finished! Your final score is:"+IntegerToString(score) );
   
}


/**
 * The entry point of the entire Blocky program.
 *
 * @return void
 */

int main()
{	   
	Randomize();
	InitBlockyGraphics();
	int score=0;
	blocky(0, score);

	return 0;
}