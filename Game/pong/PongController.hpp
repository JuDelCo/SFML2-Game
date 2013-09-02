#pragma once
#ifndef PONG_CONTROLLER_HPP
#define PONG_CONTROLLER_HPP


#include "../../Engine/Includes.hpp"
#include <SFML/Audio.hpp>


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

		sf::Sound m_sound;
		sf::SoundBuffer m_pingSound;
		sf::SoundBuffer m_pongSound;
		sf::Font m_scoreFont;
		sf::Vector2i m_screenSize;
		sf::Vector2f m_ballPosition;
		sf::Vector2f m_ballVelocity;
		sf::Vector2f m_ballSize;
		sf::Vector2f m_playerPosition;
		sf::Vector2f m_playerSize;
		sf::Vector2f m_cpuPosition;
		sf::Vector2f m_cpuSize;
		unsigned int m_playerScore;
		unsigned int m_cpuScore;
};


#endif // PONG_CONTROLLER_HPP
