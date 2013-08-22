#ifndef VIDEO_INTERFACE_HPP
#define VIDEO_INTERFACE_HPP


#include <SFML/Graphics.hpp>
#include "../helpers/Vector.hpp"


class IVideo
{
	public:
		virtual ~IVideo() {};
		virtual void SwapBuffers() = 0;
		virtual sf::Vector2u get_size() = 0;
		virtual sf::RenderWindow* get_window() = 0;
		virtual sf::Vector2f* get_camera_position() = 0;
		virtual void DrawPoint(const float position_x, const float position_y, const sf::Color color) = 0;
		virtual void DrawRectangle(const Vector2f position, const Vector2f size, const sf::Color color) = 0;

	protected:
		sf::RenderWindow window_;
		sf::Vector2f camera_position_;
};


#endif // VIDEO_INTERFACE_HPP
