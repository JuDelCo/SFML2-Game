#pragma once
#ifndef VIDEO_HPP
#define VIDEO_HPP


#include <SFML/Graphics.hpp>


class Video
{
	public:
		Video(unsigned int sizeX, unsigned int sizeY);
		~Video();
		void swapBuffers();
		sf::Vector2u getSize();
		sf::RenderWindow* getWindow();
		sf::Vector2i getCameraPosition();
		float getFpsLimit();
		void setFpsLimit(float fpsLimit);
		void setCameraPosition(sf::Vector2i position);
		void moveCameraPosition(sf::Vector2i offset);
		void viewReset(sf::FloatRect rect);
		void viewResetToCamera();
		void clear(sf::Color color);
		void draw(sf::Drawable& drawable);
		void drawPoint(const float positionX, const float positionY, const sf::Color color);
		void drawRectangle(const sf::Vector2f position, const sf::Vector2f size, const sf::Color color);

	protected:
		sf::RenderWindow m_window;
		sf::Vector2i m_cameraPosition;
		float m_fpsLimit;

	private:
		void init(unsigned int sizeX, unsigned int sizeY);
		void initWindow(unsigned int sizeX, unsigned int sizeY);
		void end();
};


#endif // VIDEO_HPP
