#include<SFML\Graphics.hpp>
#include"CoreGame.h"
#include"GameState.h"
#include"MenuState.h"
CoreGame::CoreGame(sf::RenderWindow* window) : window(window)
{
	this->currentState=new MenuState(window,this);
}
void CoreGame::handleInput(sf::Event& event)
{
	this->currentState->handleInput(event);
}
void CoreGame::update()
{
	this->currentState->update();
}
void CoreGame::render()
{
	this->currentState->render;
}
CoreGame::~CoreGame()
{
	if (this->currentState != nullptr)
		delete this->currentState;
}
void CoreGame::changeState(GameState* newState)
{
	//delete existed previous state
	if (this->currentState !=nullptr)
		delete this->currentState;
	this->currentState=newState;
}