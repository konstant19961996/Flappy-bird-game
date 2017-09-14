#include<SFML\Audio.hpp>
#pragma once
#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\System.hpp>
#include<iostream>
#include<sstream>
#include<time.h>
#include<fstream>
using namespace std;
class Bird;
class Pipes : public sf::Transformable
{
private:
	sf::Texture texture_down_pipe;
	sf::Texture texture_up_pipe;
public:
	sf::Sprite pipe_down;
	sf::Sprite pipe_up;
	int free_space;
	float x;
	float y_up;
	float y_down;
	float pipe_len;
	float pipe_width;
	float speed;
	Pipes (float xx, int Lev);
	int load_file();
	void rand_chimneys();
	void move_chimneys();
};