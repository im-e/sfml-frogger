#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include "frog.h"
#include "vehicle.h"
#include "hud.h"

using namespace std;

/*sprite sources
https://scratch.mit.edu/projects/97493924/
http://excamera.com/sphinx/_images/sprites.png
http://i.imgur.com/33Hnhw9.png

audio sources
https://github.com/AliyuAbdullahi/frogger-game
http://www.classicgaming.cc/classics/frogger/sounds
https://www.youtube.com/watch?v=fc_pUo5RZXc

*/

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Frogger");	//Creates a window to render objects in

	Frog frog;					//Allows my classes to be used
	Vehicle vehicle;
	Hud hud;
		
	sf::Clock timer;				//Timer used for checking updates within the game
	float FFrame = 1.f / 60.f;		//Determines how many frames there will be in a minute
	float FElapsedTime;				//Variable used to hold how much time has passed
	sf::Texture TexSafeArea;		//Textures for background areas
	sf::Texture TexEndArea;
	
	sf::Music GameMusic;				//Main music for the game
	sf::SoundBuffer BufferFrogWater;	//Buffers for death sound effects
	sf::SoundBuffer BufferFrogHit;
	sf::Sound SoundFrogWater;
	sf::Sound SoundFrogHit;
	

	if (!BufferFrogWater.loadFromFile(".\\assets\\audio\\frogwater.flac"))	//loading in music files and textures
	{
		cout << " frog water error" << endl;
	}
	if (!BufferFrogHit.loadFromFile(".\\assets\\audio\\froghit.flac"))		//if file is unable to load
	{
		cout << " frog hit error" << endl;									//output error to console
	}
	if (!GameMusic.openFromFile(".\\assets\\audio\\music.flac"))
	{
		cout << " music error" << endl;
	}
	if (!TexEndArea.loadFromFile(".\\assets\\textures\\endarea.png"))
	{
		cout << "endarea error" << endl;
	}
	if (!TexSafeArea.loadFromFile(".\\assets\\textures\\safearea.png"))
	{
		cout << "safearea error" << endl;
	}

	GameMusic.setLoop(true);												//sets the main music to loop
	SoundFrogHit.setBuffer(BufferFrogHit);									//setting the buffers to the sounds
	SoundFrogWater.setBuffer(BufferFrogWater);
	GameMusic.setVolume(50.f);												//sets the main music to a lower volume
	GameMusic.play();														//plays the menu music


	sf::RectangleShape bcgStartingArea;					//creating the shapes for all the background areas of the game
	bcgStartingArea.setSize(sf::Vector2f(800.f, 50.f));	//sets the size of the shape
	bcgStartingArea.setOrigin(bcgStartingArea.getSize().x / 2.0f, bcgStartingArea.getSize().y / 2.0f); //sets the origin on the shape to the centre
	bcgStartingArea.setPosition(400.f, 575.f); //sets the position of the shape
	bcgStartingArea.setTexture(&TexSafeArea);	//sets the texture of the shape

	sf::RectangleShape bcgSafeArea;
	bcgSafeArea.setSize(sf::Vector2f(800.f, 50.f));
	bcgSafeArea.setOrigin(bcgSafeArea.getSize().x / 2.0f, bcgSafeArea.getSize().y / 2.0f);
	bcgSafeArea.setPosition(400.f, 275.f);
	bcgSafeArea.setTexture(&TexSafeArea);

	sf::RectangleShape bcgEndingArea;
	bcgEndingArea.setSize(sf::Vector2f(800.f, 50.f));
	bcgEndingArea.setOrigin(bcgEndingArea.getSize().x / 2.0f, bcgEndingArea.getSize().y / 2.0f);
	bcgEndingArea.setPosition(400.f, 25.f);
	bcgEndingArea.setTexture(&TexEndArea);

	sf::RectangleShape bcgWater;
	bcgWater.setSize(sf::Vector2f(800.f, 200.f));
	bcgWater.setOrigin(bcgWater.getSize().x / 2.0f, bcgWater.getSize().y / 2.0f);
	bcgWater.setPosition(400.f, 150.f);
	bcgWater.setFillColor(sf::Color(0, 0, 71));
	sf::FloatRect waterBoundingBox;					//bounding box which is used to detect if the frog falls in the water
	waterBoundingBox = bcgWater.getGlobalBounds(); //gets the bounding box from the water shape



	
	while (window.isOpen())							//Will run until the user closes the window
	{
		sf::Event event;
		while (window.pollEvent(event))				//checks for user events
		{
			if (event.type == sf::Event::Closed)	//if the user presses the close window button
			{
				window.close();						//close the window
			}

			if (event.type == sf::Event::KeyPressed) //if a keyboard key is pressed 
			{
				
				if (event.key.code == sf::Keyboard::Up) //if the key that was pressed was up
				{
					frog.Up();							//move frog up
				}
				if (event.key.code == sf::Keyboard::Left) //if key was left
				{
					frog.Left();						//move frog left
				}
				if (event.key.code == sf::Keyboard::Right) 
				{
					frog.Right();
				}
				if (event.key.code == sf::Keyboard::Down)
				{
					frog.Down();
				}
				if (event.key.code == sf::Keyboard::Escape) //if user presses escape
				{
					window.close();							//close the game window
				}

			}		
			
		}
		//event loop ends

		FElapsedTime = timer.getElapsedTime().asSeconds(); //finds out how much time has passed
		if (FElapsedTime > FFrame)							//if more time has passed than the frame time 
		{													//update cycle
			vehicle.VehicleMove();							//function to move the vehicles in the game
			
			hud.m_TextPlayerScore.setString(std::to_string(frog.m_iScore));	//updates the score
			hud.m_TextPlayerLives.setString(std::to_string(frog.m_iLives));	//updates the lives

			for (int i = 0; i < vehicle.m_kiCarAmount; i++)					//checks each car if the frog is colliding with one of them
			{
				if (frog.FrogHitBox().intersects(vehicle.m_aCarBoundingBox[i])) //if a car is colliding with the frog
				{
					frog.Reset();											//reset the frogs position and lose a life
					SoundFrogHit.play();									//play frog hit sound
				}
			}

			for (int i = 0; i < vehicle.m_kiTruckAmount; i++)				//checks each truck for frog collision
			{
				if (frog.FrogHitBox().intersects(vehicle.m_aTruckBoundingBox[i]))	//if a truck is colliding with the frog
				{
					frog.Reset();										//resets 
					SoundFrogHit.play();								//play sound
				}
			}
			
			if (frog.FrogHitBox().intersects(waterBoundingBox))			//if frog is colliding with the water
			{
				bool bFrogOnLog = false;								//bool used to signal if the frog is sitting on a log

				for (int i = 0; i < vehicle.m_kiLogAmount; i++)			//used to check if the frog is colliding with any log
				{
					if (frog.FrogHitBox().intersects(vehicle.m_aLogBoundingBox[i]))	//if the frog is colliding with a log
					{
						bFrogOnLog = true;	

						if (i == 0 || i == 2 || i == 4 || i == 6)		//if it is any of the logs moving to the right
						{
							if (i == 0 || i == 2)						
							{
								frog.m_fFrogX = (frog.m_fFrogX + vehicle.m_aiLogSpeed[i]);	//increase the x position of the frog by the same amount the frog will move
								frog.m_FrogBody.move(vehicle.m_aiLogSpeed[i], 0.f);			//moves the frog to the right by the speed of the log
							}
							if (i == 4)
							{
								frog.m_fFrogX = (frog.m_fFrogX + vehicle.m_aiLogSpeed[0]);
								frog.m_FrogBody.move(vehicle.m_aiLogSpeed[0], 0.f);		
							}
							if (i == 6)
							{
								frog.m_fFrogX = (frog.m_fFrogX + vehicle.m_aiLogSpeed[2]);
								frog.m_FrogBody.move(vehicle.m_aiLogSpeed[2], 0.f);
							}
							
						}
						
						if (i == 1 || i == 3 || i == 5 || i == 7)		//if its any of the logs moving to the left
						{
								
							if (i == 1 || i == 3)
							{
								frog.m_fFrogX = (frog.m_fFrogX - vehicle.m_aiLogSpeed[i]);	//decrease the x position of the frog by the same amount the frog will move
								frog.m_FrogBody.move(-vehicle.m_aiLogSpeed[i], 0.f);			//moves the frog to the left by the speed of the log
							}
							if (i == 5)
							{
								frog.m_fFrogX = (frog.m_fFrogX - vehicle.m_aiLogSpeed[1]);
								frog.m_FrogBody.move(-vehicle.m_aiLogSpeed[1], 0.f);
							}
							if (i == 7)
							{
								frog.m_fFrogX = (frog.m_fFrogX - vehicle.m_aiLogSpeed[3]);
								frog.m_FrogBody.move(-vehicle.m_aiLogSpeed[3], 0.f);
							}
						}
					}						

				}

				if (bFrogOnLog == false) //if the frog wasn't colliding with a log
				{
					frog.Reset();			//reset
					SoundFrogWater.play();		//play frog falling in water sound
				}
				
				bFrogOnLog = false;			//resets the variable
			}

			if (frog.m_fFrogX <= -25.f || frog.m_fFrogX >= 825.f)  //if frog goes off the edge of the screen from sitting on a log
			{
				frog.Reset();										//reset 
				SoundFrogWater.play();								//play frog falling in water sound
			}

			if (frog.m_iLives == 0)								//if the player runs out of lives
			{
				window.close();									//close the window
			}
			
			timer.restart();					//resets the timer
		}
			

		//drawings
		window.clear();
		window.draw(bcgEndingArea);
		window.draw(bcgSafeArea);
		window.draw(bcgStartingArea);
		window.draw(bcgWater);
		window.draw(vehicle);
		window.draw(frog);
		window.draw(hud);
		window.display();

	} // main loop ends
	
}


