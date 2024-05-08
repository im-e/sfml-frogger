#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>

using namespace std;

class Frog : public sf::Drawable
{
private:
	
public:
Frog();
	
	sf::RectangleShape m_FrogBody;		//shape for the frog
	sf::Texture m_TexFrog;				//texture for the frog
	sf::SoundBuffer m_BufferFrogJump;		//buffer for the frog jump sound
	sf::SoundBuffer m_BufferEndZone;		//buffer for the frog reaching the end zone sound
	sf::Sound m_SoundFrogJump;			//sound for frog moving
	sf::Sound m_SoundEndZone;				//sound for frog reaching the end zone

	int m_iLives;						//int to hold the player lives
	int m_iScore;						//int to hold player score
	float m_fTopYPos;					//holds the players highest position reached 
	float m_fFrogX;						//holds the frogs x position
	float m_fFrogY;						//holds the frogs y position

	sf::FloatRect FrogHitBox();			//fuction to get the frogs bounding box

	void Up();							//functions to move the frog up	
	void Down();						//down
	void Left();						//left
	void Right();						//right
	void Reset();						//resets the frogs position and takes off a life

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;	//draws the frog to the screen
	
	
	
};