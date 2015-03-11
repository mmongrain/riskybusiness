#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <string>
#include "map.h"

int main() {
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

  // Get the window size to open from the texture size
  // Vector2u is a typedef for Vector2<unsigned int>
  sf::Vector2u window_size = map_texture.getSize();
  sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "Risky Business");

  // Creates the map_info textbox
  std::string map_info_text = "Author: " + Map::Instance().get_author() + "\n"
                            + "Image: " + Map::Instance().get_image() + "\n"
                            + "Window size: " + std::to_string(window_size.x) + "x" + std::to_string(window_size.y) + "\n";
  sf::Text map_info;
  map_info.setFont(pt_sans);
  map_info.setCharacterSize(18);
  map_info.setColor(sf::Color::Black); 
  map_info.setString(map_info_text);

  // Main event loop, see SFML official tutorials
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Right) {
          std::cout << "Right click ";
        } else if (event.mouseButton.button == sf::Mouse::Left) {
          std::cout << "Left click ";
        }
        std::cout << "[x: " << event.mouseButton.x << ", y: " << event.mouseButton.y << "]" << std::endl;
      }
      window.clear(sf::Color::Black);
      window.draw(map_sprite);
      window.draw(map_info);
      window.display();
    }
  }
  return 0;
}
