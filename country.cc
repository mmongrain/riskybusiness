#include "country.h"

using namespace std;


// Declaration of the Countries available to be played, to be used in the adjacency list
enum Countries
{
	Shire,
	Minhiriath,
	Enedwaith,
	Mirkwood,
	Erebor
	
};

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
	int size;
	struct GraphList* array;

public:
	// Graph constructor
	Graph(int size)
	{
		this->size = size;
		array = new GraphList [size];
		for(int i = 0; i < size; i++)
			array[i].head = NULL;
	}

	// Creating new node
	GraphNode* newGraphNode(int destination)
	{
		GraphNode* newNode = new GraphNode;
		newNode->destination = destination;
		newNode->next = NULL;
		return newNode;
	}

	// Add edge between nodes (country to country or cont. to cont.) to the map
	void addEdge(int source, int destination)
	{
		GraphNode* newNode = newGraphNode(destination);
		newNode->next = array[source].head;
		array[source].head = newNode;
		newNode = newGraphNode(source);
		newNode->next = array[destination].head;
		array[destination].head = newNode;
	}

	// Print map of Countries
	void printCountry()
	{
		for(int i = 0; i < size; i++)
		{
			GraphNode* ptr = array[i].head;
			cout<<"\nAdjacency list of Country: " << i;
			while(ptr)
			{
				cout<<"-> " <<ptr->destination;
				ptr = ptr->next;
			}
			cout<< endl;
		}
	}

	// Print map of Continents
	void printContinent()
	{
		for(int i = 0; i < size; i++)
		{
			GraphNode* ptr = array[i].head;
			cout<<"\nAdjacency list of Continent: " << i;
			while(ptr)
			{
				cout<<"-> " <<ptr->destination;
				ptr = ptr->next;
			}
			cout<< endl;
		}
	}

};