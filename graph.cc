#include "Graph.h"
#include "country.h"
using namespace std;

// In source files, how to properly declare methods and stuff?

Graph::Graph(int size)
{
	this->size = size;
	array = new GraphList [size];
	for(int i = 0; i < size; i++)
		array[i].head = NULL;
}

//Creating new node
GraphNode* newGraphNode(Country destination)
{
	// Is it possible to have a Country as a Node and not an int? Why is destination not working
	GraphNode* newNode = new GraphNode;
	newNode->destination = destination;
	newNode->next = NULL;
	return newNode;
}

//add edge between nodes to map
void addEdge(Country source, Country destination)
{
	GraphNode* newNode = newGraphNode(destination);
	newNode->next = array[source].head;		// Why is array undefined?
	array[source].head = newNode;
	newNode = newGraphNode(source);
	newNode->next = array[destination].head;
	array[destination].head = newNode;
}

//print map
void printGraph()
{
	for(int i = 0; i < sizeof(Graph); i++)
	{
		GraphNode* ptr = array[i].head;
		cout<<"\nAdjacency list of Node: " << i;
		while(ptr)
		{
			cout<<"-> " <<ptr->destination;
			ptr = ptr->next;
		}
		cout<< endl;
	}
}

void makeGraph()
{
	ifstream inputfile;
	Country country_temp;

	//adds countries into country_vector
	inputfile.open("countries.txt");
	
	if (inputfile.is_open())
    {
		// Create string for getline
		string line_from_file;

		// While the file is not empty, get a line from the file and cast to line_from_file
		while (getline(inputfile,line_from_file))
		{
			// Make temporary strings
			string country_name;
			int x_coord, y_coord;
			
			size_t current_pos;
		
			// Get X-Coordinate first
			// Find first delimiter which will give us the value
			current_pos = line_from_file.find_first_of(",");
		
			// Cast X-Coordinate into temporary var
			// Put into stringstream
			istringstream conv_to_signed(line_from_file.substr(0,current_pos));		// A friend told me this would work, but it's not. Why/What do I do?
			// Dump into x_coord
			conv_to_signed >> x_coord;
		
			// Cut the string to prevent having to flush memory
			line_from_file.erase(0,current_pos+1);

			// Find next delimiter, denoting Y-Coordinate
	        current_pos = line_from_file.find_first_of(",");

			
			// Cast Y-Coordinate into temporary var
			// Put into stringstream
			istringstream conv_to_signed(line_from_file.substr(0,current_pos+1));
			// Dump into y_coord
			conv_to_signed >> y_coord;
			
			// Cut the string to prevent having to flush memory
			line_from_file.erase(0,current_pos+1);

			// Find next delimiter, denoting Country Name
	        current_pos = line_from_file.find_first_of(",");
			country_name = line_from_file;

			// Sets attributes to temporary Country object
			country_temp.setX_Coord = x_coord;
			country_temp.setY_Coord = y_coord;
			country_temp.setCountry_Name = country_name;
			
			// Pushes temporary country into Country vector
			country_vector.push_back(country_temp);			// country_vector is defined, but it doesn't seem to be getting it from the country header,  why?
          
		}
		inputfile.close();
	}

	Continents continent_temp;

	//adds continents into continent_vector
	inputfile.open("continents.txt");
	
	if (inputfile.is_open())
    {
		// Create string for getline
		string line_from_file;

		// While the file is not empty, get a line from the file and cast to line_from_file
		while (getline(inputfile,line_from_file))
		{
			// Make temporary strings
			string continent_name;
			
			// Read Continent Name from file
			continent_name = line_from_file;
			
			continent_temp.setContinent_Name = continent_name;

			continent_vector.push_back(continent_temp);
          
		}
		inputfile.close();
	}


	Country temp_a, temp_b;

	inputfile.open("links.txt");

	if(inputfile.is_open())
	{
		// Create string for getline
		string line_from_file;
		
		// While the file is not empty, get a line from the file and cast to line_from_file
		while (getline(inputfile,line_from_file))
		{
			// Make temporary strings
			string country_a, country_b;
			
			size_t current_pos;
		
			// Get X-Coordinate first
			// Find first delimiter which will give us the value
			current_pos = line_from_file.find_first_of(",");

			country_a = line_from_file;

			// Cut the string to prevent having to flush memory
			line_from_file.erase(0,current_pos+1);

			country_b = line_from_file;

			// Need to be able to add based on name/How to?
			temp_a = Country.getCountry_Name(country_a);
			temp_b = Country.getCountry_Name(country_b);
			
			addEdge(temp_a, temp_b);

		}

	}

	// Figure out how to read from file to add continents to countries
	// but without duplicating the countries in the vector
	// i.e. just adding an attribute
	// along the lines of get country by name.addContinent??
			
}
