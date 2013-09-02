#include "PongController.hpp"


Pong::Pong() : GameBase(640, 480)
{
	reset();
}


Pong::~Pong()
{

}


void Pong::init()
{

}


void Pong::onTick()
{
	// Lógica del juego
}


void Pong::onRender()
{
	m_video->clear(sf::Color::Black);

	// Dibujar todo

	m_video->swapBuffers();
}


void Pong::onEvent(const int eventType, const int param1, const int param2)
{
	m_eventHandler.trigger(eventType);

	switch (eventType)
	{
		case EVENT_KEYDOWN:
			switch (param1)
			{
				case KEY::Escape:
					stop();
					break;

				case KEY::F1:
					reset();
					break;
			}

			break;

		case EVENT_QUIT:
			stop();

			break;
	}
}


void Pong::reset()
{
	// Resetear variables
}


void Pong::end()
{

}
