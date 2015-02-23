#include "country.h"

// Declaration of the Countries available to be played, to be used in the adjacency list
enum Countries {
  Shire,
  Minhiriath,
  Enedwaith,
  Mirkwood,
  Erebor
  
};

struct GraphNode { // GraphNode, GraphList and Graph are defined both in graph.h and in country.cc
  int destination;
  struct GraphNode* next;

};

struct GraphList {
  struct GraphNode *head;
};

class Graph { 
private:
  int size;
  struct GraphList* array;

public:
  // Graph constructor
  Graph(int size) {
    this->size = size;
    array = new GraphList [size];
    for(int i = 0; i < size; i++)
    array[i].head = NULL;
  }

  // Creating new node
  GraphNode* NewGraphNode(int destination) {
    GraphNode* new_node = new GraphNode;
    new_node->destination = destination;
    new_node->next = NULL;
    return new_node;
  }

  // Add edge between nodes (country to country or cont. to cont.) to the map
  void AddEdge(int source, int destination) {
    GraphNode* new_node = NewGraphNode(destination);
    new_node->next = array[source].head;
    array[source].head = new_node;
    new_node = NewGraphNode(source);
    new_node->next = array[destination].head;
    array[destination].head = new_node;
  }

  // Print map of Countries
  void PrintCountry() {
    for(int i = 0; i < size; i++) {
      GraphNode* ptr = array[i].head;
      std::cout<<"\nAdjacency list of Country: " << i;
      while(ptr) {
        std::cout << "-> " << ptr->destination;
        ptr = ptr->next;
      }
      std::cout << std::endl;
    }
  }

  // Print map of Continents
  void PrintContinent() {
    for(int i = 0; i < size; i++) {
      GraphNode* ptr = array[i].head;
      std::cout << "\nAdjacency list of Continent: " << i;
      while(ptr) {
        std::cout<<"-> " <<ptr->destination;
        ptr = ptr->next;
      }
      std::cout<< std::endl;
    }
  }

};
