#include<SFML\Audio.hpp>
#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\System.hpp>
#include<Windows.h>
#include<iostream>
#include<sstream>
#include<time.h>
#include<fstream>
#include"results.h"
using namespace std;
Results::Results()
{
	cheating=false;	
	correct=1;
	if (import_file()!=1)
	{
		LPCTSTR s1=L"Error at file open";
		LPCTSTR s2=L"ERROR";
		MessageBox(NULL,s1,s2,NULL);
		correct=-1;
	}
}
int Results::import_file()
{
	results.open("score.txt", ios::in);
	if (results.good()==false)
	{
		cout<<"Error at opening score.txt!"<<endl;
		return -1;
	}
	int i=0;
	while (getline(results, line))
	{
		if (atoi (line.c_str()) % 128 == 0)
		{
			best_result[i] = atoi(line.c_str()) / 128;
		    //best_result[0]=0;
		}
		else
		{
			LPCTSTR s1=L"Surprise, motherf*cker! You're cheater. Set score=0 at score.txt";
			LPCTSTR s2=L"ERROR";
			MessageBox(NULL,s1,s2,NULL);
			return -1;
		}
		i++;
	}
	results.close();
	return 1;
}
bool Results::check(int actual_result, int i)
{
	if (best_result[i]<actual_result)
	{
		best_result[i]=actual_result;
		return true;
	}
	return false;
}
void Results::save()
{
	results.open("score.txt", ios::out);
	for (int i=0; i<2; i++)
	{
	results<<(best_result[i] * 128)<<endl;
	}
	results.close();
}
string Results::return_points(int i)
{
	stringstream points_ss;
	points_ss<<best_result[i];
	string points_to_view=points_ss.str();
	return points_to_view;
}
