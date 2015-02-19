#include "country.h"
#include "continent.h"
#include "country.cpp"
#include "continent.cpp"

using namespace std;

int main()
{
	// Create the Country graph and then add the edges between the Countries
	Graph grcountry(5);
	grcountry.addEdge(Shire,Minhiriath);
	grcountry.addEdge(Shire,Erebor);
	grcountry.addEdge(Minhiriath,Enedwaith);
	grcountry.addEdge(Minhiriath,Mirkwood);
	grcountry.addEdge(Minhiriath,Erebor);
	grcountry.addEdge(Enedwaith,Mirkwood);
	grcountry.addEdge(Mirkwood,Erebor);

	grcountry.printCountry();


	// Create the continent graph and then add the edges between the Continents
	Graph grcont(4);
	grcont.addEdge(Eriador,Rhovanion);
	grcont.addEdge(Rhovanion, Mordor);
	grcont.addEdge(Rhovanion,Rhun);

	grcont.printContinent();

	// Creates the country object, and sets the known attributes
	Country shire;
	shire.setCountryName("Shire");
	shire.setContinent("Eriador");

	// Creates the continent object, and sets its name
	Continent eriador;
	eriador.setContinentName("Eriador");

	cin.get();
	return 0;
}