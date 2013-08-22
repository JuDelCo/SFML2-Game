#include "Input.hpp"
#include <string.h>
#include "../Defines.hpp"
#include "../ServiceProvider.hpp"
#include "../video/VideoInterface.hpp"


Input::Input()
{
	this->window_closed_ = false;

	this->ReleaseAll();
}


Input::~Input()
{
}


void Input::OnTick()
{
	this->mouse_.x_rel = 0;
	this->mouse_.y_rel = 0;
	this->mouse_.press.left = false;
	this->mouse_.press.middle = false;
	this->mouse_.press.right = false;
	this->mouse_.press.wheel_up = false;
	this->mouse_.press.wheel_down = false;
	this->mouse_.up.left = false;
	this->mouse_.up.middle = false;
	this->mouse_.up.right = false;
	this->mouse_.up.wheel_up = false;
	this->mouse_.up.wheel_down = false;

	memcpy(&this->key_press_, &KEY::KEY_CONFIG, sizeof(KeyInfo));
	memcpy(&this->key_up_, &KEY::KEY_CONFIG, sizeof(KeyInfo));

	this->PollEvents();
}


void Input::ReleaseAll()
{
	this->ReleaseKeys();
	this->ReleaseMouse();
}


void Input::ReleaseKeys()
{
	memcpy(&this->key_press_, &KEY::KEY_CONFIG, sizeof(KeyInfo));
	memcpy(&this->key_held_, &KEY::KEY_CONFIG, sizeof(KeyInfo));
	memcpy(&this->key_up_, &KEY::KEY_CONFIG, sizeof(KeyInfo));
}


void Input::ReleaseMouse()
{
	this->mouse_.x_rel = 0;
	this->mouse_.y_rel = 0;
	this->mouse_.press.left = false;
	this->mouse_.press.middle = false;
	this->mouse_.press.right = false;
	this->mouse_.press.wheel_up = false;
	this->mouse_.press.wheel_down = false;
	this->mouse_.held.left = false;
	this->mouse_.held.middle = false;
	this->mouse_.held.right = false;
	this->mouse_.held.wheel_up = false;
	this->mouse_.held.wheel_down = false;
	this->mouse_.up.left = false;
	this->mouse_.up.middle = false;
	this->mouse_.up.right = false;
	this->mouse_.up.wheel_up = false;
	this->mouse_.up.wheel_down = false;
}


Key* Input::GetKey(const KeyInfo* key_struct, unsigned int id_number)
{
	return (((Key*)key_struct) + id_number);
}


bool Input::is_window_closed()
{
	return this->window_closed_;
}


KeyInfo* Input::get_key_press()
{
	return &this->key_press_;
}


KeyInfo* Input::get_key_held()
{
	return &this->key_held_;
}


KeyInfo* Input::get_key_up()
{
	return &this->key_up_;
}


MouseInfo* Input::get_mouse()
{
	return &this->mouse_;
}


void Input::PollEvents()
{
	sf::Event event;

	IVideo* video = ServiceProvider::get_video();

	while(video->get_window()->pollEvent(event))
	{
		switch(event.type)
		{
			case sf::Event::GainedFocus:
				this->event_handler_.Trigger(EVENT_KEYFOCUS, 0, 0);
				break;

			case sf::Event::LostFocus:
				this->ReleaseKeys();
				this->event_handler_.Trigger(EVENT_KEYBLUR, 0, 0);
				break;

			case sf::Event::KeyPressed:
				for(unsigned int x = 0; x < NUMBER_OF_KEYS; ++x)
				{
					Key* key_down = this->GetKey(&this->key_press_, x);
					Key* key_held = this->GetKey(&this->key_held_, x);

					if(key_down->sdl_key == event.key.code)
					{
						key_down->value = true;
						key_held->value = true;

						this->event_handler_.Trigger(EVENT_KEYDOWN, key_down->sdl_key, 0);
					}
				}

				break;

			case sf::Event::KeyReleased:
				for(unsigned int x = 0; x < NUMBER_OF_KEYS; ++x)
				{
					Key* key_up = this->GetKey(&this->key_up_, x);
					Key* key_held = this->GetKey(&this->key_held_, x);

					if(key_up->sdl_key == event.key.code)
					{
						key_up->value = true;
						key_held->value = false;

						this->event_handler_.Trigger(EVENT_KEYUP, key_up->sdl_key, 0);
					}
				}

				break;

			case sf::Event::MouseEntered:
				this->event_handler_.Trigger(EVENT_MOUSEFOCUS, 0, 0);
				break;

			case sf::Event::MouseLeft:
				this->ReleaseMouse();
				this->event_handler_.Trigger(EVENT_MOUSEBLUR, 0, 0);
				break;

			case sf::Event::MouseMoved:
				this->mouse_.x_rel = event.mouseMove.x - this->mouse_.x;
				this->mouse_.y_rel = event.mouseMove.y - this->mouse_.y;
				this->mouse_.x = event.mouseMove.x;
				this->mouse_.y = event.mouseMove.y;
				this->event_handler_.Trigger(EVENT_MOUSEMOTION, 0, 0);
				break;

			case sf::Event::MouseButtonPressed:
				switch(event.mouseButton.button)
				{
					case sf::Mouse::Left:
						this->mouse_.press.left = true;
						this->mouse_.held.left = true;
						this->mouse_.x = event.mouseButton.x;
						this->mouse_.y = event.mouseButton.y;
						break;

					case sf::Mouse::Middle:
						this->mouse_.press.middle = true;
						this->mouse_.held.middle = true;
						this->mouse_.x = event.mouseButton.x;
						this->mouse_.y = event.mouseButton.y;
						break;

					case sf::Mouse::Right:
						this->mouse_.press.right = true;
						this->mouse_.held.right = true;
						this->mouse_.x = event.mouseButton.x;
						this->mouse_.y = event.mouseButton.y;
						break;

					default:
						break;
				}

				this->event_handler_.Trigger(EVENT_MOUSEDOWN, 0, 0);
				break;

			case sf::Event::MouseButtonReleased:
				switch(event.mouseButton.button)
				{
					case sf::Mouse::Left:
						this->mouse_.up.left = true;
						this->mouse_.held.left = false;
						this->mouse_.x = event.mouseButton.x;
						this->mouse_.y = event.mouseButton.y;
						break;

					case sf::Mouse::Middle:
						this->mouse_.up.middle = true;
						this->mouse_.held.middle = false;
						this->mouse_.x = event.mouseButton.x;
						this->mouse_.y = event.mouseButton.y;
						break;

					case sf::Mouse::Right:
						this->mouse_.up.right = true;
						this->mouse_.held.right = false;
						this->mouse_.x = event.mouseButton.x;
						this->mouse_.y = event.mouseButton.y;
						break;

					default:
						break;
				}

				this->event_handler_.Trigger(EVENT_MOUSEUP, 0, 0);
				break;

			case sf::Event::MouseWheelMoved:
				if(event.mouseWheel.delta > 0)
				{
					this->mouse_.press.wheel_up = true;
					this->mouse_.held.wheel_up = false;
					this->mouse_.up.wheel_up = false;
					this->mouse_.x = event.mouseWheel.x; // ???
					this->mouse_.y = event.mouseWheel.y; // ???
				}
				else
				{
					this->mouse_.press.wheel_down = true;
					this->mouse_.held.wheel_down = false;
					this->mouse_.up.wheel_down = false;
					this->mouse_.x = event.mouseWheel.x; // ???
					this->mouse_.y = event.mouseWheel.y; // ???
				}

				this->event_handler_.Trigger(EVENT_MOUSEWHEEL, 0, 0);
				this->mouse_.press.wheel_up = false; // ?
				this->mouse_.press.wheel_down = false; // ?
				break;

			case sf::Event::TextEntered:
				this->event_handler_.Trigger(EVENT_TEXTENTERED, event.text.unicode, 0);
				break;

			case sf::Event::Resized:
				this->event_handler_.Trigger(EVENT_VIDEORESIZE, event.size.width, event.size.height);
				break;

			case sf::Event::Closed:
				this->window_closed_ = true;
				this->event_handler_.Trigger(EVENT_QUIT, 0, 0);
				return;
				break;

			default:
				break;
		}
	}

	this->mouse_.x = sf::Mouse::getPosition(*video->get_window()).x;
	this->mouse_.y = sf::Mouse::getPosition(*video->get_window()).y;
}
