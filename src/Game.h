
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  bool CollisionChecker(sf::Vector2i clcik,sf::Sprite sprite);
  void spawn();


 private:
  sf::RenderWindow& window;
  sf::Sprite ball;
  sf::Texture ball_texture;
  sf::Sprite background;
  sf::Texture background_texture;
  sf::Sprite bird;
  sf::Texture bird_texture;

  sf::Font normal_font;
  sf::Text title_text;
  sf::Text play_text;
  sf::Text score_text;

  bool in_menu = true;
  bool is_reversed = false;
  bool is_reversed_Y = false;
  float speed = 200;
  int score = 0;
};

#endif // PLATFORMER_GAME_H
