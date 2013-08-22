#include "Game/PongController.hpp"


typedef std::shared_ptr<Pong> game_ptr;


int main(const int argc, const char* args[])
{
	game_ptr pong(new Pong());
	pong->Start();

	return 0;
}
