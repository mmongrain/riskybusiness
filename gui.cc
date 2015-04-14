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
#include "stats.h"

void GUI::RevengeOfTheGUI() {
  sf::Color my_white(255, 187, 91);
  sf::Color my_whiter_white(255, 239, 199);
  sf::Color my_brown(33, 0, 51);



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
  map_info.setColor(my_brown); 
  map_info.setString(map_info_text);

  // Some Drawables (& data members) stay constant thru the game so we can get them ready before the window opens
  // Really anything that can save cycles during the loop can be declared outside
  std::vector<Territory*>         *territories = Map::Instance().get_territories();
  std::vector<Player*>            *players = Game::Instance().get_players();
  std::vector<PlayerView*>         player_views = UI::player_views; 
  std::vector<sf::Sprite>          sprites;
  std::vector<sf::Sprite>  icons;
  std::vector<sf::Sprite>          legend;
  std::vector<sf::CircleShape>     player_circles;
  std::vector<sf::Text>            player_view_text;
  std::vector<sf::Text>            labels;

  
  
  sf::Texture unit_icons;
  if (unit_icons.loadFromFile("icons.png")) {}
  else exit(0);

  sf::IntRect soldier(0, 0, 15, 15);

  sf::IntRect cavalry(14, 0, 15, 15);

  sf::IntRect cannon(29, 0, 15, 15);

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

    icons.clear();
    sprites.clear();
    labels.clear();
    player_circles.clear();
    player_view_text.clear();

    sf::Sprite legend;
    legend.setTexture(unit_icons);
    legend.setPosition(sf::Vector2f(window_size.x + 6, 10));
    labels.push_back(sf::Text(
      "1",
      pt_sans,
      12
    ));
    labels.back().setColor(my_white);
    labels.back().setPosition(sf::Vector2f(window_size.x + 11, 26));
    labels.push_back(sf::Text(
      "5",
      pt_sans,
      12
    ));
    labels.back().setColor(my_white);
    labels.back().setPosition(sf::Vector2f(window_size.x + 19, 26));
    labels.push_back(sf::Text(
      "10    [ TURN " + std::to_string(Game::Instance().get_turn()) + " ]",
      pt_sans,
      12
    ));
    labels.back().setColor(my_white);
    labels.back().setPosition(sf::Vector2f(window_size.x + 47, 26));


    // Add all the objects to be drawn this cycle
    sf::Vector2u draw_position(window_size.x + 10, 45);
    for (auto &player : *players) {

      sf::Color player_color = player->get_color();
      player_circles.push_back(sf::CircleShape(5));
      player_circles.back().setFillColor(player_color);
      player_circles.back().setPosition((float)draw_position.x, (float)draw_position.y);
      player_view_text.push_back(sf::Text());
      player_view_text.back().setFont(pt_sans);
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
        int offset = ((units_single + units_tens + units_fives)*16)/2;

        for (int i = 0; i < units_tens && unit_x < window_size.x; i++) {
          icons.push_back(sf::Sprite());
          icons.back().setPosition(unit_x - offset, unit_y - 10);
          icons.back().setTexture(unit_icons);
          icons.back().setColor(player_color);
          icons.back().setTextureRect(cannon);
          unit_x += 16;
        }

        for (int i = 0; i < units_fives && unit_x < window_size.x; i++) {
          icons.push_back(sf::Sprite());
          icons.back().setColor(player_color);
          icons.back().setPosition(unit_x - offset, unit_y - 10);
          icons.back().setTexture(unit_icons);
          icons.back().setTextureRect(cavalry);
          unit_x += 16;
        }

        for (int i = 0; i < units_single && unit_x < window_size.x; i++) {
          icons.push_back(sf::Sprite());
          icons.back().setColor(player_color);
          icons.back().setPosition(unit_x - offset, unit_y - 10);
          icons.back().setTexture(unit_icons);
          icons.back().setTextureRect(soldier);
          unit_x += 16;
        }
      }
    }

    // Dynamic map labels with ownership info
    if (Game::Instance().gui_labels) {
      for (auto &territory : *territories) {
        labels.push_back(sf::Text(
          territory->get_name() +  " (" + std::to_string(territory->get_owner()->get_id()) + ", " + std::to_string(territory->get_num_units()) + ")",
          pt_sans,
          12
        ));
        labels.back().setColor(my_brown);
        labels.back().setPosition(
          sf::Vector2f(
            (float)(territory->get_x() - 15),
            (float)(territory->get_y())
          )
        );
      }
    }
    if (Game::Instance().gui_authorinfo) { labels.push_back(map_info); }


    player_view_text.push_back(sf::Text());
    player_view_text.back().setFont(pt_sans);
		player_view_text.back().setColor(my_whiter_white);
    player_view_text.back().setCharacterSize(11);
    player_view_text.back().setPosition((float)(draw_position.x + 10), (float)(draw_position.y) + 10);
    std::string player_view_content = "";
    for (auto player_view : player_views) {
      player_view_content += player_view->get_view_str() + "\n";
    }
    player_view_content += "\n" + UI::stats->get_stats_string();
    player_view_text.back().setString(player_view_content);

    // Clear, draw, display
    window.clear(my_brown);
    window.draw(legend);
    // for (auto sprite : sprites) { window.draw(sprite); }
    for (auto player_circle : player_circles) { window.draw(player_circle); }
    for (auto player_view : player_view_text) { window.draw(player_view); }
    window.draw(map_sprite);
    for (auto icon : icons)   { window.draw(icon); } 
    for (auto label : labels)   { window.draw(label); }
    window.display();
  }
}
