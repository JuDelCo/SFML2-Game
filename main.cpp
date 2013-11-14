// Copyright (c) 2013 Juan Delgado (JuDelCo)
// License: zlib/libpng License
// zlib/libpng License web page: http://opensource.org/licenses/Zlib

#include "Game/techdemo/DemoController.hpp"
#include "Game/pong/PongController.hpp"
#include "Game/snake/SnakeController.hpp"
#include "Game/arkanoid/ArkanoidController.hpp"
#include "Game/tetris/TetrisController.hpp"
#include "Game/pacman/PacmanController.hpp"
#include "Game/engitime/EngiTimeController.hpp"

int main(const int argc, const char* args[])
{
	/* --------------------------------- */
	/* Uncomment ONE to compile the game */
	/* --------------------------------- */
	GameBase::Ptr game(new TechDemo());
	//GameBase::Ptr game(new Pong());
	//GameBase::Ptr game(new Snake());
	//GameBase::Ptr game(new Arkanoid());
	//GameBase::Ptr game(new Tetris());
	//GameBase::Ptr game(new Pacman());
	/* --------------------------------- */

	game->start();

	return 0;
}
