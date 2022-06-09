#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;

#include "Player.h"
class Game
{
	enum class Players {
		Noone,
		Player1,
		Player2,
	};
private:
	Player player1, player2;
	vector<char> field;
	bool game_finished = 0;

public:
	Game();
	Game(string _p1, string _p2);

	void printField();
	Game::Players checkVictory();
	Game::Players initToss();
	void run();
	void play(Players first_player);

	void make_a_Move(Player& player);

	//friend ostream& operator<<(ostream& in);
};
const string game_title("Игра Крестики - Нолики\n\n");
