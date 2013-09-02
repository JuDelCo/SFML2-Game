#include "Game/pong/PongController.hpp"


typedef std::shared_ptr<Pong> gamePtr;


int main(const int argc, const char* args[])
{
	gamePtr demo(new Pong());
	demo->start();

	return 0;
}
