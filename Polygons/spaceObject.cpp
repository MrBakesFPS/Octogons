/* ===================================================================================================================
@Author:		Tyson Koopman-Baker
@Date:			5/16/2025
@File:			spaceObject.cpp
@Version:		2.0
@IDE:			Microsoft Visual Studios 2022 - Community
@Description:	This program covers all of the implementations for the SpaceObject Class from the "spaceObject.h"
				header file
=================================================================================================================== */

// Libraries and other files
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "spaceObject.h"
#include "constants.h"

// Default constructor
SpaceObject::SpaceObject()
{
	// Setting default values for a SpaceObject's variables
	type = ASTEROID;
	location.x = SCREEN_WIDTH / 2.0;
	location.y = SCREEN_HEIGHT / 2.0;
	velocity.x = 0;
	velocity.y = 0;
	angleDeg = 0;
	radius = 20;
	timesDrawn = 0;
}

// Alternate constructor
SpaceObject::SpaceObject(SpaceObjType type, double radius, Point location, Point velocity, double angle, int timesDrawn)
{
	// Setting specific values for a SpaceObject's variables
	changeObjType(type);
	setRadius(radius);
	setLocation(location.x, location.y);
	setVelocity(velocity.x, velocity.y);
	setAngle(angle);
	setTimesDrawn(timesDrawn);
}

// setRadius function
bool SpaceObject::setRadius(double radius)
{
	// If the given radius is bigger that half the screen size, set it to a default of 20, otherwise sets it to the given radius
	if (radius < 0 || radius >= SCREEN_HEIGHT / 2.0) { // For some reason, the program wanted me to cast these
		this->radius = 20;

		return false;
	}
	else {
		this->radius = radius;

		return true;
	}
}

// setLocation function
bool SpaceObject::setLocation(double x, double y)
{
	// Checks to see if the new location is within bounds of the screen, and if not, changes the location to fit
	if (x == location.x && y == location.y)
		return false;
	else {
		while (x >= SCREEN_WIDTH)
			x = x - SCREEN_WIDTH;
		while (x < 0)
			x = x + SCREEN_WIDTH;

		while (y >= SCREEN_HEIGHT)
			y = y - SCREEN_HEIGHT;
		while (y < 0)
			y = y + SCREEN_HEIGHT;

		this->location.x = x;
		this->location.y = y;

		return true;
	}
}

// setVelocity function
bool SpaceObject::setVelocity(double velocityX, double velocityY)
{
	if (velocity.x == velocityX && velocity.y == velocityY)
		return false;
	else {
			this->velocity.x = velocityX;
			this->velocity.y = velocityY;

		return true;
	}
}

// setAngle function
bool SpaceObject::setAngle(double angDeg)
{
	// Checks to see if the new angle degree fits within the 0-359 range, and if not, changes the degree to fit
	if (angDeg == angleDeg)
		return false;
	else {
		while (angDeg >= 360)
			angDeg = angDeg - 360;
		while (angDeg < 0)
			angDeg = angDeg + 360;

		this->angleDeg = angDeg;

		return true;
	}
}

// setTimesDrawn function
bool SpaceObject::setTimesDrawn(int newTimesDrawn)
{
	if (newTimesDrawn == timesDrawn)
		return false;
	else {
		this->timesDrawn = newTimesDrawn;
		
		return true;
	}
}

// changeAngle function
void SpaceObject::changeAngle(double deltaDeg)
{
	if (type == SHIP || type == SHIP_THRUST || type == ASTEROID)
		setAngle(angleDeg + deltaDeg);
	
}

// changeObjType function
void SpaceObject::changeObjType(SpaceObjType newObjType)
{
	this->type = newObjType;
}

// incrementTimesDrawn function
void SpaceObject::incrementTimesDrawn()
{
	this->timesDrawn += 1;
}

// getRadius function
double SpaceObject::getRadius() const
{
	return radius;
}

// getLocation function
Point SpaceObject::getLocation() const
{
	return location;
}

// getVelocity function
Point SpaceObject::getVelocity() const
{
	return velocity;
}

// getAngle function
double SpaceObject::getAngle() const
{
	return angleDeg;
}

// getType function
SpaceObjType SpaceObject::getType() const
{
	return type;
}

// getTimesDrawn function
int SpaceObject::getTimesDrawn() const
{
	return timesDrawn;
}

// updatePosition function
void SpaceObject::updatePosition()
{
	setLocation(location.x + velocity.x, location.y + velocity.y);
}

// applyThrust function
void SpaceObject::applyThrust(double engineThrust)
{
	if (type == SHIP_THRUST || type == PHOTON_TORPEDO) {
		double forcex = cos((angleDeg - 90) * PI / 180) * engineThrust;
		double forcey = sin((angleDeg - 90) * PI / 180) * engineThrust;
		velocity.x = velocity.x + forcex;
		velocity.y = velocity.y + forcey;
	}
}
// explode function
void SpaceObject::explode()
{
	changeObjType(SHIP_EXPLODING);
	setRadius(0.1);
	setVelocity(0, 0);
	setAngle(0);
}

// draw function
void SpaceObject::draw(sf::RenderWindow& win) 
{
	if (type == SHIP)
		drawShip(win);
	else if (type == SHIP_THRUST)
		drawShipThrust(win);
	else if (type == ASTEROID)
		drawAsteroid(win);
	else if (type == SHIP_EXPLODING)
		drawExplodingShip(win);
	else if (type == PHOTON_TORPEDO)
		drawAsteroid(win);
}

// drawAsteroid function
void SpaceObject::drawAsteroid(sf::RenderWindow& win) 
{
	// Creating the asteroid
	int points = 8;
	sf::CircleShape shape(radius, points);

	sf::Vector2f midpoint(radius, radius);
	shape.setOrigin(midpoint);

	shape.setFillColor(sf::Color(0, 0, 0));
	shape.setOutlineThickness(1);
	shape.setOutlineColor(sf::Color(255, 255, 255));

	// Drawing the asteroid
	shape.setPosition(location.x, location.y);
	shape.setRotation(angleDeg);

	win.draw(shape);

	if (location.x + radius > SCREEN_WIDTH) {
		shape.setPosition(location.x - radius * 2 - SCREEN_WIDTH, location.y);
	}
	if (location.x - radius < 0) {
		shape.setPosition(location.x + radius * 2 + SCREEN_WIDTH, location.y);
	}
	if (location.y + radius > SCREEN_HEIGHT) {
		shape.setPosition(location.x, location.y - radius * 2 - SCREEN_HEIGHT);
	}
	if (location.y - radius < 0) {
		shape.setPosition(location.x, location.y + radius * 2 + SCREEN_HEIGHT);
	}

	win.draw(shape);
}

// drawShip function
void SpaceObject::drawShip(sf::RenderWindow& win) 
{
	// Creating the ship
	sf::ConvexShape shipShape;
	shipShape.setPointCount(3);
	shipShape.setPoint(0, sf::Vector2f(10, 0));
	shipShape.setPoint(1, sf::Vector2f(0, 25));
	shipShape.setPoint(2, sf::Vector2f(20, 25));

	sf::Vector2f midpoint(10, 15);
	shipShape.setOrigin(midpoint);

	shipShape.setFillColor(sf::Color(0, 0, 0));
	shipShape.setOutlineThickness(1);
	shipShape.setOutlineColor(sf::Color(255, 255, 255));

	// Drawing the ship
	shipShape.setPosition(location.x, location.y);
	shipShape.setRotation(angleDeg);
	win.draw(shipShape);
}

// drawShipThrust function
void SpaceObject::drawShipThrust(sf::RenderWindow& win)
{
	// Creating the ship
	sf::ConvexShape shipShape;
	shipShape.setPointCount(3);
	shipShape.setPoint(0, sf::Vector2f(10, 0));
	shipShape.setPoint(1, sf::Vector2f(0, 25));
	shipShape.setPoint(2, sf::Vector2f(20, 25));

	sf::Vector2f midpoint(10, 15);
	shipShape.setOrigin(midpoint);

	shipShape.setFillColor(sf::Color(0, 0, 0));
	shipShape.setOutlineThickness(1);
	shipShape.setOutlineColor(sf::Color(255, 255, 255));

	// Drawing the ship
	shipShape.setPosition(location.x, location.y);
	shipShape.setRotation(angleDeg);
	win.draw(shipShape);

	// Creating the thruster flames
	sf::ConvexShape flame1;
	sf::ConvexShape flame2;

	flame1.setPointCount(3);
	flame1.setPoint(0, sf::Vector2f(10, 25));
	flame1.setPoint(1, sf::Vector2f(6, 25));
	flame1.setPoint(2, sf::Vector2f(8, 30));

	flame2.setPointCount(3);
	flame2.setPoint(0, sf::Vector2f(10, 25));
	flame2.setPoint(1, sf::Vector2f(14, 25));
	flame2.setPoint(2, sf::Vector2f(12, 30));

	flame1.setOrigin(midpoint);
	flame2.setOrigin(midpoint);

	flame1.setFillColor(sf::Color(0, 0, 0));
	flame2.setFillColor(sf::Color(0, 0, 0));

	flame1.setOutlineThickness(1);
	flame2.setOutlineThickness(1);

	flame1.setOutlineColor(sf::Color(255, 255, 255));
	flame2.setOutlineColor(sf::Color(255, 255, 255));

	// Drawing the thruster flames
	flame1.setPosition(location.x, location.y);
	flame1.setRotation(angleDeg);

	flame2.setPosition(location.x, location.y);
	flame2.setRotation(angleDeg);

	win.draw(flame1);
	win.draw(flame2);
}

// drawExplodingShip function
void SpaceObject::drawExplodingShip(sf::RenderWindow& win)
{
	// Creating the exploding ship
	sf::CircleShape shipShape;
	shipShape.setFillColor(sf::Color(255, 255, 255));
	shipShape.setOutlineColor(sf::Color(255, 255, 255));
	shipShape.setOutlineThickness(1);
	shipShape.setRadius(radius);

	// Drawing the exploding ship
	shipShape.setPosition(location.x, location.y);

	win.draw(shipShape);
}