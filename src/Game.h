
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
  void mouseButtonPressed(sf::Event event);
  void mouseButtonReleased(sf::Event event);
  void keyPressed(sf::Event event);
  bool CollisionChecker(sf::Vector2i clcik,sf::Sprite sprite);
  void spawn();
  bool animalSprite(int animal_index);
  bool passportSprite(int passport_index);
  void newAnimal();
  void dragSprite(sf::Sprite* sprite);


 private:
  sf::RenderWindow& window;
  sf::Sprite ball;
  sf::Texture ball_texture;
  sf::Sprite background;
  sf::Texture background_texture;
  sf::Sprite bird;
  sf::Texture bird_texture;

  sf::Sprite* character;
  sf::Sprite* passport;

  sf::Sprite* dragged = nullptr;
  
  sf::Texture* animals = new sf::Texture[3];
  sf::Texture* passports = new sf::Texture[3];




  sf::Font normal_font;
  sf::Text title_text;
  sf::Text play_text;
  sf::Text score_text;

  sf::Vector2f drag_offset = sf::Vector2f(50.0f, 50.f);
  
  bool in_menu = true;
  bool is_reversed = false;
  bool is_reversed_Y = false;
  float speed = 200;
  int score = 0;


  bool passport_accept = false;
  bool passport_reject = false;
  bool should_accept = false;


};

#endif // PLATFORMER_GAME_H
