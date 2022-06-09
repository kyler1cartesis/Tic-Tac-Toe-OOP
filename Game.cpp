#pragma once
#include "Game.h"
#include <set>
#include <cassert>
void clearBadInput();

Game::Game() :field(9, ' ') {}

Game::Game(string _p1, string _p2) :field(9, ' '), player1(_p1,'X'), player2(_p2,'O') {}

void Game::run() {
	char input = 'a';
	do {
		if (game_finished) {
			while (true) {
				cout << "Начать новую игру? (y/n) ";
				cin >> input;
				if (input == 'y') {
					fill(field.begin(), field.end(), ' ');
					game_finished = false;
					cin.sync();
					break;
				}
				else if (input == 'n') {
					break;
				}
			}
		}
		if (game_finished) {
			cout << "Игра окончена!";
			return;
		}
		assert("Не,ну тут мои полномочия всё, окончены!",
			(player1.symbol == 'X' or player2.symbol == 'O')
			and (player1.symbol == 'X' or player2.symbol == 'O'));
		play(initToss());
		system("cls");

	} while (true);
	//char b = -1;
	//while (true) {
	//    catch (Error& e) {
	//        cerr << e;
	//        system("pause");
	//        system("cls");
	//    }
	//    catch (...) { cerr << "\nUnknown error!\n"; }
	//}
}
	
void Game::play(Players first_player) {
	bool ticker{};
	Player* current_player{};
	if (first_player == Players::Player1) {
		ticker = 1;
	}
	else if (first_player == Players::Player2) {
		ticker = 0;
	}
	Game::Players p{};
	while (!game_finished) {
		system("cls");
		cout << game_title;
		printField();
		if (ticker) current_player = &player1;
		else current_player = &player2;
		make_a_Move(*current_player);
		ticker = !ticker;
		p = checkVictory();
		if (p != Players::Noone) {
			
			game_finished = true;
		}
	}
	system("cls");
	cout << game_title;
	printField();
	if (p == Players::Player1) {
		++player1.score;
		cout << "Первый игрок выиграл! Игра окончена!\n";
	}
	else {
		++player2.score;
		cout << "Второй игрок выиграл! Игра окончена!\n";

	}
	cin.ignore();
	//cin.get();
	clearBadInput();
}

void Game::make_a_Move(Player& player) {
	short pos = -1;
	cout << player.name << ", ваш ход (1-9): ";
	while (!(cin >> pos and 0 < pos and pos < 10 and field[pos - 1] == ' ')) {
		cout << "Неправильный ввод, введите номер незанятой клетки!\n";
		if (cin.fail()) clearBadInput();
		//cin.sync();
	}
	field[pos-1] = player.symbol;
}

void Game::printField() {
	cout << " _ _ _\n";
	for (auto it=field.begin(); it!=field.end(); ++it) {
		cout << '|' << *it << '|' << *++it << '|' << *++it
			<< "\n _ _ _\n";
	}
	cout << '\n';
}


Game::Players Game::checkVictory() {
	static vector<bool> engaged_cells(9, false);
	constexpr static auto isEqual3chars = [](const char a, const char b, const char c) -> bool { return a == b and a == c; };
	if (engaged_cells[4] or field[4] != ' ') {
		engaged_cells[4] = true;
		if (isEqual3chars(field[1], field[4], field[7])
			or isEqual3chars(field[3], field[4], field[5])
			or isEqual3chars(field[2], field[4], field[6]))
			return field[4] == 'X' ? Players::Player1 : Players::Player2;
	}
	if (engaged_cells[0] or field[0] != ' ') {
		engaged_cells[0] = true;
		if (isEqual3chars(field[0], field[1], field[2])
			or isEqual3chars(field[0], field[3], field[6])
			or engaged_cells[4] and isEqual3chars(field[0], field[4], field[8]))
				return field[0] == 'X' ? Players::Player1 : Players::Player2;
	}
	if (engaged_cells[8] or field[8] != ' ') {
		engaged_cells[8] = true;
		if (isEqual3chars(field[2], field[5], field[8])
			or isEqual3chars(field[6], field[7], field[8]))
				return field[8] == 'X' ? Players::Player1 : Players::Player2;;
	}
	return Players::Noone;
}

Game::Players Game::initToss() {
	bool winner = rand() % 2;
	char winner_symbol;
	set<char> allowed_chars_for_X{ 'X','x' };
	set<char> allowed_chars_for_O{ 'O','o','0' };
	int map[]{ 2,1 };
	cout << "По результатам жеребьёвки победил игрок " << map[winner] << "!\n"
		<< "Пожалуйста, введите выбранный символ (X/O): ";
	while (true) {
		cin >> winner_symbol;
		if (!(allowed_chars_for_X.contains(winner_symbol)
			or allowed_chars_for_O.contains(winner_symbol))) {
			cin.sync();
			continue;
		}
		if (winner == allowed_chars_for_X.contains(winner_symbol)) {
			player1.symbol = 'X';
			player2.symbol = 'O';
			break;
		}
		else {
			player1.symbol = 'O';
			player2.symbol = 'X';
			break;
		}
	}
	if (winner) return Players::Player1;
	else return Players::Player2;
}