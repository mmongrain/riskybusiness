#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System.hpp>
#include <stdlib.h> // srand();
#include <iostream>
#include <string>
#include <thread>
#include "game_builder.h"
#include "game_in_progress_builder.h"
#include "game_loader.h"
#include "game.h"
#include "map.h"
#include "player.h"
#include "territory.h"

int main(int argc, char *argv[]) {
	// Load the map, start the game. PlayerViewTestHelper randomly assigns countries.
	srand(time(NULL));

	// Load the .map file, load the font, get the relevant image from there
	sf::Texture map_texture;
	sf::Font pt_sans;
	sf::Font profont;

	// Choose between new game or loading a saved game
	std::cout << "Start new game (1) or load saved game(2)?" << std::endl;
	int answer;
	std::cin >> answer;
	std::cin.clear();
	std::cin.ignore(1000, '\n');
	bool new_game = true;
	while (answer != 1 && answer != 2)
	{
		std::cout << "Wrong input! Press 1 to start a new game or 2 to load a saved game" << std::endl;
		std::cin >> answer;
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}
	if (answer == 1){
		new_game = true;
		char filename[100] = "World.map";
		Map::Instance().Load(filename);
		Game::Instance().newly_loaded_game = false;
	}
	else {
		new_game = false;
		GameLoader my_loader;	// creating the director
		GameBuilder* my_builder = new GameInProgressBuilder(); // creating the concrete builder
		my_loader.set_game_builder(my_builder); // tell the director which builder to use
		my_loader.build_game("gamesave.txt"); // tell the director to build the game
		delete my_builder;
		Game::Instance().newly_loaded_game = true;
	}



	if (!pt_sans.loadFromFile("PTSans.ttf")) {
		std::cout << "Font not found, fool!" << std::endl;
	}
	if (!pt_sans.loadFromFile("ProFontWindows.ttf")) {
		std::cout << "Font not found, fool!" << std::endl;
	}
	if (!map_texture.loadFromFile(Map::Instance().get_image())) {
		std::cout << "Image not found, fool!" << std::endl;
	}

	// Set the map sprite and texture
	sf::Sprite map_sprite;
	map_sprite.setTexture(map_texture);

	// Get the spritesheet and set a default rect
	sf::Texture sprite_sheet;
	sprite_sheet.loadFromFile("textures/1945.png");
	sf::IntRect subrect;
	subrect.left = 4;
	subrect.width = 31;
	subrect.top = 4;
	subrect.height = 31;
	sf::Sprite marker(sprite_sheet, subrect);

	// Get the window size to open from the texture size
	// Vector2u is a typedef for Vector2<unsigned int>
	sf::Vector2u window_size = map_texture.getSize();
	std::thread logic_thread(&Game::PlayGame);

	// Creates the map_info textbox
	std::string map_info_text = "Author: " + Map::Instance().get_author() + "\n"
		+ "Image: " + Map::Instance().get_image() + "\n"
		+ "Window size: " + std::to_string(window_size.x)
		+ "x" + std::to_string(window_size.y) + "\n";
	sf::Text map_info;
	map_info.setFont(pt_sans);
	map_info.setCharacterSize(18);
	map_info.setColor(sf::Color::Black);
	map_info.setString(map_info_text);

	// Some Drawables (& data members) stay constant thru the game so we can get them ready before the window opens
	// Really anything that can save cycles during the loop can be declared outside
	std::vector<Territory*>      *territories = Map::Instance().get_territories();
	std::vector<Player*>         *players = Game::Instance().get_players();
	std::vector<PlayerView*>     *player_views = Game::Instance().get_player_views();
	std::vector<sf::Sprite>      sprites;
	std::vector<sf::CircleShape> shapes;
	std::vector<sf::CircleShape> player_circles;
	std::vector<sf::Text>        player_view_text;
	std::vector<sf::Text>        labels;
	labels.push_back(map_info);
	for (auto &territory : *territories) {
		labels.push_back(sf::Text(
			territory->get_name(),
			pt_sans,
			12
			));
		labels.back().setColor(sf::Color::Black);
		labels.back().setPosition(
			sf::Vector2f(
			(float)(territory->get_x() - 15),
			(float)(territory->get_y())
			)
			);
	}

	// Create the window
	sf::RenderWindow window(sf::VideoMode(window_size.x + 300, window_size.y), "Risky Business");
	window.setFramerateLimit(15);

	// Main event loop, see SFML official tutorials
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			// Create a vector to store all the sprites that will be drawn this loop

			// EVENTS //
			// If window is closed, close the window (!)
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			// If mouse button is pressed, do something
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Right) {
					std::cout << "Right click ";
				}
				else if (event.mouseButton.button == sf::Mouse::Left) {
					std::cout << "Left click ";
				}
				std::cout << "[x: " << event.mouseButton.x << ", y: " << event.mouseButton.y << "]" << std::endl;
			}

		}
		// Clear the current vectors
		shapes.clear();
		sprites.clear();
		player_circles.clear();
		player_view_text.clear();

		// Add all the objects to be drawn this cycle

		sf::Vector2u draw_position(window_size.x + 10, 10);
		for (auto &player : *players) {

			sf::Color player_color = player->get_color();
			player_circles.push_back(sf::CircleShape(5));
			player_circles.back().setFillColor(player_color);
			player_circles.back().setPosition((float)draw_position.x, (float)draw_position.y);
			player_view_text.push_back(sf::Text());
			player_view_text.back().setFont(pt_sans);
			player_view_text.back().setColor(sf::Color::White);
			player_view_text.back().setCharacterSize(11);
			player_view_text.back().setPosition((float)(draw_position.x + 15), (float)(draw_position.y));
			player_view_text.back().setString(player->get_name());
			draw_position.y += 10;



			std::vector<Territory*> adjacency_list = player->get_owned_territories();

			for (auto territory : adjacency_list) {
				float unit_x = (float)territory->get_x();
				float unit_y = (float)territory->get_y();
				for (int i = 0; i < territory->get_num_units() && unit_x < window_size.x; i++) {
					shapes.push_back(sf::CircleShape(5));
					shapes.back().setFillColor(player_color);
					shapes.back().setPosition(unit_x - 5, unit_y - 5);
					unit_x += 5;
				}
			}
		}
		player_view_text.push_back(sf::Text());
		player_view_text.back().setFont(pt_sans);
		player_view_text.back().setColor(sf::Color::White);
		player_view_text.back().setCharacterSize(11);
		player_view_text.back().setPosition((float)(draw_position.x + 10), (float)(draw_position.y) + 10);
		std::string player_view_content = "";
		for (auto player_view : *player_views) {
			player_view_content += player_view->get_view_str() + "\n";
		}
		player_view_text.back().setString(player_view_content);



		/* Prints a sprite on each territory
		for (auto &territory : territories) {
		sprites.push_back(sf::Sprite(sprite_sheet, subrect));
		sprites.back().setPosition(
		sf::Vector2f(
		(float)(territory->get_x() - 15),
		(float)(territory->get_y() - 15)
		)
		);
		}*/

		// Clear, draw, display
		window.clear(sf::Color::Black);
		// for (auto sprite : sprites) { window.draw(sprite); }
		for (auto player_circle : player_circles) { window.draw(player_circle); }
		for (auto player_view : player_view_text) { window.draw(player_view); }
		window.draw(map_sprite);
		for (auto shape : shapes)   { window.draw(shape); }
		//for (auto label : labels)   { window.draw(label); }
		window.display();
	}
	return 0;
}
