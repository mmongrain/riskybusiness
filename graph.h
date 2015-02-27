#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>

struct GraphNode {
	int destination;
	struct GraphNode* next;
};
/*
struct GraphList {
	struct GraphNode *head;
};

class Graph {
private:
	struct GraphList* array;
	int size;
public:
	void MakeGraph();
	void AddAdjacent(Country a, Country b);
	Graph(int size);
	GraphNode* NewGraphNode(Country destination);
	void AddEdge(Country source, Country destination);
	void PrintGraph();
};
*/