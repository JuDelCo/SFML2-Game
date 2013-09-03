#pragma once
#ifndef SNAKE_CONTROLLER_HPP
#define SNAKE_CONTROLLER_HPP


#include "../../Engine/Includes.hpp"
#include <SFML/Audio.hpp>


class Snake : public GameBase
{
	public:
		EventManager1<void, int> m_eventHandler;
		Snake();
		~Snake();

	private:
		void init();
		void onTick();
		void onRender();
		void onEvent(const int eventType, const int param1, const int param2);
		void reset();
		void end();
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


#endif // SNAKE_CONTROLLER_HPP
