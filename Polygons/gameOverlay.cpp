/* ===================================================================================================================
@Author:		Tyson Koopman-Baker
@Date:			5/16/2025
@File:			overlay.cpp
@Version:		2.0
@IDE:			Microsoft Visual Studios 2022 - Community
@Description:	This program covers all of the implementations for the GameOverlay Class from the "overlay.h"
				header file
=================================================================================================================== */

// Libraries and other include files
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include "gameOverlay.h"
#include "constants.h"

// Defaullt GameOverlay consructor
GameOverlay::GameOverlay()
{
	overlayType = TITLE_OVERLAY;
	lives = 3;
	gameInProgress = false;
	firstLifeLost = false;

	std::cout << "Loading font:" << std::endl;
	if (!gameFont.loadFromFile("JumpersCondensedItalic-d9zq7.ttf"))
		std::cout << "Error";
	else
		std::cout << "Font Loaded Successfully!";

	pauseScreenOpen = false;
}

// changeOverlay function
void GameOverlay::changeOverlay(OverlayState newOverlayType)
{
	this->overlayType = newOverlayType;
}

// drawOverlay function
void GameOverlay::drawOverlay(sf::RenderWindow& win)
{
	if (overlayType == TITLE_OVERLAY) {
		drawTitleOverlay(win);
		if (pauseScreenOpen == true)
			drawPauseOverlay(win);
	}
	else if (overlayType == GAME_OVERLAY) {
		drawGameOverlay(win);
		if (pauseScreenOpen == true)
			drawPauseOverlay(win);
	}
	else if (overlayType == PLAYER_WINS) {
		drawWinOverlay(win);
		if (pauseScreenOpen == true)
			drawPauseOverlay(win);
	}
	else if (overlayType == PLAYER_LOSES) {
		drawLoseOverlay(win);
		if (pauseScreenOpen == true)
			drawPauseOverlay(win);
	}
	else if (overlayType == LIVES_LEFT) {
		drawLivesOverlay(win);
	}
	else if (overlayType == INCOMING_SHIP) {
		drawGameOverlay(win);
		drawIncomingShip(win);
		if (pauseScreenOpen == true)
			drawPauseOverlay(win);
	}

}

// changeLifeTotal function
void GameOverlay::changeLifeTotal(int newLifeTotal)
{
	this->lives = newLifeTotal;
}

// changeFirstLifeLost function
void GameOverlay::changeFirstLifeLost(bool isFirstLifeLost)
{
	this->firstLifeLost = isFirstLifeLost;
}

// changeInProgress function
void GameOverlay::changeInProgress(bool isInProgress)
{
	this->gameInProgress = isInProgress;
}

// changePauseScreenOpen function
void GameOverlay::changePauseScreenOpen(bool isOpen)
{
	this->pauseScreenOpen = isOpen;
}

// getLivesLost function
int GameOverlay::getLivesLeft()
{
	return lives;
}

// getGameInProgress function
bool GameOverlay::getGameInProgress()
{
	return gameInProgress;
}

// isFirstLifeLost function
bool GameOverlay::isFirstLifeLost()
{
	return firstLifeLost;
}

// pauseScreenIsOpen function
bool GameOverlay::pauseScreenIsOpen()
{
	return pauseScreenOpen;
}

// drawTitleOverlay function
void GameOverlay::drawTitleOverlay(sf::RenderWindow& win)
{
	sf::Text titleOverlay;
	sf::Text spaceToPlay;
	sf::Text escapeToPause;
	
	titleOverlay.setString("OCTOGONS");
	titleOverlay.setFont(gameFont);
	titleOverlay.setCharacterSize(75);
	titleOverlay.setPosition(50, 50);

	spaceToPlay.setString("Press \'Space\' to play!");
	spaceToPlay.setFont(gameFont);
	spaceToPlay.setCharacterSize(25);
	spaceToPlay.setPosition(80, 133);

	escapeToPause.setString("Press \'ESC\' to pause\n   /show controls!");
	escapeToPause.setFont(gameFont);
	escapeToPause.setCharacterSize(25);
	escapeToPause.setPosition(80, 160);

	win.draw(titleOverlay);
	win.draw(spaceToPlay);
	win.draw(escapeToPause);
}

// drawGameOverlay function
void GameOverlay::drawGameOverlay(sf::RenderWindow& win)
{
	sf::Text displayLivesLeft;

	displayLivesLeft.setFont(gameFont);
	displayLivesLeft.setCharacterSize(25);
	displayLivesLeft.setPosition(10, 5);

	switch (getLivesLeft()) {
	case 0:
		displayLivesLeft.setString("EXTRA LIVES LEFT: 0");
		break;
	case 1:
		displayLivesLeft.setString("EXTRA LIVES LEFT: 1");
		break;
	case 2:
		displayLivesLeft.setString("EXTRA LIVES LEFT: 2");
		break;
	case 3:
		displayLivesLeft.setString("EXTRA LIVES LEFT: 3");
		break;
	}

	win.draw(displayLivesLeft);
}

// drawIncomingShip function
void GameOverlay::drawIncomingShip(sf::RenderWindow& win)
{
	sf::Text incomingShip;

	incomingShip.setString("SHIP INCOMING...");
	incomingShip.setFont(gameFont);
	incomingShip.setCharacterSize(30);
	incomingShip.setPosition(115, 165);

	win.draw(incomingShip);

}

// drawWinOverlay function
void GameOverlay::drawWinOverlay(sf::RenderWindow& win)
{
	sf::Text youWin;
	sf::Text pToPlayAgain;

	youWin.setString("YOU WIN!");
	youWin.setFont(gameFont);
	youWin.setCharacterSize(75);
	youWin.setPosition(75, 50);

	pToPlayAgain.setString("Press \'M\' to play again!");
	pToPlayAgain.setFont(gameFont);
	pToPlayAgain.setCharacterSize(25);
	pToPlayAgain.setPosition(70, 135);

	win.draw(youWin);
	win.draw(pToPlayAgain);
}

// drawLoseOverlay function
void GameOverlay::drawLoseOverlay(sf::RenderWindow& win)
{
	sf::Text youLose;
	sf::Text pToPlayAgain;

	youLose.setString("YOU LOSE!");
	youLose.setFont(gameFont);
	youLose.setCharacterSize(75);
	youLose.setPosition(50, 50);

	pToPlayAgain.setString("Press \'M\' to play again!");
	pToPlayAgain.setFont(gameFont);
	pToPlayAgain.setCharacterSize(25);
	pToPlayAgain.setPosition(75, 135);

	win.draw(youLose);
	win.draw(pToPlayAgain);
}

// drawLivesOverlay function
void GameOverlay::drawLivesOverlay(sf::RenderWindow& win)
{
	sf::Text livesLeftOverlay;

	livesLeftOverlay.setString("EXTRA LIVES LEFT:");
	livesLeftOverlay.setFont(gameFont);
	livesLeftOverlay.setCharacterSize(40);
	livesLeftOverlay.setPosition(50, 66);

	win.draw(livesLeftOverlay);
}

// drawPauseOverlay function
void GameOverlay::drawPauseOverlay(sf::RenderWindow& win)
{
	sf::RectangleShape pauseBlock;
	sf::RectangleShape objectiveBlock;
	sf::Text gamePaused;
	sf::Text controls;
	sf::Text goal;

	pauseBlock.setSize(sf::Vector2f(220, 165));
	pauseBlock.setPosition(sf::Vector2f(89, 100));
	pauseBlock.setOutlineColor(sf::Color(255, 255, 255));
	pauseBlock.setOutlineThickness(1);
	pauseBlock.setFillColor(sf::Color(0, 0, 0));

	objectiveBlock.setSize(sf::Vector2f(220, 50));
	objectiveBlock.setPosition(sf::Vector2f(89, 264));
	objectiveBlock.setOutlineColor(sf::Color(255, 255, 255));
	objectiveBlock.setOutlineThickness(1);
	objectiveBlock.setFillColor(sf::Color(0, 0, 0));

	gamePaused.setString("Game Paused");
	gamePaused.setFont(gameFont);
	gamePaused.setCharacterSize(35);
	gamePaused.setPosition(94, 94);

	controls.setString("\'Esc\' = Pause \n\'Up\' = Accelerate \n\'Left\' = Turn Left \n\'Right\' = Turn Right \n\'Space\' = Shoot Photons \n\'M\' = Main Menu \n\'R\' = Reset Game");
	controls.setFont(gameFont);
	controls.setCharacterSize(20);
	controls.setPosition(94, 129);

	goal.setString("OBJECTIVE: \nDESTROY ALL ASTEROIDS!");
	goal.setFont(gameFont);
	goal.setCharacterSize(20);
	goal.setPosition(94, 265);

	win.draw(pauseBlock);
	win.draw(gamePaused);
	win.draw(controls);
	win.draw(objectiveBlock);
	win.draw(goal);
}