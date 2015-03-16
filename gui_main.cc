#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>

#include "game.h"
#include "map.h"
#include "player.h"
#include "territory.h"

int main() {
  // Load the map, start the game. PlayerViewTestHelper randomly assigns countries.
  char FILENAME[100] = "World.map";
  Map::Instance().Load(FILENAME);
  sf::Thread test_thread(&Game::PlayGame);
  test_thread.launch();

  // Load the .map file, load the font, get the relevant image from there
  char filename[100] = "World.map";
  Map::Instance().Load(filename);
  sf::Texture map_texture;
  sf::Font pt_sans;

  if (!pt_sans.loadFromFile("PTSans.ttf")) {
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
  sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "Risky Business");

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

  // Main event loop, see SFML official tutorials
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      // Create a vector to store all the sprites that will be drawn this loop
      std::vector<sf::Sprite>       sprites;
      std::vector<sf::Text>         texts;
      std::vector<sf::CircleShape>  shapes;

      // EVENTS //
      // If window is closed, close the window (!)
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      // If mouse button is pressed, do something
      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Right) {
          std::cout << "Right click ";
        } else if (event.mouseButton.button == sf::Mouse::Left) {
          std::cout << "Left click ";
        }
        std::cout << "[x: " << event.mouseButton.x << ", y: " << event.mouseButton.y << "]" << std::endl;
      }

      // Add all the objects to be drawn this cycle
      std::vector<Territory*> territories = Map::Instance().get_copy_territories();
      std::vector<Player*> players = Game::Instance().get_copy_players();
      sprites.push_back(map_sprite);

      for (auto &player : players) {
        sf::Color player_color;
        switch (player->get_id()) {
          case 0:  player_color = sf::Color::Magenta;
                   break;
          case 1:  player_color = sf::Color::Red;
                   break;
          case 2:  player_color = sf::Color::Blue;
                   break;
          case 3:  player_color = sf::Color::Green;
                   break;
          case 4:  player_color = sf::Color::Yellow;
                   break;
          case 5:  player_color = sf::Color::Cyan;
                   break;
          default: player_color = sf::Color::Black;
        }

        std::vector<Territory*> adjacency_list = player->get_owned_territories();

        for (auto territory : adjacency_list) {
          float unit_x = (float)territory->get_x();
          float unit_y = (float)territory->get_y();
          for (int i = 0; i < territory->get_num_units(); i++) {
            shapes.push_back(sf::CircleShape(5));
            shapes.back().setFillColor(player_color);
            shapes.back().setPosition(unit_x - 5, unit_y - 5);
            unit_x += 5;
          }
        }
      }

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

      texts.push_back(map_info);
      for (auto &territory : territories) {
        texts.push_back(sf::Text(
          territory->get_name(),
          pt_sans,
          12
        ));
        texts.back().setColor(sf::Color::Black);
        texts.back().setPosition(
          sf::Vector2f(
            (float)(territory->get_x() - 15),
            (float)(territory->get_y())
          )
        );
      }

      // Clear, draw, display
      window.clear(sf::Color::Black);
      for (auto sprite : sprites) { window.draw(sprite); }
      for (auto shape : shapes)   { window.draw(shape); } 
      for (auto text : texts)     { window.draw(text); }
      window.display();
    }
  }
  return 0;
}
