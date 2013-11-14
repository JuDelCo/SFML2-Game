// Copyright (c) 2013 Juan Delgado (JuDelCo)
// License: zlib/libpng License
// zlib/libpng License web page: http://opensource.org/licenses/Zlib

#pragma once
#ifndef ARKANOID_CONTROLLER_HPP
#define ARKANOID_CONTROLLER_HPP

#include "../../Engine/Includes.hpp"
#include <SFML/Audio.hpp>

class Arkanoid : public GameBase
{
	public:
		typedef std::shared_ptr<Arkanoid> Ptr;

		Arkanoid();
		~Arkanoid() {}

	private:
		void onTick();
		void onRender();
		void onKeyDown(int keyCode);
		void onQuit();
		void reset();

		struct BlockInfo
		{
			sf::Vector2f size;
			sf::Vector2f position;
			unsigned int life;
		};

		sf::Sound m_sound;
		sf::SoundBuffer m_wallCollideSound;
		sf::SoundBuffer m_brickCollideSound;
		sf::Vector2i m_screenSize;
		sf::Vector2f m_ballPosition;
		sf::Vector2f m_ballVelocity;
		sf::Vector2f m_ballSize;
		sf::Vector2f m_playerPosition;
		sf::Vector2f m_playerSize;
		std::vector<BlockInfo> m_blockStack;
};

#endif // ARKANOID_CONTROLLER_HPP
