#ifndef VIDEO_HPP
#define VIDEO_HPP


#include "VideoInterface.hpp"
#include "SpriteAnimated.hpp"


class Video : public IVideo
{
	public:
		Video(unsigned int size_x, unsigned int size_y);
		~Video();
		void SwapBuffers();
		sf::Vector2u get_size();
		sf::RenderWindow* get_window();
		sf::Vector2f* get_camera_position();
		void DrawPoint(const float position_x, const float position_y, const sf::Color color);
		void DrawRectangle(const Vector2f position, const Vector2f size, const sf::Color color);

	private:
		void init(unsigned int size_x, unsigned int size_y);
		void init_window(unsigned int size_x, unsigned int size_y);
		void end();
};


#endif // VIDEO_HPP
