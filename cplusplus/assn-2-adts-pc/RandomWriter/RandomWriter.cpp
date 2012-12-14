/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: Lixing Lian
 * Section: Kevin Shin
 * This file is the starter project for the random writer problem
 * on Assignment #2.
 * [TODO: extend the documentation]
 */
 
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "vector.h"
#include "map.h"
#include <iostream>
#include <fstream>
 
 
void readFile(Map<Vector<char>> &map, ifstream &infile, int seed);
void Display(Map<Vector<char>> &map, string start);
 
 
int main() {
 
    int seed;
    Map<Vector<char>> map;
    ifstream infile;
    int maxSeed =0;
    string max="";
 
    while (true){   
        infile.clear();
        cout << "Please enter filename containing source text : ";
        string filename = GetLine();
        infile.open(filename.c_str());
        if (infile.good()) break;
         
    }
 
    while (true)
    {
        cout << "What order of analysis ? (a number from 1 to 10) : ";
        seed = GetInteger();
        if (seed >=1 && seed <=10) break;
    }
 
    cout << "Analyzing.... please wait. " << endl;
 
    readFile(map,infile,seed);
    infile.close();
         
    Vector<char> vector;
    foreach (string character in map)
    {
        vector = map.get(character);
        if (vector.size() > maxSeed)
        {
            max = character;
            maxSeed = vector.size();
        }
    }
 
    cout << max;
    Display(map, max);
    return 0;
}
 
 
void readFile(Map<Vector<char>> &map, ifstream &infile, int seed)
{   
    seed++;
    char* temp = new char[seed];
    infile.get(temp, sizeof(char)*seed);
    string value = temp;
    char character;
    while (!infile.eof())
    {
        Vector<char> vector;
        infile.get(character);
        if (map.containsKey(value))
            vector = map.get(value);
 
        vector.add(character);
        map.put(value, vector);
 
        value = value.substr(1,value.length()-1) + character;
    }
}
 
 
void Display(Map<Vector<char>> &map, string newStart)
{
    Randomize();
    Vector<char> vector;
    int random=0;
    int counter = newStart.length();
     
    while (true)
    {
        if (counter > 2000){
           cout << "\n-----------------END-----------------"<< endl;
           break;
        }
        vector = map.get(newStart);
        if (vector.size() ==0) 
        {
            cout << "NO MORE KEYS" <<endl; 
            break;
        }
        random = RandomInteger(0,vector.size()-1);
        cout << vector[random];
        newStart = newStart.substr(1,newStart.length()-1) + vector[random];
        counter++;
    }
}