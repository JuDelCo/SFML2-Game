#ifndef PONG_CONTROLLER_HPP
#define PONG_CONTROLLER_HPP


#include "../Engine/Includes.hpp"


class Pong : public GameBase
{
	public:
		EventManager1<void, int> m_eventHandler;
		Pong();
		~Pong();

	private:
		void init();
		void onTick();
		void onRender();
		void onEvent(const int eventType, const int param1, const int param2);
		void reset();
		void end();

		Vector2f m_ballPos;
		Vector2u m_ballMov;
		Vector2f m_playerPos;
		Vector2f m_cpuPos;
		unsigned int m_playerScore;
		unsigned int m_cpuScore;
		sf::Font m_fuente = sf::Font();
		sf::Text m_marcador;
};


#endif // PONG_CONTROLLER_HPP
