
#include "Game.h"
#include <iostream>
#include <vector>


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
	title_text.init("Critters || Crossing", 60);
	title_text.setColour(sf::Color::Cyan);
	title_text.setPosition(window.getSize().x / 2 - title_text.getText().getGlobalBounds().width / 2,
		20);
	
	score_text.setPosition(10, 10);
	score_text.setColour(sf::Color::Blue);
	score_text.init("Score| " +std::to_string(score), 40);
	lives_text.init("Lives| 3", 40);
	lives_text.setPosition(800, 10);
	lives_text.setColour(sf::Color::Blue);

	end_screen_text.init("         YOU DIED\n\nYour final score is\n             " + std::to_string(score),40);
	end_screen_text.setColour(sf::Color::Red);
	end_screen_text.setPosition(350,150);
	timer_text.init("31", 40);
	timer_text.setColour(sf::Color::Black);
	timer_text.setPosition(300, 10);

	restart_text.init("Restart", 40);
	restart_text.setPosition(200,500);
	restart_text.setColour(sf::Color::White);

	quit_text.init("Quit", 40);
	quit_text.setPosition(700, 500);
	quit_text.setColour(sf::Color::White);

	play_text.init("Play", 40);
	play_text.setPosition(200, 500);
	play_text.setColour(sf::Color::White);

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
	



	//initisilising the pntrs
	character = std::make_unique<sf::Sprite>();
	passport = std::make_unique<sf::Sprite>();

	//push back the different animals and passports into the vector list
	for (int i = 0; i < 3; i++)
	{

		animals.push_back(std::make_unique<sf::Texture>());

		if (i == 0)
		{
			if (!animals[0]->loadFromFile("../Data/Images/Critter Crossing Customs/Critter Crossing Customs/moose.png"))
			{
				std::cout << "Error";
			}
		}
		else if (i == 1)
		{
			if (!animals[1]->loadFromFile("../Data/Images/kenney_animalpackredux/PNG/Square/penguin.png"))
			{
				std::cout << "Error";
			}
		}
		else if (i == 2)
		{
			if (!animals[2]->loadFromFile("../Data/Images/Critter Crossing Customs/Critter Crossing Customs/elephant.png"))
			{
				std::cout << "Error";
			}
		}
	}

	for (int i = 0; i < 3; i++) 
	{
		passports.push_back(std::make_unique<sf::Texture>());
		if (i == 0)
		{
			if (!passports[0]->loadFromFile("../Data/Images/Critter Crossing Customs/Critter Crossing Customs/moose passport.png"))
			{
				std::cout << "Error";
			}
		}
		else if (i == 1)
		{
			if (!passports[1]->loadFromFile("../Data/Images/Critter Crossing Customs/Critter Crossing Customs/penguin passport.png"))
			{
				std::cout << "Error";
			}
		}
		else if (i == 2)
		{
			if (!passports[2]->loadFromFile("../Data/Images/Critter Crossing Customs/Critter Crossing Customs/elephant passport.png"))
			{
				std::cout << "Error";
			}
		}
	}
	
	newAnimal();

  return true;
}

void Game::update(float dt)
{
	if (in_menu) 
	{
		timer.restart();
	}
	if (reject_stamp_visible == true) {
		reject_stamp.setPosition(passport->getGlobalBounds().left, passport->getPosition().y);

	}
	if (accept_stamp_visible == true) {
		accept_stamp.setPosition(passport->getGlobalBounds().left, passport->getPosition().y);
	}


	dragSprite(dragged);
	if(character == nullptr && passport == nullptr) // making sure the charcter and passport are never nullptr
	{
		return;
	}
	if (CollisionBoxChecker(*character, *passport) && stamped == true && dragged == nullptr) 
	{
		if (won) 
		{
			score += 1000;
			score_text.setText("Score| " + std::to_string(score));
		}
		else 
		{
			score -= 1000;
			lives--;;
			score_text.setText("Score| " + std::to_string(score));
			lives_text.setText("Lives| " + std::to_string(lives));


		}
		newAnimal();
		
	}

	if (lives < 0)
	{
		end_screen_text.setText("         YOU DIED\n\nYour final score is\n             " + std::to_string(score));
		end_screen_text.setColour(sf::Color::Red);
		timer.restart();

		is_dead = true;
	}


	// timer where the countdownTime is being subtracted from the elapsed to the timer is actually going down instead of up
	float elapsed = timer.getElapsedTime().asSeconds();
	float remaining = countdownTime - elapsed;
	if (remaining < 0) {
		remaining = 0;
		is_dead = true;
		timer.restart();
		end_screen_text.setText("         SHIFT OVER\n\nYour final score is\n             " + std::to_string(score));
		end_screen_text.setColour(sf::Color::Green);
	}


	timer_text.setText(std::to_string(static_cast<int>(remaining)));
}

void Game::render()
{
	if (is_dead == true && in_menu == false) 
	{
		window.clear();
		window.draw(end_screen_text.getText());
		window.draw(restart_text.getText());
		window.draw(quit_text.getText());
	}
	else if (in_menu == true && is_dead == false) 
	{
		window.clear();
		window.draw(title_text.getText());
		window.draw(play_text.getText());
		window.draw(quit_text.getText());

	}
	else
	{
		window.clear();
		window.draw(background);
		window.draw(score_text.getText());
		window.draw(lives_text.getText());
		window.draw(timer_text.getText());
		window.draw(*character);
		window.draw(*passport);
		if (accept_stamp_visible == true) {
			window.draw(accept_stamp);
		}
		if (reject_stamp_visible == true) {
			window.draw(reject_stamp);
		}
		if (buttons_visible == true) 
		{
			window.draw(accept_button);
			window.draw(reject_button);
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
				accept_stamp_visible = true;
				reject_stamp_visible = false;
				stamped = true;
				won = true;
			}
			else 
			{
				accept_stamp_visible = true;
				stamped = true;
				won = false;
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
				reject_stamp.setPosition(500, 70);
				reject_stamp_visible = true;
				stamped = true;
				won = false;
				accept_stamp_visible = false;
			}
			else 
			{
				reject_stamp_visible = true;
				stamped = true;
				won = true;
				accept_stamp_visible = false;
			}
			accept_button.setColor(sf::Color::White);
			reject_button.setColor(sf::Color{ 55, 55, 55, 185 });
		}
		sf::Vector2i click = sf::Mouse::getPosition(window);
		sf::Vector2f clickf = static_cast<sf::Vector2f>(click);
		if (passport->getGlobalBounds().contains(clickf)) 
		{
			drag_offset = clickf - passport.get()->getPosition();//no mouse snap when moving the passport
			dragged = passport.get();
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
		timer.restart();
		if (is_dead == true) 
		{
			if (restart_text.getText().getString() == "<Restart>") //reset logic
			{
				timer.restart();
				is_dead = false;
				won = false;
				score = 0;
				lives = 5;
				in_menu = false;
				score_text.setText("Score| " + std::to_string(score));
				lives_text.setText("Lives| " + std::to_string(lives));
				buttons_visible = false;
				accept_stamp_visible = false;
				reject_stamp_visible = false;
			}
			if (quit_text.getText().getString() == "<Quit>") 
			{
				window.close();
			}
		}
	}
	if (is_dead == true) 
	{
		if (event.key.code == sf::Keyboard::Left) 
		{
			restart_text.setText("<Restart>");
			quit_text.setText("Quit");
		}

		if (event.key.code == sf::Keyboard::Right)
		{
			restart_text.setText("Restart");
			quit_text.setText("<Quit>");
		}
		
	}

}


bool Game::CollisionChecker(sf::Vector2i click, sf::Sprite sprite) //collision checker with mouse and any sprite to interact with
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


bool Game::CollisionBoxChecker(sf::Sprite sprite1, sf::Sprite sprite2) //collision checker with two sprites
{
	if (sprite1.getGlobalBounds().left > sprite2.getGlobalBounds().left  &&
		sprite1.getGlobalBounds().left < sprite2.getGlobalBounds().left + sprite2.getGlobalBounds().width &&
		sprite1.getGlobalBounds().top > sprite2.getGlobalBounds().top &&
		sprite1.getGlobalBounds().top < sprite2.getGlobalBounds().top + sprite2.getGlobalBounds().height) {

		return true;
	}
	else {
		return false;
	}
}





void Game::newAnimal()
{
	passport_accept = false;
	passport_reject = false;

	int animal_index_temp = rand() % 3; // random animal and passport
	int passport_index_temp = rand() % 3; // chooses a random num between 0 and 3

	if (animal_index_temp == passport_index_temp) 
	{
		should_accept = true;
	}
	else 
	{
		should_accept = false;
	}




	character->setTexture(*animals.at(animal_index_temp),true); // sets the character to the texture of the animal with the index randomly chosen from the vector list
	character->setScale(1, 1);
	character->setPosition(window.getSize().x / 12, window.getSize().y / 12);
	
	passport->setTexture(*passports.at(passport_index_temp),true);
	passport->setScale(0.6,0.6);
	passport->setPosition(200, 200);
	accept_stamp_visible = false;
	reject_stamp_visible = false;
	reject_button.setColor(sf::Color::White);
	accept_button.setColor(sf::Color::White);
	stamped = false;
}

void Game::dragSprite(sf::Sprite* sprite)
{
	if (sprite != nullptr) //this allows the player to only drag one sprite at a time
	{
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(window); 
		sf::Vector2f mouse_posf = static_cast<sf::Vector2f>(mouse_pos);

		sf::Vector2f drag_position = mouse_posf - drag_offset;
		sprite->setPosition(drag_position);
		moved_pass_x = sprite->getPosition().x;
		moved_pass_y = sprite->getPosition().y;
	}


}


