#pragma once
#include <string>
#include <iostream>
using namespace std;

class Player
{
	friend class Game;
private:
	string name;
	short score = 0;
	char symbol;
public:
	Player(string _name, char symbol);
	Player(char _symbol = NULL);
	
	static short player_count;
	
};


