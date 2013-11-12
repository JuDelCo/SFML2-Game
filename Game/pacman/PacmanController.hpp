// Copyright (c) 2013 Juan Delgado (JuDelCo)
// License: zlib/libpng License
// zlib/libpng License web page: http://opensource.org/licenses/Zlib

#pragma once
#ifndef PACMAN_CONTROLLER_HPP
#define PACMAN_CONTROLLER_HPP

#include "../../Engine/Includes.hpp"
#include <SFML/Audio.hpp>

class Pacman : public GameBase
{
	public:
		Pacman();
		~Pacman() {}

	private:
		void onTick();
		void onRender();
		void onKeyDown(int keyCode);
		void onQuit();
		void reset();

		enum CellType
		{
			Nothing = 0,
			Wall,
			Ball,
			BallBig,
			GhostStartPosition,
			GhostDoor,
			PacmanStartPosition
		};

		enum ViewDirection
		{
			Up = 0,
			Left,
			Right,
			Down
		};

		struct PacmanEntity
		{
			sf::Texture TileSet;
			sf::Sprite Sprite;
			unsigned int CurrentFrame;
			ViewDirection Direction;
			ViewDirection DesiredDirection;
			unsigned int CurrentCellIndex;
			sf::Vector2f PositionOffset;
			float MoveSpeed;
			bool Moving;
			unsigned int Lives;
			bool IsDead;
		};

		struct GhostEntity
		{
			sf::Sprite Sprite;
			unsigned int CurrentFrame;
			ViewDirection Direction;
			ViewDirection DesiredDirection;
			unsigned int CurrentCellIndex;
			sf::Vector2f PositionOffset;
			sf::Color color;
			float MoveSpeed;
			bool Moving;
			unsigned int TimeToRelease;
			unsigned int HomeIndex;
			bool IsDead;
			bool Invulnerable;
			unsigned int LastCellChecked;
			bool IsInChase;
			unsigned int StateDuration;
			unsigned int LastStateChange;
		};

		struct Node
		{
			unsigned int Index;
			Node* ParentNode;
			unsigned int Range; // ( xAxis + yAxis )
			unsigned int Cost; 	// (*ParentNode.Cost+1)

			Node()
			{
				Index = 0;
				ParentNode = NULL;
				Range = 0;
				Cost = 0;
			}
		};

		void resetGame();
		bool loadMap();
		void mapSetCell(unsigned int cellIndex, CellType cellType);
		bool checkCollision(unsigned int cellIndex, ViewDirection direction, bool isPlayer);
		void moveEntity(unsigned int* cellIndex, sf::Vector2f* offset, ViewDirection* direction, ViewDirection* desiredDirection, bool* isMoving, float speed, bool isPlayer);
		ViewDirection getNextDirection(unsigned int startIndex, unsigned int searchIndex, unsigned int ignoreCell);
		ViewDirection getRandomDirection(unsigned int cellIndex, unsigned int ignoreCell);
		unsigned int getMapIndex(unsigned int cellIndex, ViewDirection direction);
		unsigned int getMapInfo(unsigned int cellIndex, ViewDirection direction);
		void ghostCollide(unsigned int ghostId);
		void addScore(unsigned int score);

		sf::Sound m_sound;
		sf::SoundBuffer m_killSound;
		sf::SoundBuffer m_deadSound;
		sf::SoundBuffer m_ballSound;
		sf::SoundBuffer m_powerupSound;
		sf::Font m_textFont;
		sf::Vector2i m_screenSize;
		sf::Vector2i m_tileSize;
		unsigned int m_mapInfo[28*31];
		unsigned int m_mapNullCell;
		std::vector<sf::Vector2i> m_ballPosition;
		std::vector<sf::Vector2i> m_ballBigPosition;
		unsigned int m_powerupKillCounter;
		sf::Vector2i m_mapScreenOffset;
		sf::Texture m_mapTileSet;
		sf::VertexArray m_mapVertexArray;
		sf::Vector2i m_mapSize;
		Timer m_frameTimer;
		Timer m_gameTimer;
		Timer m_ghostKillTimer;
		Timer m_readyTimer;
		Timer m_pauseTimer;
		PacmanEntity m_player;
		sf::Texture m_ghostTileSet;
		GhostEntity m_ghost[4];
		unsigned int m_ghostCount;
		unsigned int m_gameScore;
		sf::Sprite m_liveSprite;
};

typedef std::shared_ptr<Pacman> PacmanPtr;

#endif // PACMAN_CONTROLLER_HPP
