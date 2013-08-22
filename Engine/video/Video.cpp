#include "Video.hpp"
#include "../Defines.hpp"


Video::Video(unsigned int size_x, unsigned int size_y)
{
	this->init(size_x, size_y);
}


Video::~Video()
{
	this->end();
}


void Video::init(unsigned int size_x, unsigned int size_y)
{
	this->init_window(size_x, size_y);

	/*glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Normal blending

	glClearColor(0, 0, 0, 0);

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();*/

	this->window_.setKeyRepeatEnabled(false);
	this->window_.clear();

	//texture_Init();
	//sprite_Init();
	// TILEMAPS SUBSYSTEM
	// TEXT SUBSYSTEM

}


void Video::init_window(unsigned int size_x, unsigned int size_y)
{
	this->window_.create(sf::VideoMode(size_x, size_y), "Demo");

	this->window_.setFramerateLimit(FPS_LIMIT);
	//this->window.setVerticalSyncEnabled(true);

	if(!this->window_.isOpen())
	{
		//DEBUG.error(__LINE__, "Error at Init Window");
		exit(ERROR_INIT);
	}

	//this->debugDraw.LinkTarget(this->window);
}


void Video::end()
{
	// TEXT SUBSYSTEM
	// TILEMAPS SUBSYSTEM
	//sprite_End();
	//texture_End();

	this->window_.close();
}


void Video::SwapBuffers()
{
	this->window_.display();
}


/*void Video::set_zBuffer(bool set)
{
	if (set)
	{
		glEnable(GL_DEPTH_TEST);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}
}*/


/*void Video::setRender_2D()
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_CULL_FACE);
	//texture_Use(-1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 640, 480, 0, -1000.0, 1000.0);
	//glOrtho(0, GAME_SCREEN_X, GAME_SCREEN_Y, 0, -1000.0, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}*/


/*void Video::setRender_3D()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
	//texture_Use(-1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45.0f, (GLfloat)GAME_SCREEN_X / (GLfloat)GAME_SCREEN_Y, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}*/


sf::Vector2u Video::get_size()
{
	return this->window_.getSize();
}


sf::RenderWindow* Video::get_window()
{
	return &this->window_;
}


sf::Vector2f* Video::get_camera_position()
{
	return &this->camera_position_;
}


static sf::CircleShape circle_draw_point;
void Video::DrawPoint(const float position_x, const float position_y, const sf::Color color)
{
	circle_draw_point.setRadius(1);
	circle_draw_point.setFillColor(color);
	circle_draw_point.setPosition(position_x, position_y);

	this->window_.draw(circle_draw_point);
}


static sf::RectangleShape rectangle_draw_rectangle;
void Video::DrawRectangle(const Vector2f position, const Vector2f size, const sf::Color color)
{
	rectangle_draw_rectangle.setPosition(position.x, position.y);
	rectangle_draw_rectangle.setSize(sf::Vector2f(size.x, size.y));
	rectangle_draw_rectangle.setFillColor(color);

	this->window_.draw(rectangle_draw_rectangle);
}
