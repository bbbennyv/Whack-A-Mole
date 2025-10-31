
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>
#include "Text.h"

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
  bool CollisionBoxChecker(sf::Sprite sprite1, sf::Sprite sprite2);
  bool animalSprite(int animal_index);
  bool passportSprite(int passport_index);
  void newAnimal();
  void dragSprite(sf::Sprite* sprite);


 private:
  sf::RenderWindow& window;
  sf::Sprite background;
  sf::Texture background_texture;

  sf::Sprite* character;
  sf::Sprite* passport;
  sf::Sprite accept_button;
  sf::Sprite reject_button;
  sf::Sprite accept_stamp;
  sf::Sprite reject_stamp;

  sf::Sprite* dragged = nullptr;
  
  /*sf::Texture* animals = new sf::Texture[3];
  sf::Texture* passports = new sf::Texture[3];*/
  sf::Texture accept_button_texture;
  sf::Texture reject_button_texture;
  sf::Texture accept_stamp_texture;
  sf::Texture reject_stamp_texture;
  
  std::vector<std::unique_ptr< sf::Texture>> passports;
  std::vector<std::unique_ptr< sf::Texture>> animals;

  sf::Clock timer;


  Text title_text;
  Text play_text;
  Text score_text;
  Text lives_text;
  Text end_screen_text;
  Text timer_text;
  Text restart_text;
  Text quit_text;

  sf::Vector2f drag_offset = sf::Vector2f(125.0f,150.f);
  
  bool in_menu = true;

  int score = 0;
  int lives = 5; 
  
  const float countdownTime = 31.0f;

  float moved_pass_x = 0;
  float moved_pass_y = 0;


  bool passport_accept = false;
  bool passport_reject = false;
  bool should_accept = false;

  bool buttons_visible = false;
  bool accept_stamp_visible = false;
  bool reject_stamp_visible = false;
  bool stamped = false;
  bool won = false;
  bool is_dead = false;
};

#endif // PLATFORMER_GAME_H
