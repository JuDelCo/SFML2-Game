#pragma once
#ifndef SPRITE_ANIMATED_HPP
#define SPRITE_ANIMATED_HPP


#include <SFML/Graphics.hpp>


class SpriteAnimated : public sf::Sprite
{
	public:
		SpriteAnimated();
		SpriteAnimated(const std::string location, const int numFrames, const int delay);
		~SpriteAnimated() {};
		void loadTexture(const std::string location, const int numFrames);
		void update(const int& msLastFrame);
		void setCurrentFrame(const int currentFrame);
		void setFrameWidth(const int frameWidth);
		void setNumOfFrames(const int numFrames);
		void setDelay(const int delay);
		int getCurrentFrame();
		int getFrameWidth();
		int getNumOfFrames();
		int getDelay();

	private:
		sf::Texture m_image;
		unsigned int m_currentFrame;
		unsigned int m_numFrames;
		int m_timeRemain;
		unsigned int m_frameWidth;
		float m_frameTime;
};


#endif // SPRITE_ANIMATED_HPP
