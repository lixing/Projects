
/**
 * File: maze-generator.cpp
 * ------------------
 * Name:Lixing Lian
 * Section Leader Name:Kevin Shin
 */
#include "foreach.h"
#include <iostream>
#include "set.h"
#include "vector.h"
#include "map.h"
#include "genlib.h"
#include "extgraph.h"
#include "simpio.h"
#include "random.h"
#include "maze-types.h"
#include "maze-graphics.h"
 
 
void initialize(Vector<wall> &vectorWall, int dimension);
int recursiveFindA(Vector<Vector<cell>> &vectorCell, cell check, int index);
bool recursiveFindB(Vector<cell> &vectorCell, cell check, int index);
 
 
 
int main(){
 
     
    int dimension;
    InitMazeGraphics();
    int a, b;
    double kMazeDimension = 3.75;
 
    while (true){
                 
        cout << "What should the dimension of your maze be [0 to exit]? ";
        dimension = GetInteger();
     
        if (dimension ==0)
            return 0;
 
        if (dimension >= 7 && dimension <= 50){
 
        InitMazeGraphics();
        SetPenColorRGB(1,1,1);
        MovePen(0,0);
        StartFilledRegion(1);
        EndFilledRegion();
        UpdateDisplay();
 
        Vector<Vector<cell>> vectorCell;
        Vector<wall> vectorWall;
        cell element;
 
        cout << "Building initial chambers..." << endl;
        int counter = 0;
 
        for (int i= 0; i < dimension; i++)
            for (int j = 0; j < dimension; j++){
                element.col = i;
                element.row = j;
                Vector<cell> initial;
                initial.add(element);
                vectorCell.add(initial);
        }
 
        initialize(vectorWall, dimension);
 
        DrawMazeBorder();
 
        double llx = GetWindowWidth()/2 - kMazeDimension/2;
        double lly = GetWindowHeight()/2 - kMazeDimension/2;
     
       MovePen(llx, lly);
       SetPenColor("Blue");
       DrawLine(0, kMazeDimension);
       SetPenColor("White");
       DrawLine(kMazeDimension/dimension, 0 );
       SetPenColor("Blue");
       DrawLine(kMazeDimension - kMazeDimension/dimension, 0);
       DrawLine(0, -kMazeDimension);
       SetPenColor("White");
       DrawLine(- kMazeDimension/dimension, 0);
       SetPenColor("Blue");
       DrawLine(- kMazeDimension + kMazeDimension/dimension, 0);    
 
        SetMazeDimension(dimension);
 
 
        Randomize();
         
 
        for (int i = 0; i < vectorWall.size(); i++){
            a = RandomInteger(0,(vectorWall.size()-1));
            b = RandomInteger(0,(vectorWall.size()-1));
 
            wall tmp = vectorWall[a];
            vectorWall[a] = vectorWall[b];
            vectorWall[b] = tmp;
        }
 
        foreach (wall element in vectorWall){
            DrawWall(element);
        }
 
        Pause(3);
       
        cout << "Safely merging chambers, being carefule to never introduce loops..." << endl;
 
         
         
        Vector<wall>::Iterator iterator = vectorWall.iterator();
        while (iterator.hasNext() && (counter < ((dimension * dimension)-1))){
            wall check = iterator.next();
             
            int k = recursiveFindA(vectorCell, check.one, 0);
            if (k >= 0){
                if (!recursiveFindB(vectorCell[k], check.two, 0)){
                    counter++;
 
                    RemoveWall(check);
                    Pause(0.0005);
                    int t = recursiveFindA(vectorCell, check.two, 0);
                    if (t >= 0){
                        for (int i = 0; i < vectorCell[t].size(); i++)
                            vectorCell[k].add(vectorCell[t][i]);
                        vectorCell.removeAt(t);
                    }
                }
            }
        }
     
     
    }
    }
 
    return 0;
}
 
 
void initialize(Vector<wall> &vectorWall, int dimension){
    wall horizontal, vertical;
 
    for (int i=0; i < dimension; i++)
        for (int j = 0; j < dimension; j++){
             
            if (i < (dimension-1)){
                horizontal.one.col = i;
                horizontal.one.row = j;
                horizontal.two.col = i+1;
                horizontal.two.row = j;
                vectorWall.add(horizontal);
            }
             
            if (j < (dimension-1)){
                vertical.one.col = i;
                vertical.one.row = j;
                vertical.two.col = i;
                vertical.two.row = j+1;
                vectorWall.add(vertical);
            }
             
        }
 
}
 
 
int recursiveFindA(Vector<Vector<cell> > &vectorCell, cell check, int index){
    if (index < vectorCell.size()){
        if (recursiveFindB(vectorCell[index], check, 0))
            return index;
        else
            return recursiveFindA(vectorCell, check, ++index);
    }
    return -1;
}
 
bool recursiveFindB(Vector<cell> &vectorCell, cell check, int index){
    if (index < vectorCell.size()){
        if (vectorCell[index] == check)
            return true;
        else
            return recursiveFindB(vectorCell, check, ++index);
    }
    return false;
}