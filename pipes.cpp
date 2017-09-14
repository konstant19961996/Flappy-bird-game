#include<SFML\Audio.hpp>
#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\System.hpp>
#include<iostream>
#include<sstream>
#include<time.h>
#include<fstream>
#include"bird.h"
#include"pipes.h"
using namespace std;
Pipes::Pipes (float xx, int Lev)
{
	free_space=150;
	x=800;
	//y_up=100;
	//y_down=100;
	pipe_len=375;
	pipe_width=150;
	if (Lev==2)
	{
	speed=3;
	}
	else if (Lev==1)
	{
		speed=1;
	}
	x=xx;
}
int Pipes::load_file()
{
	if (!texture_up_pipe.loadFromFile("img/pipe_up.png"))
		return -1;
	pipe_up.setTexture(texture_up_pipe);
	if (!texture_down_pipe.loadFromFile("img/pipe_down.png"))
		return -1;
	pipe_down.setTexture(texture_down_pipe);
	return 1;
}
void Pipes::rand_chimneys()
{
	y_up=(std :: rand() % (150+free_space))-(150+free_space);
	y_down=y_up + pipe_len + free_space;
}
void Pipes::move_chimneys()
{
	x-=speed;
	pipe_up.setPosition(x,y_up);
	pipe_down.setPosition(x,y_down);
}