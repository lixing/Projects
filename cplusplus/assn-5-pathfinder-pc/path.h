/*
 * File: path.h
 * ------------
 * Name: Lixing Lian
 * Section: Kevin Shin
 * This file is the interface for a Path class that encapsulates
 * the idea of a multistep path.
 */

/////////////////////////////////////////////////////////////////////
// Your task in this part of the assignment is to design a Path    //
// class that supports the implementation of Dijkstra's algorithm. //
// As noted in the assignment handout, your class must meet the    //
// following conditions:                                           //
//                                                                 //
// 1. The class must not export any public instance variables.     //
//    All data required to store the path must be private to the   //
//    class.                                                       //
//                                                                 //
// 2. The method that returns the total cost of the path must      //
//    run in constant time.                                        //
//                                                                 //
// 3. The class must export a toString method that returns a       //
//    string composed of the nodes on the path separated by        //
//    arrows formed by the two-character sequence ->.              //
//                                                                 //
// 4. Any heap storage allocated by this class must be freed       //
//    when the object is deleted.                                  //
//                                                                 //
// Beyond those restrictions, you are free to design and implement //
// this class as you see fit.  You must, however, document your    //
// design decisions in the corresponding path.cpp file.            //
/////////////////////////////////////////////////////////////////////

#ifndef _path_h
#define _path_h


#include "graphtypes.h"

class Path {

public:
	Path();
	~Path();

/*
 * Function: Add
 * Usage: Add(arcT *arc);
 * ----------------------------------
 * Adds a arc to the internal array of arc(s)
 */
	void Add(arcT *arc);

/*
 * Function: TotalPathDistance
 * Usage: TotalPathDistance();
 * ----------------------------------
 * Returns the distance
 */
	double CountDistance();

	
/*
 * Function: toString
 * Usage: toString();
 * ----------------------------------
 * Converts the array of arcs to a string type
 */
	string toString();

/*
 * Function: size
 * Usage: size();
 * ----------------------------------
 * Returns the size of the arcs.
 */
	int size();

/*
 * Function: GetElementAt
 * Usage: Set a integer i, GetElementAt(i); For example,  GetElementAt(10)
 * ----------------------------------
 * Returns an arcT* type element in a specific index(position) i.
 */
	arcT* GetElementAt(int i);

private:
	Vector<arcT *> arcs;
	double cost;
};

#endif
