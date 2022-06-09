#pragma once
#include "Player.h"
short Player::player_count = 0;

Player::Player(string _name, char _symbol) : name(_name), symbol(_symbol) { ++player_count; }

Player::Player(char _symbol) : symbol(_symbol) {
	switch (player_count)
	{
	case 0:
		cout << "¬ведите им€ дл€ первого игрока: "; break;
	case 1:
		cout << "¬ведите им€ дл€ второго игрока: "; break;
	default:
		cout << "¬ведите им€ дл€ следующего игрока: ";
		break;
	}
	//cin.sync();
	getline(cin, name);
	if (name.empty()) name = "Player " + to_string(++player_count);
	else ++player_count;
	cin.sync();
}