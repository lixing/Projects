/*
 * File: path.cpp
 * --------------
 * Name: Lixing Lian
 * Section: Kevin Shin
 * This file implements the path.h interface.
 */

/////////////////////////////////////////////////////////////////////
// Your task in this part of the assignment is to write the code   //
// that implements your path.h interface.  For the benefit of      //
// future programmers who will need to work on this interface,     //
// you must also write an extended comment (presumably replacing   //
// this to-do box) that documents the design decisions you made    //
// in structuring the Path class as you did.                       //
/////////////////////////////////////////////////////////////////////


#include "genlib.h"
#include "path.h"


Path::Path(){
	cost = 0;
}

Path::~Path(){
	arcs.clear();
}

void Path::Add(arcT *arc){
	arcs.add(arc);
	cost += arc->cost;
}

double Path::CountDistance(){
	return cost;
}

string Path::toString(){
	string value;
	foreach(arcT *arc in arcs){
		value = value + arc->start->name + "->" + arc->finish->name + "(" + RealToString(arc->cost) + ")" +"\n";
	}
	return value;
}

int Path::size(){
	return arcs.size();
}

arcT* Path::GetElementAt(int i){
	if(i < 0 || i > arcs.size())
		Error("invalid index");
	return arcs[i];
}