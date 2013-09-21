// Copyright (c) 2013 Juan Delgado (JuDelCo)
// License: zlib/libpng License
// zlib/libpng License web page: http://opensource.org/licenses/Zlib

#pragma once
#ifndef PONG_CONTROLLER_HPP
#define PONG_CONTROLLER_HPP

#include "../../Engine/Includes.hpp"
#include <SFML/Audio.hpp>

class Pong : public GameBase
{
	public:
		Pong();
		~Pong() {};

	private:
		void onTick();
		void onRender();
		void onKeyDown(int keyCode);
		void onQuit();
		void reset();

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

typedef std::shared_ptr<Pong> PongPtr;

#endif // PONG_CONTROLLER_HPP
