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
class Results
{
public:
	bool cheating;
	int correct;
	Results();
	bool check (int actual_result, int i);
	void save();
	string return_points(int i);
private:
	fstream results;
	string line;
	int best_result[2];
	int import_file();

};