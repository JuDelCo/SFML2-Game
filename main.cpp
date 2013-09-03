#include "Game/snake/SnakeController.hpp"


typedef std::shared_ptr<Snake> gamePtr;


int main(const int argc, const char* args[])
{
	gamePtr demo(new Snake());
	demo->start();

	return 0;
}
