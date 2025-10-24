#include "Text.h"
#include <iostream>


Text::Text()
{
	srand(time(NULL));
}

Text::~Text()
{

}

void Text::init(std::string string, int character_size)
{
	textitem.setString(string);
	if (!font.loadFromFile("../Data/Fonts/OpenSans-Bold.ttf")) {
		std::cout << "NO FONT";
	}
	textitem.setFont(font);
	textitem.setColor(sf::Color::White);
	textitem.setCharacterSize(character_size);
}

void Text::setPosition(int pos_x, int pos_y)
{
	textitem.setPosition(pos_x, pos_y);
}

void Text::setColour(sf::Color colour)
{
	textitem.setColor(colour);
}

sf::Text Text::getText()
{
	return textitem;
}

