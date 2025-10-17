
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{
	delete[] animals;
	delete[] passports;
	delete character;
	delete passport;

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


	if (!accept_button_texture.loadFromFile("../Data/Images/Critter Crossing Customs/Critter Crossing Customs/accept button.png")) 
	{
		std::cout << "no accept button";
	}
	if (!reject_button_texture.loadFromFile("../Data/Images/Critter Crossing Customs/Critter Crossing Customs/reject button.png"))
	{
		std::cout << "no accept button";
	}
	if (!accept_stamp_texture.loadFromFile("../Data/Images/Critter Crossing Customs/Critter Crossing Customs/accept.png"))
	{
		std::cout << "no accept stamp";
	}
	if (!reject_stamp_texture.loadFromFile("../Data/Images/Critter Crossing Customs/Critter Crossing Customs/reject.png"))
	{
		std::cout << "no accept stamp";
	}
	
	accept_button.setTexture(accept_button_texture);
	accept_button.setPosition(700, 300);
	reject_button.setTexture(reject_button_texture);
	reject_button.setPosition(700, 410);
	accept_stamp.setTexture(accept_stamp_texture);
	reject_stamp.setTexture(reject_stamp_texture);
	



	character = new sf::Sprite;
	passport = new sf::Sprite;






	newAnimal();
	




  return true;
}

void Game::update(float dt)
{
	

	reject_stamp.setPosition(passport->getGlobalBounds().left, passport->getPosition().y);
	accept_stamp.setPosition(passport->getGlobalBounds().left, passport->getPosition().y);


	dragSprite(dragged);
	if(moved_pass_x == )

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
		window.draw(*character);
		window.draw(*passport);
		if (buttons_visible == true) 
		{
			window.draw(accept_button);
			window.draw(reject_button);
		}
		if (accept_stamp_visible == true) {
			window.draw(accept_stamp);
		}
		if (reject_stamp_visible == true) {
			window.draw(reject_stamp);
		}

	}
}

void Game::mouseButtonPressed(sf::Event event)
{
  //get the click position

    sf::Vector2i click = sf::Mouse::getPosition(window);
	if (event.mouseButton.button == sf::Mouse::Right) 
	{
		buttons_visible = !buttons_visible;

	}
	
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		if (CollisionChecker(click, accept_button) && buttons_visible == true)
		{
			passport_accept = true;
			if (should_accept == passport_accept) 
			{
				std::cout << "WIJ";
				accept_stamp_visible = true;
				reject_stamp_visible = false;
				stamped = true;
			}
			else 
			{
				std::cout << "loss"; 
				accept_stamp_visible = true;
				stamped = true;
				reject_stamp_visible = false;
			}
			accept_button.setColor(sf::Color{ 55, 55, 55, 185 });
			reject_button.setColor(sf::Color::White);


		}
		if (CollisionChecker(click, reject_button) && buttons_visible == true)
		{
			passport_reject = true;
			if (should_accept == passport_reject ) 
			{
				std::cout << "LOSSS";
				reject_stamp.setPosition(500, 70);
				reject_stamp_visible = true;
				stamped = true;
				accept_stamp_visible = false;
			}
			else 
			{
				std::cout << "Win"; 
				reject_stamp_visible = true;
				stamped = true;
				accept_stamp_visible = false;
			}
			accept_button.setColor(sf::Color::White);
			reject_button.setColor(sf::Color{ 55, 55, 55, 185 });
		}
		sf::Vector2i click = sf::Mouse::getPosition(window);
		sf::Vector2f clickf = static_cast<sf::Vector2f>(click);
		if (passport->getGlobalBounds().contains(clickf)) 
		{
			dragged = passport;
		}
	}




}

void Game::mouseButtonReleased(sf::Event event)
{
	dragged = nullptr;


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

bool Game::animalSprite(int animal_index)
{
	if (animal_index == 0) {
		if (!animals[0].loadFromFile("../Data/Images/Critter Crossing Customs/Critter Crossing Customs/moose.png"))
		{
			std::cout << "Error";
		}
	}
	else if (animal_index == 1) {
		if (!animals[1].loadFromFile("../Data/Images/kenney_animalpackredux/PNG/Square/penguin.png"))
		{
			std::cout << "Error";
		}
	}
	else if (animal_index == 2) {
		if (!animals[2].loadFromFile("../Data/Images/Critter Crossing Customs/Critter Crossing Customs/elephant.png"))
		{
			std::cout << "Error";
		}
	}
	character->setTexture(animals[animal_index]);
	return true;
}

bool Game::passportSprite(int passport_index)
{
	if (passport_index == 0) {
		if (!passports[0].loadFromFile("../Data/Images/Critter Crossing Customs/Critter Crossing Customs/moose passport.png")) 
		{
			std::cout << "Error";
		}
	}
	else if (passport_index == 1) {
		if (!passports[1].loadFromFile("../Data/Images/Critter Crossing Customs/Critter Crossing Customs/penguin passport.png"))
		{
			std::cout << "Error";
		}
	}
	else if (passport_index == 2) {
		if (!passports[2].loadFromFile("../Data/Images/Critter Crossing Customs/Critter Crossing Customs/elephant passport.png"))
		{
			std::cout << "Error";
		}
	}
	passport->setTexture(passports[passport_index]);
	
	return true;
}

void Game::newAnimal()
{
	passport_accept = false;
	passport_reject = false;

	int animal_index_temp = rand() % 3;
	int passport_index_temp = rand() % 3;

	if (animal_index_temp == passport_index_temp) 
	{
		should_accept = true;
		std::cout << animal_index_temp;
		std::cout << passport_index_temp;
	}
	else 
	{
		should_accept = false; std::cout << animal_index_temp;
		std::cout << passport_index_temp;
	}





	animalSprite(animal_index_temp);
	character->setScale(1.8, 1.8);
	character->setPosition(window.getSize().x / 12, window.getSize().y / 12);

	passportSprite(passport_index_temp);
	passport->setScale(0.6,0.6);
	passport->setPosition(window.getSize().x / 2, window.getSize().y / 3);



}

void Game::dragSprite(sf::Sprite* sprite)
{
	if (sprite != nullptr) 
	{
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
		sf::Vector2f mouse_posf = static_cast<sf::Vector2f>(mouse_pos);

		sf::Vector2f drag_position = mouse_posf - drag_offset;
		sprite->setPosition(drag_position);
		moved_pass_x = sprite->getPosition().x;
		moved_pass_y = sprite->getPosition().y;
	}


}


