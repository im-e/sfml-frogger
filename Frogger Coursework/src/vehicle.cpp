#include "vehicle.h"

Vehicle::Vehicle()
{
	srand((int)time(0)); //seeds the random function to prevent the same numbers occouring

	if (!m_TexCar.loadFromFile(".\\assets\\textures\\car.png"))	//loading in textures
	{
		cout << " error" << endl;
	}
	if (!m_TexTruck.loadFromFile(".\\assets\\textures\\truck.png"))//if file is unable to load
	{
		cout << " error" << endl;								//output error to console
	}
	if (!m_TexLog.loadFromFile(".\\assets\\textures\\log.png"))
	{
		cout << " error" << endl;
	}

	for (int i = 0; i < m_kiCarAmount; i++)			//assigns common attributes to all cars
	{
		m_aCar[i].setSize(sf::Vector2f(100.f, 50.f));	//sets the size of the car
		m_aCar[i].setOrigin(m_aCar[i].getSize().x / 2.0f, m_aCar[i].getSize().y / 2.0f);	//sets origin of the car
		m_aCar[i].setTexture(&m_TexCar);	//sets the texture of the car
	}

	for (int i = 0; i < m_kiTruckAmount; i++) //assigns common attributes to all trucks
	{
		m_aTruck[i].setSize(sf::Vector2f(175.f, 50.f));
		m_aTruck[i].setOrigin(m_aTruck[i].getSize().x / 2.0f, m_aTruck[i].getSize().y / 2.0f);
		m_aTruck[i].setTexture(&m_TexTruck);
	}

	for (int i = 0; i < m_kiLogAmount; i++) //assigns common attributes to all logs
	{
		m_aLog[i].setSize(sf::Vector2f(125.f, 50.f));
		m_aLog[i].setOrigin(m_aLog[i].getSize().x / 2.0f, m_aLog[i].getSize().y / 2.0f);
		m_aLog[i].setTexture(&m_TexLog);
	}
	
	for (int i = 0; i < m_kiCarSpeedAmount; i++) //gets a set of random speed values for the amount of car lanes
	{
		int iMaxSpeed = 5;	//variable for the maximum speed that can be added to the minimum speed
		int iMinSpeed = 3;	//sets the minimum speed for the car
		m_aiCarSpeed[i] = iMinSpeed + (rand() % iMaxSpeed); //takes a random value from the max speed value and adds it to the minimum speed
	}

	for (int i = 0; i < m_kiTruckSpeedAmount; i++) //gets a set of random speed values for the amount of truck lanes
	{
		int iMaxSpeed = 3;
		int iMinSpeed = 3;
		m_aiTruckSpeed[i] = iMinSpeed + (rand() % iMaxSpeed);
	}

	for (int i = 0; i < m_kiLogSpeedAmount; i++) //gets a set of random speed values for the amount of log lanes
	{
		int iMaxSpeed = 5;
		int iMinSpeed = 2;
		m_aiLogSpeed[i] = iMinSpeed + (rand() % iMaxSpeed);
	}

	m_aCar[0].setPosition(150.f, 325.f); // assigns the positions for one of the vehicles in a lane
	m_aCar[1].setPosition(25.f, 425.f);
	m_aCar[2].setPosition(300.f, 525.f);
	m_aTruck[0].setPosition(600.f, 375.f);
	m_aTruck[1].setPosition(800.f, 475.f);
	m_aLog[0].setPosition(100.f, 75.f);
	m_aLog[1].setPosition(650.f, 125.f);
	m_aLog[2].setPosition(260.f, 175.f);
	m_aLog[3].setPosition(740.f, 225.f);

	float fPosY = 325.f;			//variable used to position the second vehicle in a lane
	for (int i = 0; i < m_kiCarSpeedAmount; i++) //sets the second car in a lane with a random distance inbetween
	{
		int iMaxDistance = 400;	//variable for the maximum distance that can be added to the minimum distance
		int iMinDistance = 100; //sets the minimum distance for the car to be spaced
		m_aCar[i + 3].setPosition(-iMinDistance - (rand() % iMaxDistance), fPosY); //sets the x position to be a random value from the max distance value and adds it to the minimum distance 
		fPosY = fPosY + 100.f; //increase PosY to spawn the car in the next lane 
	}

	fPosY = 375.f;				//variable used to position the next set of second vehicles	in a lane	
	for (int i = 0; i < m_kiTruckSpeedAmount; i++) //sets the second trucks in a lane with a random distance inbetween
	{
		int iMaxDistance = 300.f;
		int iMinDistance = 100.f;
		m_aTruck[i + 2].setPosition(iMinDistance + (rand() % iMaxDistance), fPosY);
		fPosY = fPosY + 100.f;
	}
	
	fPosY = 75.f;
	for (int i = 0; i < m_kiLogSpeedAmount; i++)  //sets the second logs in a lane with a random distance inbetwee
	{
		if (i % 2 == 0)		//if i is even 
		{
			int iMaxDistance = 300.f;
			int iMinDistance = 100.f;
			m_aLog[i + 4].setPosition(-iMinDistance - (rand() % iMaxDistance), fPosY);	//spawn log to the left side of the screen
		}
		else
		{
			int iMaxDistance = 300.f;
			int iMinDistance = 100.f;
			m_aLog[i + 4].setPosition(iMinDistance + (rand() % iMaxDistance), fPosY); //spawn log to the right side of the screen
		}
		fPosY = fPosY + 50.f; //increase PosY to spawn the log in the next lane 
	}	
}


void Vehicle::VehicleMove()		//moves each vehicle
{
	for (int i = 0; i < m_kiCarSpeedAmount; i++)
	{		
		m_aCar[i].move(m_aiCarSpeed[i], 0.f);		//move both vehicles in the same lane by the same speed so that they do not overlap
		m_aCar[i+3].move(m_aiCarSpeed[i], 0.f);
		if (m_aCar[i].getPosition().x >= 900.f)	//if the car goes completely off the screen
		{
			m_aCar[i].setPosition(-100.f, m_aCar[i].getPosition().y);	//set the position to the other side of the screen so it will wrap around
		}
		if (m_aCar[i+3].getPosition().x >= 900.f)	//does the same for the other car in the lane
		{
			m_aCar[i+3].setPosition(-100.f, m_aCar[i+3].getPosition().y);
		}
		m_aCarBoundingBox[i] = m_aCar[i].getGlobalBounds();		//updates the bounding boxes of each of the cars when they move
		m_aCarBoundingBox[i+3] = m_aCar[i+3].getGlobalBounds();
	}

	for (int i = 0; i < m_kiTruckSpeedAmount; i++) //moves the trucks in the same way as cars
	{
		m_aTruck[i].move(-m_aiTruckSpeed[i], 0.f);
		m_aTruck[i+2].move(-m_aiTruckSpeed[i], 0.f);
		if (m_aTruck[i].getPosition().x <= -175.f)
		{
			m_aTruck[i].setPosition(975.f, m_aTruck[i].getPosition().y);
		}
		if (m_aTruck[i+2].getPosition().x <= -175.f)
		{
			m_aTruck[i+2].setPosition(975.f, m_aTruck[i+2].getPosition().y);
		}
		m_aTruckBoundingBox[i] = m_aTruck[i].getGlobalBounds();
		m_aTruckBoundingBox[i+2] = m_aTruck[i+2].getGlobalBounds();
	}

	bool bMoveRight = true;						//determines wether the log will move right or left
	for (int i = 0; i < m_kiLogSpeedAmount; i++)
	{
		if (bMoveRight == true)					//moves the logs right
		{
			m_aLog[i].move(m_aiLogSpeed[i], 0.f);
			m_aLog[i + 4].move(m_aiLogSpeed[i], 0.f);
			bMoveRight = false;					//variable reset
			if (m_aLog[i].getPosition().x >= 925.f)
			{
				m_aLog[i].setPosition(-125.f, m_aLog[i].getPosition().y);
			}
			if (m_aLog[i + 4].getPosition().x >= 925.f)
			{
				m_aLog[i + 4].setPosition(-125.f, m_aLog[i].getPosition().y);
			}
			m_aLogBoundingBox[i] = m_aLog[i].getGlobalBounds();
			m_aLogBoundingBox[i + 4] = m_aLog[i + 4].getGlobalBounds();
		}
		else if (bMoveRight == false)			//moves the logs left
		{
			m_aLog[i].move(-m_aiLogSpeed[i], 0.f);
			m_aLog[i + 4].move(-m_aiLogSpeed[i], 0.f);
			bMoveRight = true;					//variable reset
			if (m_aLog[i].getPosition().x <= -125.f)
			{
				m_aLog[i].setPosition(925.f, m_aLog[i].getPosition().y);
			}
			if (m_aLog[i + 4].getPosition().x <= -125.f)
			{
				m_aLog[i + 4].setPosition(925.f, m_aLog[i].getPosition().y);
			}
			m_aLogBoundingBox[i] = m_aLog[i].getGlobalBounds();
			m_aLogBoundingBox[i + 4] = m_aLog[i + 4].getGlobalBounds();
		}
	}
}


void Vehicle::draw(sf::RenderTarget & target, sf::RenderStates states) const		//allows for my objects to be drawn
{
	for (int i = 0; i < m_kiCarAmount; i++)	//for every car
	{
		target.draw(m_aCar[i], states);		//draw every car
	}

	for (int i = 0; i < m_kiTruckAmount; i++)	//for every truck
	{
		target.draw(m_aTruck[i], states);		//draw every truck
	}
	
	for (int i = 0; i < m_kiLogAmount; i++)		//for every log
	{
		target.draw(m_aLog[i], states);			//draw every log
	}

}


