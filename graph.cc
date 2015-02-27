/*

#include "graph.h"

// TODO: convert these functions to use Map::Territory and associated accessors

// In source files, how to properly declare methods and stuff?
// This is exactly correct!   --Matthew

Graph::Graph(int size) {
	this->size = size;
	array = new GraphList [size];
	for(int i = 0; i < size; i++)
		array[i].head = NULL;
}

//Creating new node
GraphNode* NewGraphNode(Country destination) {
	// Is it possible to have a Country as a Node and not an int? Why is destination not working
		// -> in the definition of GraphNode (in country.cc), destination is an integer, so it's expecting an int, not a Country object
	GraphNode* new_node = new GraphNode;
	new_node->destination = destination;
	new_node->next = NULL;
	return new_node;
}

//add edge between nodes to map
void AddEdge(Country source, Country destination) {
	GraphNode* new_node = NewGraphNode(destination);
	new_node->next = array[source].head;		// Why is array undefined?
	array[source].head = new_node;
	new_node = NewGraphNode(source);
	new_node->next = array[destination].head;
	array[destination].head = new_node;
}

//print map
void PrintGraph() {
	for(int i = 0; i < sizeof(Graph); i++) {
		GraphNode* ptr = array[i].head;
		std::cout << "\nAdjacency list of Node: " << i;
		while(ptr) {
			std::cout<<"-> " <<ptr->destination;
			ptr = ptr->next;
		}
		std::cout<< std::endl;
	}
}

void MakeGraph() {
	std::ifstream input_file;
	Country country_temp;

	//adds countries into country_vector
	input_file.open("countries.txt");
	
	if (input_file.is_open()) {
		// Create std::string for getline
		std::string line_from_file;

		// While the file is not empty, get a line from the file and cast to line_from_file
		while (getline(input_file,line_from_file)) {
			// Make temporary std::strings
			std::string country_name;
			int x_coord, y_coord;
			
			size_t current_pos;
		
			// Get X-Coordinate first
			// Find first delimiter which will give us the value
			current_pos = line_from_file.find_first_of(",");
		
			// Cast X-Coordinate into temporary var
			// Put into std::stringstream
			istd::stringstream conv_to_signed(line_from_file.substr(0,current_pos));		// A friend told me this would work, but it's not. Why/What do I do?
			// Dump into x_coord
			conv_to_signed >> x_coord;
		
			// Cut the std::string to prevent having to flush memory
			line_from_file.erase(0,current_pos+1);

			// Find next delimiter, denoting Y-Coordinate
	    current_pos = line_from_file.find_first_of(",");

			
			// Cast Y-Coordinate into temporary var
			// Put into std::stringstream
			istd::stringstream conv_to_signed(line_from_file.substr(0,current_pos+1));
			// Dump into y_coord
			conv_to_signed >> y_coord;
			
			// Cut the std::string to prevent having to flush memory
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
		input_file.close();
	}

	Continents continent_temp;

	//adds continents into continent_vector
	input_file.open("continents.txt");
	
	if (input_file.is_open()) {
		// Create std::string for getline
		std::string line_from_file;

		// While the file is not empty, get a line from the file and cast to line_from_file
		while (getline(input_file,line_from_file)) {
			// Make temporary std::strings
			std::string continent_name;
			
			// Read Continent Name from file
			continent_name = line_from_file;
			
			continent_temp.setContinent_Name = continent_name;

			continent_vector.push_back(continent_temp);
          
		}
		input_file.close();
	}


	Country temp_a, temp_b;

	input_file.open("links.txt");

	if(input_file.is_open()) {
		// Create std::string for getline
		std::string line_from_file;
		
		// While the file is not empty, get a line from the file and cast to line_from_file
		while (getline(input_file,line_from_file)) {
			// Make temporary std::strings
			std::string country_a, country_b;
			
			size_t current_pos;
		
			// Get X-Coordinate first
			// Find first delimiter which will give us the value
			current_pos = line_from_file.find_first_of(",");

			country_a = line_from_file;

			// Cut the std::string to prevent having to flush memory
			line_from_file.erase(0,current_pos+1);

			country_b = line_from_file;

			// Need to be able to add based on name/How to?
			temp_a = Country.getCountry_Name(country_a);
			temp_b = Country.getCountry_Name(country_b);
			
			AddEdge(temp_a, temp_b);

		}

	}

	// Figure out how to read from file to add continents to countries
	// but without duplicating the countries in the vector
	// i.e. just adding an attribute
	// along the lines of get country by name.addContinent??
			
}
*/