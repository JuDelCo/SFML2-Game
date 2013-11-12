// Copyright (c) 2013 Juan Delgado (JuDelCo)
// License: zlib/libpng License
// zlib/libpng License web page: http://opensource.org/licenses/Zlib

#pragma once
#ifndef SNAKE_CONTROLLER_HPP
#define SNAKE_CONTROLLER_HPP

#include "../../Engine/Includes.hpp"
#include <SFML/Audio.hpp>

class Snake : public GameBase
{
	public:
		Snake();
		~Snake() {}

	private:
		void onTick();
		void onRender();
		void onKeyDown(int keyCode);
		void onQuit();
		void reset();
		void createNewFood();

		enum
		{
			LeftDirection = 1,
			TopDirection,
			RightDirection,
			BottomDirection
		};

		struct CellStatus
		{
			unsigned char nextNodeDirection;
			bool isSnake;
			bool isFood;
		};

		sf::Sound m_sound;
		sf::SoundBuffer m_moveSound;
		sf::SoundBuffer m_pickupSound;
		Timer m_timingTimer;
		unsigned int m_lastUpdateTime;
		unsigned int m_snakeHeadPositionId;
		unsigned char m_snakeDirection;
		sf::Texture m_squareTexture;
		std::vector<sf::Sprite> m_cellSprite;
		std::vector<CellStatus> m_cellState;
		sf::Vector2i m_screenSize;
};

typedef std::shared_ptr<Snake> SnakePtr;

#endif // SNAKE_CONTROLLER_HPP
