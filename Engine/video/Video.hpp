#pragma once
#ifndef VIDEO_HPP
#define VIDEO_HPP


#include <SFML/Graphics.hpp>
#include <memory>

typedef std::shared_ptr<sf::RenderWindow> RenderWindowPtr;


class Video
{
	public:
		Video();
		~Video();
		bool init();
		void swapBuffers();
		sf::Vector2u getSize();
		RenderWindowPtr getWindow();
		sf::Vector2i getCameraPosition();
		float getFpsLimit();
		void setFpsLimit(float fpsLimit);
		void changeTitle(std::string title);
		void changeResolution(sf::Vector2u resolution);
		void setCameraPosition(sf::Vector2i position);
		void moveCameraPosition(sf::Vector2i offset);
		void viewReset(sf::FloatRect rect);
		void viewResetToCamera();
		void clear(sf::Color color);
		void draw(sf::Drawable& drawable);
		void drawPoint(const float positionX, const float positionY, const sf::Color color);
		void drawRectangle(const sf::Vector2f position, const sf::Vector2f size, const sf::Color color);

	protected:
		sf::Vector2u m_resolution;
		RenderWindowPtr m_window;
		sf::Vector2i m_cameraPosition;
		std::string m_title;
		float m_fpsLimit;

	private:
		void initWindow();
		void endWindow();
};


typedef std::shared_ptr<Video> VideoPtr;


#endif // VIDEO_HPP
