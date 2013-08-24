#include "Game/PongController.hpp"


typedef std::shared_ptr<Pong> gamePtr;


int main(const int argc, const char* args[])
{
	gamePtr pong(new Pong());
	pong->start();

	return 0;
}
