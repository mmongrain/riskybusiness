#include <SFML/Graphics.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Risky Business");
  sf::Texture texture;
  if (!texture.loadFromFile("World.bmp")) {
  }
  sf::Sprite map_sprite;
  map_sprite.setTexture(texture);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      window.clear(sf::Color::Black);
      window.draw(map_sprite);
      window.display();
    }
  }
  return 0;
}
