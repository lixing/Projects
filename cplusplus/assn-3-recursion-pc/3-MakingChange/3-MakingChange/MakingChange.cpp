/*
 * File: MakingChange.cpp
 * ----------------------
 * Name: Lixing Lian
 * Section: Kevin Shin
 * This file is the starter project for the stock cutting problem on
 * Assignment #3
 * [TODO: extend the documentation]
 */
  
#include "genlib.h"
#include "simpio.h"
#include "vector.h"
#include <iostream>
 
int MakeChange(int amount, Vector<int>& denominations);
 
int main() {
 
    while(true){
 
    Vector<int> denominations;
    string reply;
    int v1,v2,v3,v4;
 
     
    while(true){
 
    cout << "Do you want to type in the coins value? ";
    reply = GetLine();
 
    //input the coins' values by user.
    if(reply == "y" || reply == "yes"){
 
        cout<<"Type in the first coin value:";
            v1=GetInteger();
        cout<<"Type in the second coin value:";
            v2=GetInteger();
        cout<<"Type in the third coin value:";
            v3=GetInteger();
        cout<<"Type in the fourth coin value:";
            v4=GetInteger();
 
        denominations.add(v1);
        denominations.add(v2);
        denominations.add(v3);
        denominations.add(v4);
        break;
    }
 
    //automatically generate the coins' value.
    if(reply == "n" || reply == "no"){
 
        cout << "The coins are worth 25, 10, 5, 1." << endl;
        denominations.add(25);
        denominations.add(10);
        denominations.add(5);
        denominations.add(1);
        break;
    }
 
    cout << "Please reply yes or no." << endl;
 
    }
 
    cout << "Input the amount: ";
    int amount = GetInteger();
     
    int coin = MakeChange(amount, denominations);
    cout << "Minimun number of coin is: " << coin << endl;
 
    cout << "Do you want to play again?(press n to exit)";
    reply = GetLine();
    if(reply == "no" || reply == "n") break;
 
    }
    return 0;
}
 
int MakeChange(int amount, Vector<int>& denominations, int start) {
    if (amount == 0) return 0;
    if (amount < 0) return -1;
    if (start == denominations.size()) return -1;
 
    int num = -1;
 
    //decrease the amount and analyze the rest amount.
    int rest = MakeChange(amount-denominations[start], denominations, start);
    if (rest!=-1) 
        num = 1+rest;
 
    int next = MakeChange(amount, denominations, start+1);
    if ((num == -1)||(next != -1 && next<num))
        num = next;
 
    return num;
}
 
//Wrapper function.
int MakeChange(int amount, Vector<int>& denominations) {
    return MakeChange(amount, denominations, 0);
}