
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
	if (!background_texture.loadFromFile("../Data/WhackaMole Worksheet/background.png")) {
		std::cout << "NO BACKGROUND";
	}
	background.setTexture(background_texture);
	if (!bird_texture.loadFromFile("../Data/WhackaMole Worksheet/bird.png")) {
		std::cout << "NO BIRD";
	}
	bird.setTexture(bird_texture);
	bird.setPosition(200, 100);
	bird.setScale(0.5, 0.5);
	if (!normal_font.loadFromFile("../Data/Fonts/OpenSans-Bold.ttf")) {
		std::cout << "NO FONT";
	}
	title_text.setString("WHACK A MOLEE");
	title_text.setFont(normal_font);
	title_text.setColor(sf::Color::Cyan);
	title_text.setPosition(window.getSize().x / 2 - title_text.getGlobalBounds().width / 2,
		20);
	title_text.setCharacterSize(20);
	play_text.setFont(normal_font);
	play_text.setString("Press Enter to Start");
	play_text.setCharacterSize(20);
	play_text.setPosition(100, 200);
	play_text.setColor(sf::Color::Cyan);
	score_text.setFont(normal_font);
	score_text.setPosition(10, 10);
	score_text.setColor(sf::Color::Blue);
	score_text.setString(std::to_string(score));

  return true;
}

void Game::update(float dt)
{
	if (bird.getGlobalBounds().left > window.getSize().x - bird.getGlobalBounds().width || bird.getGlobalBounds().left < 0) {
		is_reversed = !is_reversed;
	}
	if (is_reversed == false) {
		bird.move(1.0f * speed * dt, 0);
		bird.setTextureRect(sf::IntRect(
			0, 0, bird.getLocalBounds().width, bird.getLocalBounds().height));
	}
	else {
		bird.setTextureRect(sf::IntRect(
			bird.getLocalBounds().width,
			0,
			-bird.getLocalBounds().width,
			bird.getLocalBounds().height));
		bird.move(-1.0f * speed * dt, 0);
	}
}

void Game::render()
{
	if (in_menu == true) 
	{
		window.clear();
		window.draw(title_text);
		window.draw(play_text);
	}
	else
	{
		window.clear();
		window.draw(background);
		window.draw(bird);
		window.draw(score_text);
	}
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
  if (CollisionChecker(click, bird)){
	  spawn();
	  score++;
	  score_text.setString(std::to_string(score));
  }

}

void Game::keyPressed(sf::Event event)
{
	if (event.key.code == sf::Keyboard::Enter) {
		in_menu = false;
	}
}


bool Game::CollisionChecker(sf::Vector2i click, sf::Sprite sprite) 
{
	if (click.x > sprite.getGlobalBounds().left &&
		click.x < sprite.getGlobalBounds().left + sprite.getGlobalBounds().width &&
		click.y > sprite.getGlobalBounds().top &&
		click.y < sprite.getGlobalBounds().top + sprite.getGlobalBounds().height) {
		return true;
	}
	else {
		return false;
	}
}

void Game::spawn() 
{
	int x = rand() % (window.getSize().x - (int)bird.getGlobalBounds().width);
	int y = rand() % (window.getSize().y - (int)bird.getGlobalBounds().height);
	bird.setPosition(x, y);

}


