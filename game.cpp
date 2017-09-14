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
/*string setForm (int points)
{
	string form = "";
	if ((points / 10) % 10 ==1)
		form= "ochkov";
	else if (points % 10 == 0 || points & 10 > 5)
		form = "ochkov";
	else if (points % 10 == 1)
		form = "ochko";
	else if (points % 10 >= 2 && points % 10 <= 4)
		form = "ochka";
	return form;
}*/
Game::Game()
{
	state = END;
	if (bird.load_file()!=1)
		return;
	if (!font.loadFromFile("fonts/angrybirds-regular.ttf"))
		return;
	if (!background.loadFromFile("img/background.png"))
		return;
	if (!floor.loadFromFile("img/floor.png"))
		return;
	if (results.correct != 1)
		return;
	window.create(sf::VideoMode(800,600), "Flappy bird");
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
	Sounds=true;
	Level=2;
	state=MENU;
}
void Game::runGame()
{
	while (state != END)
	{
		switch (state)
		{
		case MENU:
			menu();
			break;
		case GAME:
			single();
			break;
		case GAME_OVER:
			state=GAME;
			single();
			break;
		case SCORE:
			score();
			break;
		case OPTIONS:
			options();
			break;
		case END:
			break;
		}
	}
}
void Game::menu()
{
	sf::Text title("Flappy bird by Konstantin Butuzov", font, 50);
	title.setStyle(sf::Text::Bold);
	title.setColor(sf::Color::Red);
	title.setPosition(800/2-title.getGlobalBounds().width/2,20);
	const int buttons = 4;
	sf::Text buttons_text[buttons];
	string str[] = {"Play", "Score", "Options", "Exit"};
	//string str[] = {"Èãðà", "Ñ÷¸ò", "Îïöèè", "Âûõîä"};
	for (int i=0; i<buttons; i++)
	{
		buttons_text[i].setFont(font);
		buttons_text[i].setCharacterSize(65);
		buttons_text[i].setString(str[i]);
		buttons_text[i].setPosition(800/2-buttons_text[i].getGlobalBounds().width/2, 150+i*120);
	}
	while (state==MENU)
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(window));
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
				state=END;
			else if (buttons_text[0].getGlobalBounds().contains(mouse) &&
				sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				state=GAME;
			}
			else if (buttons_text[1].getGlobalBounds().contains(mouse) &&
				sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				state=SCORE;
			}
			else if (buttons_text[2].getGlobalBounds().contains(mouse) &&
				sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				state=OPTIONS;
			}
			else if (buttons_text[3].getGlobalBounds().contains(mouse) &&
				sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				state=END;
			}
		}
		window.clear();
		for (int i=0; i<buttons; i++)
		{
			if (buttons_text[i].getGlobalBounds().contains(mouse))
				buttons_text[i].setColor(sf::Color::Yellow);
			else
				buttons_text[i].setColor(sf::Color::Yellow);
		}
		for (int i=0; i<buttons; i++)
		{
			window.draw(buttons_text[i]);
		}
		window.draw(title);
		window.display();
	}
}
void Game::single()
{
	bird.reset_bird(Level);
	bool colision=false;
	Pipes pipes(600,Level);
	Pipes pipes2(925,Level);
	Pipes pipes3(1250,Level);
	background_sprite.setTexture(background);
	background_sprite.setPosition(0,0);
	floor_sprite.setTexture(floor);
	floor_sprite.setPosition(0,550);
	pipes.rand_chimneys();
	pipes2.rand_chimneys();
	pipes3.rand_chimneys();
	text.setFont(font);
	error.setFont(font);
	text.setPosition(400,50);
	error.setPosition(5,200);
	error.setCharacterSize(50);
	error.setColor(sf::Color::Red);
	if (pipes.load_file()!=1)
		state=END;
	if (pipes2.load_file()!=1)
		state=END;
	if (pipes3.load_file()!=1)
		state=END;
	if (results.correct!=1)
		state=END;
	while (state==GAME)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if (bird.speed!=0)
				{
					bird.y-=40;
					if (Sounds) bird.go_up.play();
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && bird.speed == 0)
			{
				state=GAME_OVER;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && bird.speed == 0)
			{
				state=MENU;
			}
		}
		/*if (bird.over_chimney(pipes))
		{
			if (Sounds) bird.get_point.play();
		}*/

		bird.over_chimney(pipes);
		if (bird.point(pipes))
		{
			if (Sounds) bird.get_point.play();
		}

		/*if (bird.over_chimney(pipes2))
		{
			if (Sounds) bird.get_point.play();
		}*/
		bird.over_chimney(pipes2);
		if (bird.point(pipes2))
		{
			if (Sounds) bird.get_point.play();
		}
		/*if (bird.over_chimney(pipes3))
		{
			if (Sounds) bird.get_point.play();
		}*/
		
		bird.over_chimney(pipes3);
		if (bird.point(pipes3))
		{
			if (Sounds) bird.get_point.play();
		}
		
		if (bird.check_collision(pipes) == true || bird.check_collision(pipes2) == true || bird.check_collision(pipes3) == true)
		{
			bird.speed=0;
			pipes.speed=0;
			pipes2.speed=0;
			pipes3.speed=0;
			if (!colision)
			{
				colision=true;
				if (Sounds) bird.die.play();
			}
			if (results.check(bird.points, Level-1))
			{
				results.save();
			}
			error.setString("You lost! Your points: " +bird.return_points() + "\n" +
				"Your best score: " +results.return_points(Level-1)+ " points" + "\n" +
				"Press ESC to go to menu.");
		}
		else
		{
			error.setString("");
		}
		
		text.setString(bird.return_points());
		bird.move_bird();
		pipes.move_chimneys();
		pipes2.move_chimneys();
		pipes3.move_chimneys();
		window.clear();
		window.draw(background_sprite);
		window.draw(pipes.pipe_up);
		window.draw(pipes.pipe_down);
		window.draw(pipes2.pipe_up);
		window.draw(pipes2.pipe_down);
		window.draw(pipes3.pipe_up);
		window.draw(pipes3.pipe_down);
		window.draw(floor_sprite);
		window.draw(text);
		window.draw (bird.bird);
		window.draw(error);
		window.display();
	}
}
void Game::score()
{
	sf::Text title("Score info", font, 80);
	title.setStyle(sf::Text::Bold);
	title.setPosition(800/2-title.getGlobalBounds().width/2,20);
	const int buttons = 2;
	sf::Text buttons_text[buttons];
	string str[] = {"Your best score = " + results.return_points(Level-1), "Return to menu"};
	for (int i=0; i<buttons; i++)
	{
		buttons_text[i].setFont(font);
		buttons_text[i].setCharacterSize(65);
		buttons_text[i].setString(str[i]);
		buttons_text[i].setPosition(800/2-buttons_text[i].getGlobalBounds().width/2, 250+i*120);

	}
	while (state==SCORE)
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(window));
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
				state=MENU;
			else if (buttons_text[1].getGlobalBounds().contains(mouse) &&
				(sf::Mouse::isButtonPressed(sf::Mouse::Left)))
			{
				state=MENU;
			}
		}
		window.clear();
		for (int i=0; i<buttons; i++)
		{
			if (buttons_text[i].getGlobalBounds().contains(mouse))
				buttons_text[i].setColor(sf::Color::Yellow);
			else
				buttons_text[i].setColor(sf::Color::White);
		}
		for (int i=0; i<buttons; i++)
		{
			window.draw(buttons_text[i]);
		}
		window.draw(title);
		window.display();
	}
}
void Game::options()
{
	sf::Text title("Options", font, 80);
	title.setStyle(sf::Text::Bold);
	sf::Texture yellow_bird_texture;
	sf::Sprite yellow_bird;
	if (!yellow_bird_texture.loadFromFile("img/flappy.png"))
	{
		state=END;
		return;
	}
	yellow_bird.setTexture(yellow_bird_texture);
	sf::Texture blue_bird_texture;
	sf::Sprite blue_bird;
	if (!blue_bird_texture.loadFromFile("img/flappy2.png"))
	{
		state=END;
		return;
	}
	blue_bird.setTexture(blue_bird_texture);
	yellow_bird.setPosition(170,250);
	blue_bird.setPosition(620,250);
	title.setPosition(800/2-title.getGlobalBounds().width/2,20);
	const int buttons = 5;
	sf::Text buttons_text[buttons];
	string str[] = {"Yellow bird", "Blue bird", "Return to menu", "Sounds: ON","Level: Normal"};
	for (int i=0; i<buttons; i++)
	{
		buttons_text[i].setFont(font);
		buttons_text[i].setCharacterSize(65);
		buttons_text[i].setString(str[i]);
	}
	buttons_text[0].setPosition(50,150);
	buttons_text[1].setPosition(500,150);
	buttons_text[2].setPosition(800/2-buttons_text[2].getGlobalBounds().width/2, 490);
	buttons_text[3].setPosition(250,300);
	buttons_text[4].setPosition(250,400);
	if (Sounds)
	{
		buttons_text[3].setColor(sf::Color::Green);
		buttons_text[3].setString("Sounds: ON");
	}
	else
	{
		buttons_text[3].setColor(sf::Color::Red);
		buttons_text[3].setString("Sounds: OFF");
	}
	if (Level==1)
	{
		buttons_text[4].setColor(sf::Color::Green);
		buttons_text[4].setString("Level: Easy");
	}
	else if (Level==2)
	{
		buttons_text[4].setColor(sf::Color::Red);
		buttons_text[4].setString("Level: Normal");
	}
	while (state == OPTIONS)
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(window));
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type==sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
				state=MENU;
			else if ((buttons_text[0].getGlobalBounds().contains(mouse) || yellow_bird.getGlobalBounds().contains(mouse)) &&
				(sf::Mouse::isButtonPressed(sf::Mouse::Left)))
			{
				bird.bird.setTexture(bird.yellow_bird_texture);
			}
			else if ((buttons_text[1].getGlobalBounds().contains(mouse) || blue_bird.getGlobalBounds().contains(mouse)) &&
				(sf::Mouse::isButtonPressed(sf::Mouse::Left)))
			{
				bird.bird.setTexture(bird.blue_bird_texture);
			}
			else if (buttons_text[2].getGlobalBounds().contains(mouse) &&
				(sf::Mouse::isButtonPressed(sf::Mouse::Left)))
			{
				state=MENU;
			}
			else if (buttons_text[3].getGlobalBounds().contains(mouse) &&
				(sf::Mouse::isButtonPressed(sf::Mouse::Left)))
			{
				if (Sounds)
				{
					buttons_text[3].setString("Sounds: OFF");
					buttons_text[3].setColor(sf::Color::Red);
					Sounds=false;
				}
				else
				{
					buttons_text[3].setString("Sounds: ON");
					buttons_text[3].setColor(sf::Color::Green);
					Sounds=true;
				}
			}
			else if (buttons_text[4].getGlobalBounds().contains(mouse) &&
				(sf::Mouse::isButtonPressed(sf::Mouse::Left)))
			{
				if (Level==1)
				{
					buttons_text[4].setString("Level: Normal");
					buttons_text[4].setColor(sf::Color::Red);
					Level=2;
				}
				else if (Level==2)
				{
					buttons_text[4].setString("Level: Easy");
					buttons_text[4].setColor(sf::Color::Green);
					Level=1;
				}
			}
		}
		window.clear();
		for (int i=0; i<buttons; i++)
		{
			if (buttons_text[i].getGlobalBounds().contains(mouse))
				buttons_text[i].setColor(sf::Color::Yellow);
			else
				buttons_text[i].setColor(sf::Color::White);
		}
		for (int i=0; i<buttons; i++)
		{
			window.draw(buttons_text[i]);
		}
		window.draw(title);
		window.draw(yellow_bird);
		window.draw(blue_bird);
		window.display();
	}
}