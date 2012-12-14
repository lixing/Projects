/*
 * File: KarelGoesHome.cpp
 * ----------------------
 * Name: Lixing Lian
 * Section: Kevin Shin
 * This file is the starter project for the path counting problem on
 * Assignment #3
 * [TODO: extend the documentation]
 */
  
#include "genlib.h"
#include "simpio.h"
#include <iostream>
 
int CountPaths(int street, int avenue);
 
 
int main() {
 
    int street, avenue;
    string reply;
 
    //ask the user to input the street and avenue number.
    while(true){
 
        cout << "street: ";
        street = GetInteger();
 
        cout << "avenue: ";
        avenue = GetInteger();
 
        //call the function CountPaths.
        int rout = CountPaths(street, avenue);
 
        cout << "There are " << rout << " possible ways." << endl;
 
        cout << "Do you want to play again?(press n to exit)";
        reply = GetLine();
 
    if(reply == "n" || reply == "no") break;
 
    }
 
    return 0;
}
 
//Recursive function. (1,1) is the destination. The direction is limited for down and left.
int CountPaths(int street, int avenue){
 
    if(street == 1 && avenue == 1)
        return 1;
    if(street < 1 || avenue < 1)
        return 0;
 
    return CountPaths(street-1, avenue) + CountPaths(street, avenue-1);
 
}