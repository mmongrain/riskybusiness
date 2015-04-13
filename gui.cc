#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System.hpp>
#include <string>
#include <vector>
#include <iostream>

#include "gui.h"
#include "game.h"
#include "map.h"
#include "player.h"
#include "player_view.h"
#include "territory.h"
#include "ui.h"

void GUI::RevengeOfTheGUI() {
  // Load the .map file, load the font, get the relevant image from there
  sf::Texture map_texture;
  sf::Font pt_sans;
  sf::Font profont;
  if (!pt_sans.loadFromFile("PTSans.ttf")) {
    UI::StatusMessage("GUI: PTSans.ttf: Font not found, fool!");
    return;
  }
  if (!pt_sans.loadFromFile("ProFontWindows.ttf")) {
    UI::StatusMessage("GUI: ProFontWindows: Font not found, fool!");
    return;
  }
  if (!map_texture.loadFromFile(Map::Instance().get_image())) {
    UI::StatusMessage("GUI: Image not found, fool!");
    return;
  }

  // Set the map sprite and texture
  sf::Sprite map_sprite;
  map_sprite.setTexture(map_texture);

  // Get the window size to open from the texture size
  // Vector2u is a typedef for Vector2<unsigned int>
  sf::Vector2u window_size = map_texture.getSize();

  // Creates the map_info textbox
  std::string map_info_text = "Author: " + Map::Instance().get_author() + "\n"
                            + "Image: " + Map::Instance().get_image() + "\n"
                            + "Window size: " + std::to_string(window_size.x) 
                            + "x" + std::to_string(window_size.y) + "\n";
  sf::Text map_info;
  map_info.setFont(pt_sans);
  map_info.setCharacterSize(18);
	sf::Color my_brown(33, 0, 51);
  map_info.setColor(my_brown); 
  map_info.setString(map_info_text);

  // Some Drawables (& data members) stay constant thru the game so we can get them ready before the window opens
  // Really anything that can save cycles during the loop can be declared outside
  std::vector<Territory*>         *territories = Map::Instance().get_territories();
  std::vector<Player*>            *players = Game::Instance().get_players();
  std::vector<PlayerView*>         player_views = UI::player_views; 
  std::vector<sf::Sprite>          sprites;
  std::vector<sf::CircleShape>     circle_shapes;
  std::vector<sf::CircleShape>     triangle_shapes;
  std::vector<sf::RectangleShape>  square_shapes;
  std::vector<sf::CircleShape>     player_circles;
  std::vector<sf::Text>            player_view_text;
  std::vector<sf::Text>            labels;

  if (Game::Instance().gui_authorinfo) { labels.push_back(map_info); }
  if (Game::Instance().gui_labels) {
    for (auto &territory : *territories) {
      labels.push_back(sf::Text(
        territory->get_name(),
        pt_sans,
        12
      ));
			sf::Color my_brown(113, 24, 0);
      labels.back().setColor(my_brown);
      labels.back().setPosition(
        sf::Vector2f(
          (float)(territory->get_x() - 15),
          (float)(territory->get_y())
        )
      );
    }
  }
  
  // Create the window
  sf::RenderWindow window(sf::VideoMode(window_size.x + 300, window_size.y), "Risky Business");
  window.setFramerateLimit(15);

  // Main event loop, see SFML official tutorials
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      // EVENTS //
      // If window is closed, close the window (!)
      // That's pretty much it, this GUI is noninteractive
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    // Clear the current vectors
    circle_shapes.clear();
    triangle_shapes.clear();
    square_shapes.clear();
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
			sf::Color my_white(255, 187, 91);
      player_view_text.back().setColor(my_white);
      player_view_text.back().setCharacterSize(11);
      player_view_text.back().setPosition((float)(draw_position.x + 15), (float)(draw_position.y));
      player_view_text.back().setString(player->get_name());
      draw_position.y += 10;
      
      

      std::vector<Territory*> adjacency_list = player->get_owned_territories();

      for (auto territory : adjacency_list) {
        float unit_x = (float)territory->get_x();
        float unit_y = (float)territory->get_y();
        int units_single = territory->get_num_units();
        int units_tens = units_single/10;
        units_single %= 10;
        int units_fives = units_single/5;
        units_single %= 5;

        for (int i = 0; i < units_tens && unit_x < window_size.x; i++) {
          square_shapes.push_back(sf::RectangleShape(sf::Vector2f(10, 10)));
          square_shapes.back().setFillColor(player_color);
          square_shapes.back().setPosition(unit_x - 5, unit_y - 5);
          unit_x += 10;
        }

        for (int i = 0; i < units_fives && unit_x < window_size.x; i++) {
          triangle_shapes.push_back(sf::CircleShape(5, 3));
          triangle_shapes.back().setFillColor(player_color);
          triangle_shapes.back().setPosition(unit_x - 5, unit_y - 5);
          unit_x += 10;
        }

        for (int i = 0; i < units_single && unit_x < window_size.x; i++) {
          circle_shapes.push_back(sf::CircleShape(5));
          circle_shapes.back().setFillColor(player_color);
          circle_shapes.back().setPosition(unit_x - 5, unit_y - 5);
          unit_x += 10;
        }
      }
    }

    player_view_text.push_back(sf::Text());
    player_view_text.back().setFont(pt_sans);
		sf::Color my_whiter_white(255, 239, 199);
		player_view_text.back().setColor(my_whiter_white);
    player_view_text.back().setCharacterSize(11);
    player_view_text.back().setPosition((float)(draw_position.x + 10), (float)(draw_position.y) + 10);
    std::string player_view_content = "";
    for (auto player_view : player_views) {
      player_view_content += player_view->get_view_str() + "\n";
    }
    player_view_text.back().setString(player_view_content);

    // Clear, draw, display
    window.clear(my_brown);
    // for (auto sprite : sprites) { window.draw(sprite); }
    for (auto player_circle : player_circles) { window.draw(player_circle); }
    for (auto player_view : player_view_text) { window.draw(player_view); }
    window.draw(map_sprite);
    for (auto shape : square_shapes)   { window.draw(shape); } 
    for (auto shape : triangle_shapes)   { window.draw(shape); } 
    for (auto shape : circle_shapes)   { window.draw(shape); } 
    for (auto label : labels)   { window.draw(label); }
    window.display();
  }
}
