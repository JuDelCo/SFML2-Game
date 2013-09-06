#include "Game/arkanoid/ArkanoidController.hpp"


typedef std::shared_ptr<Arkanoid> gamePtr;


int main(const int argc, const char* args[])
{
	gamePtr demo(new Arkanoid());
	demo->start();

	return 0;
}
