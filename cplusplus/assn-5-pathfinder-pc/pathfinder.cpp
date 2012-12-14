/*
 * File: Pathfinder.cpp
 * --------------------
 * Name: Lixing Lian
 * Section: Kevin Shin
 * This file is the starter project for the Pathfinder application
 * on Assignment #6.
 */
 

#include "graph.h"
#include "graphtypes.h"
#include "genlib.h"
#include "gpathfinder.h"
#include "pqueue.h"
#include "simpio.h"
#include "path.h"
#include <iostream>

typedef Graph<nodeT, arcT> PathfinderClass;

//get and set the map image information.
class Pathfinder : public PathfinderClass{
	public:
		string getImage() { return image;}
		void setImage(string i) { image = i;}

    private:
		string image;
};

/* Function prototypes */

void QuitAction();
void ReadMapInfo(Pathfinder &pfinder);
void AddArc(string startPosition, string endPosition, double cost, Pathfinder &pfinder);
void ComputeDijkstra(Pathfinder &pfinder);
void GetTwoLocations(Pathfinder &pfinder, nodeT * &start, nodeT * &end);
nodeT * GetClickingLocations(Pathfinder &pfinder, pointT mouseInput);
Path FindShortestPath(nodeT *start, nodeT *finish);
double CountDistance(Vector<arcT *> path);
void DrawNodes(Set<nodeT *> node, string color);
void DrawArcs(Set<arcT *> arcs, string color);
void ComputeKruskal(Pathfinder &pfinder);


/* Main program */

int main() {
	
	Pathfinder pfinder;

	InitPathfinderGraphics();

	AddButton("Map" , ReadMapInfo, pfinder);
	AddButton("Dijkstra", ComputeDijkstra, pfinder);
	AddButton("Kruskal", ComputeKruskal, pfinder);
	AddButton("Quit", QuitAction);

	ReadMapInfo(pfinder);
	
	PathfinderEventLoop();
    return 0;
}

/* Sample callback function */

void QuitAction() {
	exit(0);
}


// -------------------------------------------- Function of "Map" Button ---------------------------------------------- 
void ReadMapInfo(Pathfinder &pfinder){
	ifstream inFile;
	string filename;
	string contents;
	bool open = false;
	pfinder.clear();

	while (!open){
		inFile.clear();
		cout << "Please enter name of graph data file: ";
		filename = GetLine();
		inFile.open(filename.c_str());
		if (inFile.good())
			open = true;
	}
	
	// read the name of the image file.
	getline(inFile, contents, '\n');
	pfinder.setImage(contents);

	// read the information of the nodes.
	getline(inFile, contents, '\n');
	if (contents=="NODES"){
		while (contents != "ARCS" && !inFile.eof()){
			getline(inFile, contents, '\n');
			if (contents != "ARCS"){
				// get the location of each node.
				pointT location;
				int index = contents.find_first_of(" ");
				location.x = StringToInteger(contents.substr(index, contents.find_last_of(" ")- index));
				location.y = StringToInteger(contents.substr(contents.find_last_of(" ")));

                // add the node
	            nodeT *node = new nodeT();
	            node->name = contents.substr(0,index);
	            node->loc = location;
	            pfinder.addNode(node);
			}
		}
	}

	// read the information of the arcs.
	if (contents == "ARCS"){
		while (!inFile.eof()){
			getline(inFile, contents, '\n');
			if (!inFile.eof()){

				//read the position of arcs.
				string startPosition;
				string endPosition;
				int index = contents.find_first_of(" ");
				startPosition = contents.substr(0, index);
				index++;
				endPosition = contents.substr(index, contents.find_last_of(" ")-index);
				double cost = StringToReal(contents.substr(contents.find_last_of(" ")));

				// add the arc
				AddArc(startPosition, endPosition, cost, pfinder);
			}
		}
	}

	inFile.close();

	// clean the screen
	DrawPathfinderMap(pfinder.getImage());
	DrawNodes(pfinder.getNodeSet(), NODE_COLOR);
}


 // add the nodes
void AddArc(string startPosition, string endPosition, double cost, Pathfinder &pfinder){
	nodeT *start = pfinder.getNode(startPosition);
	nodeT *end = pfinder.getNode(endPosition);

	// since the arc is bidimensional, so it needs to add twice for two directions.
	arcT *arc = new arcT();
	arc->cost = cost;
	arc->start = start;
	arc->finish = end;
	pfinder.addArc(arc);

	arcT *arc2 = new arcT();
	arc2->cost = cost;
	arc2->start = end;
	arc2->finish = start;
	pfinder.addArc(arc2);
}


// -------------------------------------------- Function of "Dijkstra" Button ---------------------------------------------- 
void ComputeDijkstra(Pathfinder &pfinder){
	nodeT *start = NULL;
	nodeT *end = NULL;

	// clean the screen
	DrawPathfinderMap(pfinder.getImage());
	DrawNodes(pfinder.getNodeSet(), NODE_COLOR);

	// get the two nodes from mouse clicking
	GetTwoLocations(pfinder, start, end);

	Path shortestPath = FindShortestPath(start, end);
	Set<arcT *> drawPath;

	for (int i =0; i < shortestPath.size(); i++)
		drawPath.add(shortestPath.GetElementAt(i));

	cout << "Shortest path: " << shortestPath.toString() << endl;
	DrawNodes(pfinder.getNodeSet(), DIM_COLOR);	
	DrawArcs(drawPath, HIGHLIGHT_COLOR);
	DrawPathfinderNode(start->loc, HIGHLIGHT_COLOR, start->name);
	DrawPathfinderNode(end->loc, HIGHLIGHT_COLOR, end->name);
	cout << "Finish Dijkstra analysis! \n"<< endl;
}


// need to pull out two places, start and end.
void GetTwoLocations(Pathfinder &pfinder, nodeT * &start, nodeT * &end){
	pointT mouseClick = pointT();

	//get the start position.
	while (true){
		mouseClick = pointT();
		cout << "Click on starting location...  ";
		mouseClick = GetMouseClick();
		start = GetClickingLocations(pfinder, mouseClick);
		if (start == NULL)
			cout << "Invalid click, please try again. \n"<< endl;
		else break;
	}
	cout << start->name <<" chosen."<< endl;
	DrawPathfinderNode(start->loc, HIGHLIGHT_COLOR, start->name);

	//get the end position.
	while (true){
		while (true){
			mouseClick = pointT();
		    cout << "Click on ending location...   ";
		    mouseClick = GetMouseClick();
		    end = GetClickingLocations(pfinder, mouseClick);
		    if(end == NULL)
				cout << "Invalid click, please try again. \n"<< endl;
		    else break;	
		}

		if (start->name == end->name){
			cout << "That is silly, you are already there!"<< endl;
			cout << "Invalid click, please try again. \n"<< endl;
		}
		else break;
	}
	cout << end->name <<" chosen."<< endl;
	DrawPathfinderNode(end->loc, HIGHLIGHT_COLOR, end->name);
}


// Detect the node near the mouse clicking area. If it doesn't found a node, return NULL
nodeT * GetClickingLocations(Pathfinder &pfinder, pointT mouseInput){
	foreach (nodeT *node in pfinder.getNodeSet()){
		pointT location = node->loc;
		if (mouseInput.x >(location.x - NODE_RADIUS) && mouseInput.x <(location.x + NODE_RADIUS))
			if (mouseInput.y > (location.y - NODE_RADIUS) &&mouseInput.y < (location.y + NODE_RADIUS))
				return node;
	}
	return NULL;
}

// Compute the shortest path using Dijkstra algorithm. It will return as a vector of arc pointers. Otherwise return an empty vecotr.
Path FindShortestPath(nodeT *start, nodeT *finish) {
	Path path;
	PQueue< Path> queue;
	Map<double> fixed;
	while (start != finish) {
		if (!fixed.containsKey(start->name)) {
			fixed.put(start->name, path.CountDistance());  
			foreach (arcT *arc in start->arcs) {
				if (!fixed.containsKey(arc->finish->name)) {
					Path newPath = path;
					newPath.Add(arc);
					queue.enqueue(newPath, newPath.CountDistance());
				}
			}
		}
		if (queue.isEmpty()) 
			return Path();
		path = queue.dequeue();
		start = path.GetElementAt(path.size() -1)->finish; 
	}
	return path;
}

//calculate the total distance along the path.
double CountDistance(Vector<arcT *> path) {
	double distance = 0;
	foreach (arcT *arc in path) {
		distance += arc->cost;
	}
	return distance;
}


void DrawNodes(Set<nodeT *> nodes, string color){	
	foreach (nodeT *node in nodes){
		DrawPathfinderNode(node->loc, color, node->name);
		DrawArcs(node->arcs, color);
	}
	UpdatePathfinderDisplay();
}

void DrawArcs(Set<arcT *> arcs, string color){
	foreach (arcT *arc in arcs)
		DrawPathfinderArc(arc->start->loc, arc->finish->loc, color);
}


// -------------------------------------------- Function of "Kruskal" Button ---------------------------------------------- 
// according to the cost, build a pqueue of the arcs from the graph, the minimum one will be extracted.
void ComputeKruskal(Pathfinder &pfinder){
	Set<arcT *> arcs = pfinder.getArcSet();
	PQueue<arcT *> path;
	Vector< Set<string> > nodes;
	Set<arcT *> arcSet;

	//clean the screen
	DrawPathfinderMap(pfinder.getImage());
	DrawNodes(pfinder.getNodeSet(), NODE_COLOR);

	// create a new set to store the nodes if they are not exist. 
	foreach (arcT *arc in arcs){
		path.enqueue(arc, arc->cost);
		bool alreadyExist = false;
		for (int i = 0; i < nodes.size(); i++){
			if (nodes[i].contains(arc->start->name)){
				alreadyExist = true;
				break;
			}
		}
		if (!alreadyExist){
			Set<string> newNode;
			newNode.add(arc->start->name);
			nodes.add(newNode);
		}
	}

	while (!path.isEmpty()){
		arcT * arc = path.dequeue();
		int startI , endI;
		for (int i =0; i < nodes.size(); i++){
			if (nodes[i].contains(arc->start->name))
				startI = i;
			if (nodes[i].contains(arc->finish->name))
				endI = i;
		}

		// check if they are in different sets
		if (startI != endI){
			nodes[startI].unionWith(nodes[endI]);
			nodes.removeAt(endI);
			arcSet.add(arc);
		}
	}

	// draw the nodes and arcs.
	DrawNodes(pfinder.getNodeSet(), DIM_COLOR);
	DrawArcs(arcSet, HIGHLIGHT_COLOR);
	cout << "Finish Kruskal analysis! \n"<< endl;
}

