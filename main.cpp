#include "Game/tetris/TetrisController.hpp"


typedef std::shared_ptr<Tetris> gamePtr;


int main(const int argc, const char* args[])
{
	gamePtr demo(new Tetris());
	demo->start();

	return 0;
}
