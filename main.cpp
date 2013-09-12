#include "Game/pacman/PacmanController.hpp"


typedef std::shared_ptr<Pacman> gamePtr;


int main(const int argc, const char* args[])
{
	gamePtr demo(new Pacman());
	demo->start();

	return 0;
}
