#include "ball.h"
Ball::Ball(float startX, float startY)
{
	position.x=startX;
	position.y=startY;
	ballShape.setSize(sf::Vector2f(10,10));
	ballShape.setPosition(position);
	xVelocity = .2f;
	yVelocity = .2f;
}
FloatRect Ball::getPosition()
{
	return ballShape.getGlobalBounds();
}
RectangleShape Ball::getShape()
{
	return ballShape;
}
float Ball::getXVelocity()
{
	return xVelocity;
}
void Ball::reboundSides()
{
	xVelocity = -xVelocity;
}
void Ball::reboundBatOrTop()
{
	position.y -= (yVelocity*30);
	yVelocity = -yVelocity;
}
void Ball::hitBottom()
{
	position.x=1;
	position.y=500;
}
void Ball::update()
{
	position.y += yVelocity;
	position.x += xVelocity;
	ballShape.setPosition(position);
}

