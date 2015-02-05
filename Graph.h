#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include "country.h"

struct GraphNode
{
	int destination;
	struct GraphNode* next;

};

struct GraphList
{
	struct GraphNode *head;
};

class Graph
{
private:
	struct GraphList* array;
	int size;
public:
	void makeGraph();
	void addAdjacent(Country a, Country b);
	Graph(int size);
	GraphNode* newGraphNode(Country destination);
	void addEdge(Country source, Country destination);
	void printGraph();
};