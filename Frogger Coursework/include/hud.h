#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>

using namespace std;

class Hud : public sf::Drawable
{
private:

public:
	Hud();

	sf::Font m_FontConitionFont;	//font used for score and lives text http://www.1001fonts.com/condition-font.html 
	sf::Text m_TextPlayerScore;	//text which holds for the players score
	sf::Text m_TextScoreLabel;	//text label for the players score

	sf::Text m_TextPlayerLives;	//text which holds for the players lives
	sf::Text m_TextLivesLabel;	//text label for the players lives


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;	//used to draw the objects to the screen
};