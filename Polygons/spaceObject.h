/* ===================================================================================================================
@Author:		Tyson Koopman-Baker
@Date:			5/16/2025
@File:			spaceObject.h
@Version:		2.0
@IDE:			Microsoft Visual Studios 2022 - Community
@Description:	This progrram is the spaceObject header file used to create space objects for the Octogons video game,
				and gives it values, like it's radius, location, velocity, and angle. It also calls functions that 
				modify these values and keeps the object within bounds of things like, the "game screen" for the 
				location and, 0 - 359 degrees (360 degrees == 0) for the angle. This program also handles any type
				of drawing feature to the game screen for each object
=================================================================================================================== */

#ifndef SPACEOBJECT_H
#define SPACEOBJECT_H

// Structure for the location (x and y) on the game screen
struct Point {
	double x;
	double y;
};

// Enumerator for the tyes of space objects
enum SpaceObjType { SHIP, SHIP_THRUST, ASTEROID, PHOTON_TORPEDO, SHIP_EXPLODING, SHIP_GONE };

// SpaceObject class
class SpaceObject
{
public:
	/* Constructors */
	
	/*
	*	Initializes the default spaceObject constructor
	*/
	SpaceObject();

	/*
	*	Initializes specific spaceObject data type constructors
	* 
	*	@param	SpaceObjType Type - The type of space object that this object is
	*	@param	double radius - The radius of the space object
	*	@param	Point location - The x and y location of the space object
	*	@param	Point velocity - The initial velocity of the space object
	*	@param	double angle - The initial angle of the space object
	*	@param int timesDrawn - The initial times the object has been drawn
	*/
	SpaceObject(SpaceObjType type, double radius, Point location, Point velocity, double angle, int timesDrawn);

	/* Mutator functions */

	/*
	*	Sets the radius of the space object
	* 
	*	@param	double radius - The radius that the space object will be set to
	*	@return	bool false - If the radius is < 0 or >= the screen height
	*	@return	bool true - If the space object radius successfully gets set to the radius in the function parameter
	*/
	bool setRadius(double radius);

	/*
	*	Sets the a new location of the space object using x and y coordinates
	* 
	*	@param	double x - The x coordinate to set the space object location to
	*	@param	double y - The y coordinate to set the space object location to
	*	@return	bool false - If the current location of the space object matches the function parameters
	*	@return	bool true - If the location of the space object is successfully set to a new location
	*/
	bool setLocation(double x, double y);

	/*
	*	Sets a new velocity for the space object given x velocity and y velocity
	* 
	*	@param	double velocityX - The new x velocity being set
	*	@param	double velocityY - The new y velocity being set
	*	@return	bool false - If the current space object velocity matches the old velocity
	*	@return bool true - If the velocity of the space object is successfully set to a new velocity
	*/
	bool setVelocity(double velocityX, double velocityY);

	/*
	*	Sets a new angle for the space object given by an angle in degrees
	* 
	*	@param	double angDeg - The angle in degrees 0 - 359 (360 = 0)
	*	@return	bool false - If the current space object angle matches the function parameters
	*	@return bool true - If the angle of the space object is successfully set to a new angle
	*/
	bool setAngle(double angDeg);

	/*
	*	Sets a new times drawn for the space object
	* 
	*	@param int newTimesDrawn - The new times drawn to be set to
	*	@return bool false - If the current times drawn matches the parameter
	*	@return bool true - If the times drawn was successfully changed
	*/
	bool setTimesDrawn(int newTimesDrawn);

	/*
	*	Changes the angle of the space object by a deltaChange in degree
	* 
	*	@param	double deltaDeg - The amount of change the current space objects angle will get
	*/
	void changeAngle(double deltaDeg);

	/*
	*	Changes the current space object type to a new space object type
	* 
	*	@param	SpaceObjTyoe newObjType - The type of space object being changed to
	*/
	void changeObjType(SpaceObjType newObjType);

	/*
	*	Increments the timesDrawn variable for the object by + 1
	*/
	void incrementTimesDrawn();

	/* Accessor functions */

	/*
	*	Gets the current space object radius and returns that value
	* 
	*	@return	double radius - The current radius of the space object
	*/
	double getRadius() const;

	/*
	*	Gets the current space object location and returns that value
	* 
	*	@return	Point location - The current location of the space object
	*/
	Point getLocation() const;

	/*
	*	Gets the current space object velocity and returns that value
	* 
	*	@return	Point velocity - The current velocity of the space object
	*/
	Point getVelocity() const;

	/*
	*	Gets the current space object velocity and returns that value
	* 
	*	@return	double angleDeg - The current angle of the space object
	*/
	double getAngle() const;

	/*
	*	Gets the current space object type and returns that value
	* 
	*	@return	SpaceObjType type - The current type of the space object
	*/
	SpaceObjType getType() const;

	/*
	*	Gets the current number of times the object has been drawn
	* 
	*	@return int timesDrawn - The number of times the object has been drawn
	*/
	int getTimesDrawn() const;

	/* Other public functions */

	/*
	*	Updates the current position using current location and velocity of the space object
	*/
	void updatePosition();
	
	/*
	*	Applies thrust to a space object using the current angle and velocity of the object
	*/
	void applyThrust(double engineThrust);

	/*
	*	Explodes the space object and changes its values
	*/
	void explode();

	/*
	*	Draws the spaceObject to the given window
	*
	*	@param	sf::RenderWindow& win - The window on which the space object is being drawn on
	*/
	void draw(sf::RenderWindow& win);

private:
	SpaceObjType type;	// The type of space object
	Point location;	// The current location of the space object (x,y)
	Point velocity;	// The current velocity of the space object (in pixels/frame)
	double angleDeg;	// The angle the object is facing (in degrees)
	double radius;	// The gross radius of object (for collision detection)
	int timesDrawn;	// The amount of times the object has been drawn on the game window

	/* Other private functions */
	/*
	*	Draws the spaceObject on the given window as an asteroid
	*
	*	@param	sf::RenderWindow& win - The window on which the asteroid is being drawn on
	*/
	void drawAsteroid(sf::RenderWindow& win);

	/*
	*	Draws the spaceObject on the given window as a ship
	* 
	*	@param	sf::RenderWindow& win - The window on which the ship is being drawn on
	*/
	void drawShip(sf::RenderWindow& win);

	/*
	*	Draws the spaceObject on the given window as a ship with thrusters
	* 
	*	@param sf::RenderWindow& win - The window on which the ship is being drawn on
	*/
	void drawShipThrust(sf::RenderWindow& win);

	/*
	*	Draws the spaceObject on the given window as an exploding ship
	* 
	*	@param	sf::RenderWindow& win - The window on which the exploding ship is being drawn on
	*/
	void drawExplodingShip(sf::RenderWindow& win);
};

#endif

