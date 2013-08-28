#pragma once
#ifndef VIDEO_HPP
#define VIDEO_HPP


#include "VideoInterface.hpp"
#include "SpriteAnimated.hpp"


class Video : public IVideo
{
	public:
		Video(unsigned int sizeX, unsigned int sizeY);
		~Video();
		void swapBuffers();
		sf::Vector2u getSize();
		sf::RenderWindow* getWindow();
		sf::Vector2f* getCameraPosition();
		void drawPoint(const float positionX, const float positionY, const sf::Color color);
		void drawRectangle(const sf::Vector2f position, const sf::Vector2f size, const sf::Color color);

	private:
		void init(unsigned int sizeX, unsigned int sizeY);
		void initWindow(unsigned int sizeX, unsigned int sizeY);
		void end();
};


#endif // VIDEO_HPP
