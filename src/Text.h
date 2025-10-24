#ifndef PLATFORMER_TEXT_H
#define PLATFORMER_TEXT_H

#include <SFML/Graphics.hpp>

class Text 
{
public:
	Text();
	~Text();
	void init(std::string string,int character_size);
	void setPosition(int pos_x,int pos_y);
	void setColour(sf::Color colour);
	sf::Text getText();
	void setText(sf::String text);


	sf::Text textitem;
	sf::Font font;


private:

};
#endif // PLATFORMER_TEXT_H
