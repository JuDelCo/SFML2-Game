// Copyright (c) 2013 Juan Delgado (JuDelCo)
// License: zlib/libpng License
// zlib/libpng License web page: http://opensource.org/licenses/Zlib

#pragma once
#ifndef TETRIS_CONTROLLER_HPP
#define TETRIS_CONTROLLER_HPP

#include "../../Engine/Includes.hpp"
#include <SFML/Audio.hpp>

class Tetris : public GameBase
{
	public:
		typedef std::shared_ptr<Tetris> Ptr;

		Tetris();
		~Tetris() {}

	private:
		void onTick();
		void onRender();
		void onKeyDown(int keyCode);
		void onQuit();
		void reset();
		sf::Color getColor(unsigned int colorId);
		void changeNextBlock();
		bool checkCollision(sf::Vector2i playerPosition);
		void copyBlockInfoToPlayer();
		void copyPlayerToBoard();
		void changePlayerBlock();
		bool checkLinesBoard();
		void rotatePlayerBlocks();

		struct BlockInfo
		{
			unsigned int color;
			bool isBlock;
		};

		sf::Sound m_sound;
		sf::SoundBuffer m_collideSound;
		sf::SoundBuffer m_scoreSound;
		sf::Font m_scoreFont;
		Timer m_timingTimer;
		Timer m_sliderTimer;
		unsigned int m_lastUpdateTime;
		static int blockInfo[10][4*4];
		static int blockInfoColor[10];
		sf::Vector2i m_screenSize;
		bool m_hardMode;
		sf::Vector2i m_blockSize;
		std::vector<BlockInfo> m_blockStack;
		std::vector<BlockInfo> m_blockPlayerStack;
		sf::Vector2i m_blockStackSize;
		sf::Vector2i m_blockPlayerStackSize;
		sf::Vector2i m_playerPosition;
		unsigned int m_playerBlockId;
		unsigned int m_nextBlockId;
		unsigned int m_playerScore;
};

#endif // TETRIS_CONTROLLER_HPP
