#include "country.h"
#include "continent.h"
#include "country.cc"
#include "continent.cc"

int main() {
	// Create the Country graph and then add the edges between the Countries
	Graph grcountry(5);
	grcountry.AddEdge(Shire,Minhiriath);
	grcountry.AddEdge(Shire,Erebor);
	grcountry.AddEdge(Minhiriath,Enedwaith);
	grcountry.AddEdge(Minhiriath,Mirkwood);
	grcountry.AddEdge(Minhiriath,Erebor);
	grcountry.AddEdge(Enedwaith,Mirkwood);
	grcountry.AddEdge(Mirkwood,Erebor);

	grcountry.PrintCountry();

	// Create the continent graph and then add the edges between the Continents
	Graph grcont(4);
	grcont.AddEdge(Eriador,Rhovanion);
	grcont.AddEdge(Rhovanion, Mordor);
	grcont.AddEdge(Rhovanion,Rhun);

	grcont.PrintContinent();

	// Creates the country object, and sets the known attributes
	Country shire;
	shire.set_country_name("Shire");
	shire.set_continent("Eriador");

	// Creates the continent object, and sets its name
	Continent eriador;
	eriador.set_continent_name("Eriador");

	cin.get();
	return 0;
}
