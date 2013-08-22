#ifndef SPRITE_ANIMATED_HPP
#define SPRITE_ANIMATED_HPP


#include <SFML/Graphics.hpp>


class SpriteAnimated : public sf::Sprite
{
	public:
		SpriteAnimated();
		SpriteAnimated(const std::string location, const int num_frames, const int delay);
		~SpriteAnimated();
		void LoadTexture(const std::string location, const int num_frames);
		void Update(const int& milliseconds_last_frame);
		void set_current_frame(const int current_frame);
		void set_frame_width(const int frame_width);
		void set_num_of_frames(const int num_frames);
		void set_delay(const int delay);
		int get_current_frame();
		int get_frame_width();
		int get_num_of_frames();
		int get_delay();

	private:
		sf::Texture image_;
		unsigned int current_frame_;
		unsigned int num_frames_;
		int time_remain_;
		unsigned int frame_width_;
		float frame_time_;
};


#endif // SPRITE_ANIMATED_HPP
