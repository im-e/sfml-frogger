#include "frog.h"

Frog::Frog()
{
	m_iLives = 3;		//initialising all the variables to their starting values
	m_iScore = 0;
	m_fFrogX = 375.f;
	m_fFrogY = 575.f;
	m_fTopYPos = 575.f;

	m_FrogBody.setSize(sf::Vector2f(50.f, 50.f));			//assigning attributes to the frog body shape
	m_FrogBody.setOrigin(m_FrogBody.getSize().x / 2.0f, m_FrogBody.getSize().y / 2.0f);
	m_FrogBody.setPosition(m_fFrogX, m_fFrogY);
	
	if (!m_TexFrog.loadFromFile(".\\assets\\textures\\frogup.png")) //loading in textures and sounds
	{
		cout << "frogup error" << endl;
	}
	if (!m_BufferFrogJump.loadFromFile(".\\assets\\audio\\move.flac")) //if the file fails to load
	{
		cout << " frog jump error" << endl;							//output error
	}
	if (!m_BufferEndZone.loadFromFile(".\\assets\\audio\\endzone.flac"))
	{
		cout << " endzone error" << endl;
	}
	m_FrogBody.setTexture(&m_TexFrog);			//set the texture
	m_SoundFrogJump.setBuffer(m_BufferFrogJump);	//and the buffers to the sounds
	m_SoundEndZone.setBuffer(m_BufferEndZone);
}

sf::FloatRect Frog::FrogHitBox()				//returns the frog body's bounding box
{
	return m_FrogBody.getGlobalBounds();
}

void Frog::Up()									//move the frog up, and increase the score
{
	m_fFrogY = (m_fFrogY - 50.f);				//update the frogs y position
	if (m_fFrogY > -25.f)						//if the frog isn't off the top of the screen
	{
		m_SoundFrogJump.play();					//play the jump sound effect
		m_FrogBody.move(0.f, -50.f);			//move the frog up
		m_FrogBody.setRotation(0.f);			//rotate the frog to upright
		
		if (m_fTopYPos > m_fFrogY)				//if the players highest position in that life is bested
		{
			m_fTopYPos = m_fFrogY;					//update their best position
			m_iScore = m_iScore + 10;				//increase the score
		}

		if (m_fFrogY <= 25.f)					//if the frog reaches the end zone
		{
			m_SoundEndZone.play();				//play the end zone sound
			m_iScore = m_iScore + 100;			//increase the score 
			m_fFrogX = 375.f;					//reset x and y positions
			m_fFrogY = 575.f;
			m_fTopYPos = 575.f;					//reset the players top position
			m_FrogBody.setPosition(m_fFrogX, m_fFrogY);		//move the frog to the starting position
			
		}


	}
	else									//if the frog was trying to move off the edge of the screen
	{
		m_fFrogY = (m_fFrogY + 50.f);		//return the y position to normal		
	}
}

void Frog::Down() //moves the frog down, works the same way for up without scoring
{
	m_fFrogY = (m_fFrogY + 50.f);
	if (m_fFrogY < 625.f)
	{
		m_SoundFrogJump.play();
		m_FrogBody.move(0.f, 50.f);
		m_FrogBody.setRotation(180.f);
	}
	else
	{
		m_fFrogY = (m_fFrogY - 50.f);
	}
}

void Frog::Left() //moves frog left
{
	m_fFrogX = (m_fFrogX - 50.f);
	if (m_fFrogX > -25.f)
	{
		m_SoundFrogJump.play();
		m_FrogBody.move(-50.f, 0.f);
		m_FrogBody.setRotation(270.f);
	}
	else
	{
		m_fFrogX = (m_fFrogX + 50.f);
	}
}

void Frog::Right() //moves frog right
{
	m_fFrogX = (m_fFrogX + 50.f);
	if (m_fFrogX < 825.f)
	{
		m_SoundFrogJump.play();
		m_FrogBody.move(50.f, 0.f);
		m_FrogBody.setRotation(90.f);
	}
	else
	{
		m_fFrogX = (m_fFrogX - 50.f);
	}
}

void Frog::Reset()	//resets the frog when a player has died
{
	m_iLives = (m_iLives - 1);			//takes off a life
	m_fFrogX = 375.f;					//resets the x and y positions
	m_fFrogY = 575.f;
	m_fTopYPos = 575.f;					//resets the players top position

	m_FrogBody.setPosition(m_fFrogX, m_fFrogY);		//places the frog in the starting position
}

void Frog::draw(sf::RenderTarget & target, sf::RenderStates states) const		//allows my objects to be drawn
{
	target.draw(m_FrogBody, states);		//draw frog body
}
