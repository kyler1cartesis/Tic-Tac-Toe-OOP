#include "built-in's.cpp"
using namespace std;

#include "Game.h"

int main() {
    srand(time(0));
    setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    Game game;
    game.run();
    return 0;
}
