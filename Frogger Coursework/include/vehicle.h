#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>

using namespace std;

class Vehicle : public sf::Drawable
{
private:
	
public:
	Vehicle(); //constructor

	//constant ints to prevent magic numbers
	const static int m_kiCarAmount = 6;		//sets the amount of cars in total
	const static int m_kiTruckAmount = 4;	//sets the amount of truckts in total
	const static int m_kiLogAmount = 8;		//sets the amount of logs in total
	const static int m_kiCarSpeedAmount = 3;	//amount of speeds needed for cars
	const static int m_kiTruckSpeedAmount = 2;	//amount of speeds needed for trucks
	const static int m_kiLogSpeedAmount = 4;	//amount of speeds needed for logs

	sf::RectangleShape m_aCar[m_kiCarAmount];	//array for car shapes
	sf::FloatRect m_aCarBoundingBox[m_kiCarAmount];	//array for car bounding boxes
	sf::Texture m_TexCar;							//car texture
	int m_aiCarSpeed[m_kiCarSpeedAmount];		//array for car speeds

	sf::RectangleShape m_aTruck[m_kiTruckAmount]; //same as above but for the trucks
	sf::FloatRect m_aTruckBoundingBox[m_kiTruckAmount];
	sf::Texture m_TexTruck;
	int m_aiTruckSpeed[m_kiTruckSpeedAmount];
	
	sf::RectangleShape m_aLog[m_kiLogAmount]; //same as above but for the logs
	sf::FloatRect m_aLogBoundingBox[m_kiLogAmount];
	sf::Texture m_TexLog;
	int m_aiLogSpeed[m_kiLogSpeedAmount];


	void VehicleMove();				//function which moves all the vehicles
	
	

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;		//used to draw objects to the window
	
};
