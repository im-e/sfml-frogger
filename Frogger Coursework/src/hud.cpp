#include "hud.h"

Hud::Hud()
{				//load in font
	if (!m_FontConitionFont.loadFromFile(".\\assets\\fonts\\Condition-Regular.ttf"))	//if the font fails to load
	{
		cout << "Font Error" << endl;			//output error
	}
	
	m_TextPlayerScore.setFont(m_FontConitionFont); //set attributes to my text and labels
	m_TextPlayerScore.setPosition(110, 555);		//sets the position of the text
	m_TextPlayerScore.setCharacterSize(32);		//sets the size of the text
	m_TextPlayerScore.setFillColor(sf::Color::Cyan);	//sets the colour of the text

	m_TextScoreLabel.setFont(m_FontConitionFont);
	m_TextScoreLabel.setPosition(10, 555);
	m_TextScoreLabel.setCharacterSize(32);
	m_TextScoreLabel.setFillColor(sf::Color::Cyan);
	m_TextScoreLabel.setString("Score:");			//sets the string that will displayed

	m_TextPlayerLives.setFont(m_FontConitionFont);
	m_TextPlayerLives.setPosition(780, 555);
	m_TextPlayerLives.setCharacterSize(32);
	m_TextPlayerLives.setFillColor(sf::Color::Cyan);

	m_TextLivesLabel.setFont(m_FontConitionFont);
	m_TextLivesLabel.setPosition(700, 555);
	m_TextLivesLabel.setCharacterSize(32);
	m_TextLivesLabel.setFillColor(sf::Color::Cyan);
	m_TextLivesLabel.setString("Lives:");

}

void Hud::draw(sf::RenderTarget & target, sf::RenderStates states) const		//draws the objects in the class
{
	target.draw(m_TextPlayerScore, states);			//draw each of the texts
	target.draw(m_TextScoreLabel, states);
	target.draw(m_TextLivesLabel, states);
	target.draw(m_TextPlayerLives, states);
}
