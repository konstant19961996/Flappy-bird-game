#pragma once
#include<SFML\Audio.hpp>
#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\System.hpp>
#include<iostream>
#include<sstream>
#include<time.h>
#include<fstream>
using namespace std;
class Pipes;
class Bird : public sf::Transformable
{
private:
	sf::SoundBuffer get_point_buffer;
	sf::SoundBuffer go_up_buffer;
	sf::SoundBuffer die_buffer;
public:
	sf::Texture yellow_bird_texture;
	sf::Texture blue_bird_texture;
	sf::Sprite bird;
	sf::Sound get_point;
	sf::Sound go_up;
	sf::Sound die;
	float y;
	float x;
	float length;
	float width;
	int points;
	float speed;
	//Bird ();
	int load_file();
	void move_bird();
	string return_points();
	bool check_collision (const Pipes &pipes);
	void over_chimney (Pipes &pipe);
	bool point (Pipes &pipe);
	void reset_bird(int Lev);
};