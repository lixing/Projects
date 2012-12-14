
/* File: boggle.cpp
 * ----------------
 * Author:
 * Date:
 * Section leader:
 */
 
#include "genlib.h"
#include "gboggle.h"
#include "sound.h"
#include "extgraph.h"
#include "simpio.h"
#include "lexicon.h"
#include "random.h"
#include "grid.h"
#include <iostream>
 
const int MIN_WORD_COUNT = 4;
 
struct cell{
    int row, col;
};
 
const string STANDARD_CUBES[16] = {
  "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS", 
  "AOOTTW", "CIMOTU", "DEILRX", "DELRVY", 
  "DISTTY", "EEGHNW", "EEINSU", "EHRTVW", 
  "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25] = {
  "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM", 
  "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW", 
  "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT", 
  "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU", 
  "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};
 
void GiveInstructions()
{
    cout << endl << "The boggle board is a grid onto which I will randomly distribute" << endl
     << "dice.  These 6-sided dice have letters rather than numbers on the faces, " << endl
     << "creating a grid of letters on which you try to form words.  You go first, " << endl
     << "entering the words you find that are formed by tracing adjoining " << endl
     << "letters.  Two letters adjoin if they are next to each other horizontally, " << endl
     << "vertically, or diagonally. A letter can only be used once in the word. Words" << endl
     << "must be at least 4 letters long and can only be counted once.  You score points" << endl
     << "based on word length, a 4-letter word is worth one, 5-letters two, etc."   << endl
     << "After your tiny brain is exhausted, I, the brilliant computer, will find " << endl
     << "all the remaining words in the puzzle and double or triple your paltry score." << endl;
     
    cout << "\nHit return when you're ready...";
         
    GetLine();
}
 
void Welcome()
{
    cout << "Welcome!  You're about to play an intense game of mind-numbing Boggle." << endl
     << "The good news is that you might improve your vocabulary a bit.  The" << endl
     << "bad news is that you're probably going to lose miserably to this little" << endl
     << "dictionary-toting hunk of silicon.  If only YOU had a gig of RAM...\n" << endl;
}
 
bool containsDigit(string reply);
void highLightOrder(Vector<cell> wordOrder, string word, int dimension);
char clickMouse(Grid<char> &board, int dimension);
bool usedLetter(int row, int col,Vector<cell> &wordOrder);
bool humanFind(string currentWord, Grid<char> &board, Vector<cell> &wordOrder, string foundWord, int xPostion, int yPostion );
string computerFind(Grid<char> &board, Lexicon alreadyFoundWords, Lexicon dictionary, Vector<cell> &wordOrder, string foundWord, int startX, int startY, int xPostion, int yPostion);
 
int main()
{
 
    string reply, file, diceList, input, currentWord;
    int replyInt=0;
    Vector<string> theDice;
    int dimension = 4;
    Grid<char> board(dimension, dimension);
    bool mouse = false;
    Vector<cell> wordOrder;
  
 
    InitGraphics();
    Welcome();
    Lexicon lex("lexicon.dat");
 
    while(true){
        theDice.clear();
        wordOrder.clear();
        diceList="";
        InitGraphics();
 
        while(true){
 
            cout <<"Would you like sound? ";
            reply=GetLine();
            if(reply=="yes" || reply=="y"){
               SetSoundOn(true);
               break;
            }
            else if(reply=="no" || reply=="n"){
               SetSoundOn(false);
               break;
            }
            else cout <<"Please answer yes or no."<<endl;
        }
 
 
        while(true){
            cout <<"Do you need instructions? ";
            reply=GetLine();
            if(reply=="yes" || reply=="y"){
               GiveInstructions();
               break;
            }
            else if(reply=="no" || reply=="n"){
               break;
            }
            else cout <<"Please answer yes or no."<<endl;
        }
 
     
        while(true){
            cout <<"Which dimension do you want? (4 or 5) ";
            replyInt=GetInteger();
            if(replyInt== 4){
               dimension=4;
               board.resize(4,4);
               file="cubes16.txt";
               PlayNamedSound("not fooling anyone.wav");
               break;
            }
            else if(replyInt==5){
               dimension=5;
               board.resize(5,5);
               file="cubes25.txt";
               PlayNamedSound("not fooling anyone.wav");
               break;
            }
            else cout <<"Please answer 4 or 5."<<endl;
            }
 
 
        cout <<"I'll give you a chance to set up the board to your specification."<< endl;
        cout<<"This makes it easier to confirm your boggle program is working." <<endl;
 
 
        while (true){
            cout <<"Do you want to force the board configuration? "; 
            reply=GetLine();
            if(reply=="yes" || reply=="y"){
              cout <<"Enter a " << dimension*dimension<<"-character string to identify which letters you want on the cubes."<<endl;
              cout<<"The first " <<dimension<<" letter are the cubes on the top row from left to right,"<<endl;
              cout<<"next "<<dimension<<" letters are the second row, etc."<<endl;
 
              while(true){
                  cout <<"Enter the string: "; 
                  reply=GetLine();
                  if(!containsDigit(reply)){
                      diceList=reply;
                      break;
                  }
              cout <<"The string cannot contain digits! "; 
     
              }
               break;
            }
            else if(reply=="no" || reply=="n"){
 
            // open the file and read the values
               ifstream infile;
               infile.open(file.c_str());
               if (infile.good()){
                   for (int i = 0; i < (dimension*dimension); i++){
                        string temp;
                        getline(infile, temp, '\n');
                        theDice.add(temp);
                    }
                    infile.close();
              }
    
       
               Randomize();
               int insert;
               while (theDice.size() > 0){
                   insert = RandomInteger(0, theDice.size()-1);
                   diceList += theDice[insert][RandomInteger(0, theDice[insert].length()-1)];
                   theDice.removeAt(insert);
               }
 
               PlayNamedSound("yeah right.wav");
               break;
            }
            else cout <<"Please answer yes or no."<<endl;
        }
 
 
        while(true){
            cout <<"Do you want to use mouse? ";
            reply=GetLine();
            if(reply=="yes" || reply=="y"){
               mouse=true;
               break;
            }
            else if(reply=="no" || reply=="n"){
               mouse=false;
               break;
            }
            else cout <<"Please answer yes or no."<<endl;
        }
 
        PlayNamedSound("dice rattle.wav");
         
 
        // build the grid and label the cube
        int counter=0;
        for (int i = 0; i < dimension; i++){
            for (int j = 0; j < dimension; j++){
                board[i][j] = diceList[counter++];
            }
        }
 
        DrawBoard(dimension, dimension);
 
        for (int i = 0; i < dimension; i++){
            for (int j = 0; j < dimension; j++){
               LabelCube(i, j, board[i][j]);
            }
        }
         
        Lexicon humanWords, computerWords;
 
        while (true){
            cout <<  "Enter a word (Q is equal to Qu) : ";
 
            if (mouse){
                currentWord ="";
                cout << "/nChoose a word by clicking the letter (click to the blank area to finish): ";
 
                while (true){
                    WaitForMouseDown();
                    WaitForMouseUp();
 
                    //get the letter by clicking
                    char clickLetter = clickMouse(board, dimension);
                    if (clickLetter != NULL){
                        cout << clickLetter;
                        currentWord += clickLetter;     
                    }
                    else break;
                }
            }
            else currentWord = GetLine();
 
            if (currentWord == "") break;
 
            // use QU instead of Q
            currentWord = ConvertToUpperCase(currentWord);
            int size=currentWord.size();
            for(int i = 0; i<size; i++){
                if(currentWord[i]=='Q')
                    currentWord.replace(i,1,"QU");
            }
          
            //for user input the word, and check if it is legal.
            wordOrder.clear();
            if( currentWord.length() >= MIN_WORD_COUNT){
              if (lex.containsWord(currentWord)){
                if (!humanWords.containsWord(currentWord)){             
                    if (humanFind(currentWord,board, wordOrder, "", 0, 0)){
                         
                        humanWords.add(currentWord);
                        highLightOrder(wordOrder, currentWord, dimension);
                        PlayNamedSound("excellent.wav");
                         
                        //cover the printed word at the bottom.
                        SetPenColor("White");
                        StartFilledRegion(0.5);
     
                        MovePen(2.35, 0.5);
                        DrawLine(5,0);
                        DrawLine(0,0.3);
                        DrawLine(-5,0);
                        DrawLine(0,-0.3);
                        EndFilledRegion();
 
                        RecordWordForPlayer(currentWord, Human);
                    }
                    else{
                        cout << "You can't make that word." << endl;
                        PlayNamedSound("whoops.wav");
                    }
                }
                else{
                    cout << "You've already guessed that!" << endl;
                    PlayNamedSound("not fooling anyone.wav");
                }
              }
              else{         
                 cout << "Not a valid word." << endl;
                 PlayNamedSound("denied.wav");
              }
            }
            else {
                cout << "That word doesn't meet the minimum word length." << endl;
                PlayNamedSound("moo.wav");
            }
        }
 
        // computer finds the words. 
 
        cell startPos;
        startPos.row = 0;
        startPos.col =0;
        computerWords = humanWords;
 
        PlayNamedSound("tweetle.wav");
         
        while (true){
            if (wordOrder.size() > 0){
                // to determind the start position.
                if((wordOrder[0].col == dimension-1) && (startPos.row != wordOrder[0].row))
                    startPos.col=0;
                else startPos.col = wordOrder[0].col;
                 
                startPos.row = wordOrder[0].row;
            }
 
            wordOrder.clear();
            //to call the function to return all the possible words.
            string computerFound = computerFind(board, computerWords, lex,wordOrder, "", startPos.col, startPos.row,0, 0);
 
            if (computerFound =="") break;
 
            computerWords.add(computerFound);
            RecordWordForPlayer(computerFound, Computer);
             
        }
 
        cout << "Would you like to play again ?";
        reply=GetLine();
        if (reply =="no" || reply == "n")   break;
    }
 
    return 0;
}
 
 
//to check if the input configuration contains digit
bool containsDigit(string reply){
    for(int i=0;i<reply.size();i++){
         if ((reply[i]>'0') && (reply[i]<'9'))
             return true;
    }
    return false;
  
}
 
 
//identify the mouse click position and return the corresponding word.
char clickMouse(Grid<char> &board, int dimension){
    double x = GetMouseX()-1.93;
    double y = -1*(GetMouseY()-3.1);
     
    int row = (int)(y / 0.5);
    int col = (int)(x / 0.5);
    if ((row < dimension) && (col < dimension))
        return board[row][col];
 
    return NULL;
}
 
 
// to highlight the words and write down the order 
void highLightOrder(Vector<cell> wordOrder, string word, int dimension){
    int order =1;
    int size;
    double x,y;
 
    //draw the word under the board.
    SetFont("Geneva");
    SetPointSize(30);
    SetPenColor("Label Color");
    MovePen(2.35,0.5);
    DrawTextString(word);
 
    foreach (cell theCell in wordOrder){
         
        HighlightCube(theCell.row, theCell.col, true);  
 
        //write the order in the letters
        size=10;
        x=2 + (theCell.col * 0.5);
        y=2.93 - (theCell.row * 0.5);
          
        if(dimension==5){
            size=8;
            x=0.8*x;
            y=0.8*y;
        }
 
        //draw the order in the letter.
        SetFont("Geneva");
        SetPenColor("White");
         
        SetPointSize(size);
        MovePen(x,y);
        DrawTextString(IntegerToString(order));
        order++;
    }
 
    Pause(2);
 
    foreach (cell theCell in wordOrder){
        HighlightCube(theCell.row, theCell.col, false);
    }
}
 
 
// to check if the letter is already used.
bool usedLetter(int row, int col, Vector<cell> &wordOrder){
    cell checkCell;
    for (int i =0; i < wordOrder.size(); i++){
        checkCell = wordOrder[i];
        if (checkCell.row == row && checkCell.col == col) 
            return true;
    }
    return false;
}
 
 
// to check if the input word is legal and in the board.
bool humanFind(string currentWord, Grid<char> &board, Vector<cell> &wordOrder, string foundWord, int xPostion,  int yPostion){  
    cell addNew;
     
    if (currentWord == foundWord)
        return true;
 
    //to find the word in the board according to the input
    if (foundWord.empty()){
        for (int rows = 0; rows < board.numRows(); rows++){
            for (int cols = 0; cols < board.numCols(); cols++){
                // find the each character within the 
                if (board[rows][cols] == currentWord[0]){
                    addNew.row = rows;
                    addNew.col = cols;
                    foundWord = currentWord[0];
                    wordOrder.add(addNew);
                    if (humanFind(currentWord, board, wordOrder, foundWord, cols, rows))
                        return true;
                    wordOrder.clear();
                }
            }
        }
    }
    else{
        // check around letters in the board to determind the next letter's position 
        int x1,x2,y1,y2;
        if(yPostion > 0)
            y1 = yPostion - 1;
        else y1 = yPostion;
 
        if(yPostion == board.numRows()-1)
            y2 = yPostion;
        else y2 = yPostion + 1;
 
        if(xPostion > 0)
            x1 = xPostion - 1;
        else x1 = xPostion;
 
        if(xPostion == board.numCols()-1)
            x2 = xPostion;
        else x2 = xPostion + 1;
 
        //check the word is legal or not. If legal, return true
        for (int i = y1; i <=y2 ;i++){
            for (int j = x1; j <=x2; j++){
                if (board[i][j] == currentWord[foundWord.length()]){
                    if( !(i==yPostion && j ==xPostion) ){
                        if (!usedLetter(i,j,wordOrder)){
                            addNew.row = i;
                            addNew.col = j;
                            foundWord += currentWord[foundWord.length()];
                            wordOrder.add(addNew);
 
                            if (humanFind(currentWord, board,wordOrder, foundWord, j, i))
                                return true;
 
                            else{ 
                                if (foundWord.length() > 1)
                                   foundWord = foundWord.substr(0, foundWord.length()-1);
                                wordOrder.removeAt(wordOrder.size()-1);
                            }
                       }
                    }
                   
                 
                }
            }
        }
     
        return false;
    }
    return false;
}
 
 
// to generate all the possible and unused words in the board for computer
string computerFind(Grid<char> &board, Lexicon alreadyFoundWords, Lexicon dictionary, Vector<cell> &wordOrder, string foundWord, int startX, int startY, int xPostion, int yPostion ){  
    cell addNew;
     
    if (foundWord.length() >= MIN_WORD_COUNT)
        if (dictionary.containsWord(foundWord) && (!alreadyFoundWords.containsWord(foundWord)))
                return foundWord;
 
     
    //to find the word in the board according to the input
    if (foundWord.empty()){
        for (int rows = startY; rows < board.numRows(); rows++){
            for (int cols = startX; cols < board.numCols(); cols++){
                    addNew.row = rows;
                    addNew.col = cols;
                    foundWord = board[rows][cols];  
                    wordOrder.add(addNew);
                    string newWord = computerFind(board,alreadyFoundWords, dictionary,wordOrder, foundWord,startX, startY, cols, rows );
                    if (newWord.length() > 0)
                        return newWord;
                    wordOrder.clear();
                     
            }
        }
    }
    else{
 
        // check around letters in the board to determind the next letter's position 
        int x1,x2,y1,y2;
        if(yPostion > 0)
            y1 = yPostion - 1;
        else y1 = yPostion;
 
        if(yPostion == board.numRows()-1)
            y2 = yPostion;
        else y2 = yPostion + 1;
 
        if(xPostion > 0)
            x1 = xPostion - 1;
        else x1 = xPostion;
 
        if(xPostion == board.numCols()-1)
            x2 = xPostion;
        else x2 = xPostion + 1;
 
         //check the word is legal or not. If legal, return true
        for (int i = y1; i <= y2;i++){
            for (int j = x1; j<= x2; j++){
                if (!(i==yPostion && j ==xPostion)){
                    if (!usedLetter(i,j,wordOrder)){
                        addNew.row = i;
                        addNew.col = j;
                        foundWord += board[i][j];
                        wordOrder.add(addNew);
                        if (dictionary.containsPrefix(foundWord)){
                            string newWord = computerFind(board, alreadyFoundWords, dictionary,wordOrder,foundWord, startX, startY,  j, i);
                            if (newWord.length() > 1)
                                return newWord;
                            else if (wordOrder.size() > 0)
                                    wordOrder.removeAt(wordOrder.size()-1);
                        }
                        else if (wordOrder.size() > 0)
                                wordOrder.removeAt(wordOrder.size()-1);
                         
                        if (foundWord.length() > 0)
                            foundWord = foundWord.substr(0, foundWord.length()-1);
                    }
                }
            }
        }
    }
    return "";
}