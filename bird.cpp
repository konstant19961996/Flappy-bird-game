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
/*Bird::Bird()
{
	y=300;
	x=30;
	length=50;
	width=50;
	points=0;
	speed=3.5;
}*/
int Bird::load_file()
{
	if (!yellow_bird_texture.loadFromFile("img/flappy.png"))
		return -1;
	bird.setTexture(yellow_bird_texture);
	if (!blue_bird_texture.loadFromFile("img/flappy2.png"))
		return -1;
	if (!get_point_buffer.loadFromFile("sounds/get_point.ogg"))
		return -1;
	get_point.setBuffer(get_point_buffer);
	if (!go_up_buffer.loadFromFile("sounds/go_up.ogg"))
		return -1;
	go_up.setBuffer(go_up_buffer);
	if (!die_buffer.loadFromFile("sounds/die.ogg"))
		return -1;
	die.setBuffer(die_buffer);
	return 1;
}
void Bird::move_bird()
{
	y+=speed;
	bird.setPosition(x,y);
}
string Bird::return_points()
{
	std::stringstream points_ss;
	points_ss<<points;
	std::string points_to_view=points_ss.str();
	return points_to_view;
}
bool Bird::check_collision ( const Pipes &pipes)
{
   // if (x+width<pipes.x && x+width>pipes.x+pipes.pipe_width)
	//		return true;
	if ((y<pipes.y_up+pipes.pipe_len && y>pipes.y_up) ||
		(y<pipes.y_down+pipes.pipe_len && y>pipes.y_down) ||
		(y+length<pipes.y_up+pipes.pipe_len && y+length>pipes.y_up) ||
		(y+length<pipes.y_down+pipes.pipe_len && y+length>pipes.y_down))
	{
		if (x+width>pipes.x && x+width<pipes.x+pipes.pipe_width)
			return true;
		if (y<=-40 || y>=500)
			return true;
	}
	return false;
}
void Bird::over_chimney (Pipes &pipe)
{
	/*if (pipe.x==0)
	{
		points+=1;
		return true;
	}*/
	if (pipe.x<=-200)
	{
		pipe.x=800;
		//points += 1;
		pipe.rand_chimneys();
		//return true;
	}
	/*else
	{
		return false;
	}*/
}
void Bird::reset_bird(int Lev)
{
	if (Lev==2)
	{
	speed=3;
	}
	else if (Lev==1)
	{
		speed=1;
	}
	y=300;
	x=30;
	length=50;
	width=50;
	points=0;
}
bool Bird::point (Pipes &pipe)
{
	float sp=pipe.speed*1.2;
	if (pipe.x<0 && pipe.x>-sp && check_collision(pipe)==false)
	{
		points+=1;
		return true;
	}
	else
		return false;
}

