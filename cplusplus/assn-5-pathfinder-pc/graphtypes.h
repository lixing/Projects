/*
 * File: graphtypes.h
 * ------------------
 * Name: Lixing Lian
 * Section: Kevin Shin
 * The initial version of this file contains only the definitions required
 * for graphs.  Your job is to add new fields as needed for the Pathfinder
 * application.
 */
 

#ifndef _graphtypes_h
#define _graphtypes_h

#include "set.h"
#include "point.h"
/* Forward references to nodeT and arcT */

struct nodeT;
struct arcT;

/*
 * Type: nodeT
 * -----------
 * This type represents an individual node and consists of the
 * name of the node and the set of arcs that leave this node.
 */

struct nodeT {
	string name;
	Set<arcT *> arcs;
	pointT loc;
};

/*
 * Type: arcT
 * ----------
 * This type represents an individual arc and consists
 * of pointers to the nodes at each end, along with the
 * cost of traversing the arc.
 */

struct arcT {
	nodeT *start, *finish;
	double cost;
};

#endif
