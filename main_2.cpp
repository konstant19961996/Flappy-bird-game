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
#include"results.h"
#include"game.h"
using namespace std;
int main()
{
	srand(time(NULL));
	Game game;
	game.runGame();
	//system("pause");
	return 0;
}