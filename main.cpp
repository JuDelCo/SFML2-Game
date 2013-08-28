#include "Game/DemoController.hpp"


typedef std::shared_ptr<TechDemo> gamePtr;


int main(const int argc, const char* args[])
{
	gamePtr demo(new TechDemo());
	demo->start();

	return 0;
}
