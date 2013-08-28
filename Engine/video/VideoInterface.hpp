#pragma once
#ifndef VIDEO_INTERFACE_HPP
#define VIDEO_INTERFACE_HPP


#include <SFML/Graphics.hpp>


class IVideo
{
	public:
		virtual ~IVideo() {};
		virtual void swapBuffers() = 0;
		virtual sf::Vector2u getSize() = 0;
		virtual sf::RenderWindow* getWindow() = 0;
		virtual sf::Vector2f* getCameraPosition() = 0;
		virtual void drawPoint(const float positionX, const float positionY, const sf::Color color) = 0;
		virtual void drawRectangle(const sf::Vector2f position, const sf::Vector2f size, const sf::Color color) = 0;

	protected:
		sf::RenderWindow m_window;
		sf::Vector2f m_cameraPosition;
};


#endif // VIDEO_INTERFACE_HPP
