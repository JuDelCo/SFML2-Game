#include "Game/techdemo/DemoController.hpp"
#include "Game/pong/PongController.hpp"
#include "Game/snake/SnakeController.hpp"
#include "Game/arkanoid/ArkanoidController.hpp"
#include "Game/tetris/TetrisController.hpp"
#include "Game/pacman/PacmanController.hpp"


int main(const int argc, const char* args[])
{
	/* --------------------------------- */
	/* Uncomment ONE to compile the game */
	/* --------------------------------- */
	//TechDemoPtr game(new TechDemo());
	//PongPtr game(new Pong());
	//SnakePtr game(new Snake());
	//ArkanoidPtr game(new Arkanoid());
	//TetrisPtr game(new Tetris());
	PacmanPtr game(new Pacman());
	/* --------------------------------- */

	game->start();

	return 0;
}
