#include "Input.hpp"
#include <string.h>
#include "../Defines.hpp"
#include "../ServiceProvider.hpp"
#include "../video/VideoInterface.hpp"


Input::Input()
{
	m_windowClosed = false;

	releaseAll();
}


Input::~Input()
{
}


void Input::onTick()
{
	m_mouse.xRel = 0;
	m_mouse.yRel = 0;
	m_mouse.press.left = false;
	m_mouse.press.middle = false;
	m_mouse.press.right = false;
	m_mouse.press.wheelUp = false;
	m_mouse.press.wheelDown = false;
	m_mouse.up.left = false;
	m_mouse.up.middle = false;
	m_mouse.up.right = false;
	m_mouse.up.wheelUp = false;
	m_mouse.up.wheelDown = false;

	memcpy(&m_keyPress, &KEY::KEY_CONFIG, sizeof(KeyInfo));
	memcpy(&m_keyUp, &KEY::KEY_CONFIG, sizeof(KeyInfo));

	pollEvents();
}


void Input::releaseAll()
{
	releaseKeys();
	releaseMouse();
}


void Input::releaseKeys()
{
	memcpy(&m_keyPress, &KEY::KEY_CONFIG, sizeof(KeyInfo));
	memcpy(&m_keyHeld, &KEY::KEY_CONFIG, sizeof(KeyInfo));
	memcpy(&m_keyUp, &KEY::KEY_CONFIG, sizeof(KeyInfo));
}


void Input::releaseMouse()
{
	m_mouse.xRel = 0;
	m_mouse.yRel = 0;
	m_mouse.press.left = false;
	m_mouse.press.middle = false;
	m_mouse.press.right = false;
	m_mouse.press.wheelUp = false;
	m_mouse.press.wheelDown = false;
	m_mouse.held.left = false;
	m_mouse.held.middle = false;
	m_mouse.held.right = false;
	m_mouse.held.wheelUp = false;
	m_mouse.held.wheelDown = false;
	m_mouse.up.left = false;
	m_mouse.up.middle = false;
	m_mouse.up.right = false;
	m_mouse.up.wheelUp = false;
	m_mouse.up.wheelDown = false;
}


Key* Input::getKey(const KeyInfo* key_struct, unsigned int numberId)
{
	return (((Key*)key_struct) + numberId);
}


bool Input::isWindowClosed()
{
	return m_windowClosed;
}


KeyInfo* Input::getKeyPress()
{
	return &m_keyPress;
}


KeyInfo* Input::getKeyHeld()
{
	return &m_keyHeld;
}


KeyInfo* Input::getKeyUp()
{
	return &m_keyUp;
}


MouseInfo* Input::getMouse()
{
	return &m_mouse;
}


void Input::pollEvents()
{
	sf::Event event;

	IVideo* video = ServiceProvider::getVideo();

	while (video->getWindow()->pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::GainedFocus:
				m_eventHandler.trigger(EVENT_KEYFOCUS, 0, 0);
				break;

			case sf::Event::LostFocus:
				releaseKeys();
				m_eventHandler.trigger(EVENT_KEYBLUR, 0, 0);
				break;

			case sf::Event::KeyPressed:
				for (unsigned int x = 0; x < NUMBER_OF_KEYS; ++x)
				{
					Key* keyDown = getKey(&m_keyPress, x);
					Key* keyHeld = getKey(&m_keyHeld, x);

					if (keyDown->sdlKey == event.key.code)
					{
						keyDown->value = true;
						keyHeld->value = true;

						m_eventHandler.trigger(EVENT_KEYDOWN, keyDown->sdlKey, 0);
					}
				}

				break;

			case sf::Event::KeyReleased:
				for (unsigned int x = 0; x < NUMBER_OF_KEYS; ++x)
				{
					Key* keyUp = getKey(&m_keyUp, x);
					Key* keyHeld = getKey(&m_keyHeld, x);

					if (keyUp->sdlKey == event.key.code)
					{
						keyUp->value = true;
						keyHeld->value = false;

						m_eventHandler.trigger(EVENT_KEYUP, keyUp->sdlKey, 0);
					}
				}

				break;

			case sf::Event::MouseEntered:
				m_eventHandler.trigger(EVENT_MOUSEFOCUS, 0, 0);
				break;

			case sf::Event::MouseLeft:
				releaseMouse();
				m_eventHandler.trigger(EVENT_MOUSEBLUR, 0, 0);
				break;

			case sf::Event::MouseMoved:
				m_mouse.xRel = event.mouseMove.x - m_mouse.x;
				m_mouse.yRel = event.mouseMove.y - m_mouse.y;
				m_mouse.x = event.mouseMove.x;
				m_mouse.y = event.mouseMove.y;
				m_eventHandler.trigger(EVENT_MOUSEMOTION, 0, 0);
				break;

			case sf::Event::MouseButtonPressed:
				switch (event.mouseButton.button)
				{
					case sf::Mouse::Left:
						m_mouse.press.left = true;
						m_mouse.held.left = true;
						m_mouse.x = event.mouseButton.x;
						m_mouse.y = event.mouseButton.y;
						break;

					case sf::Mouse::Middle:
						m_mouse.press.middle = true;
						m_mouse.held.middle = true;
						m_mouse.x = event.mouseButton.x;
						m_mouse.y = event.mouseButton.y;
						break;

					case sf::Mouse::Right:
						m_mouse.press.right = true;
						m_mouse.held.right = true;
						m_mouse.x = event.mouseButton.x;
						m_mouse.y = event.mouseButton.y;
						break;

					default:
						break;
				}

				m_eventHandler.trigger(EVENT_MOUSEDOWN, 0, 0);
				break;

			case sf::Event::MouseButtonReleased:
				switch (event.mouseButton.button)
				{
					case sf::Mouse::Left:
						m_mouse.up.left = true;
						m_mouse.held.left = false;
						m_mouse.x = event.mouseButton.x;
						m_mouse.y = event.mouseButton.y;
						break;

					case sf::Mouse::Middle:
						m_mouse.up.middle = true;
						m_mouse.held.middle = false;
						m_mouse.x = event.mouseButton.x;
						m_mouse.y = event.mouseButton.y;
						break;

					case sf::Mouse::Right:
						m_mouse.up.right = true;
						m_mouse.held.right = false;
						m_mouse.x = event.mouseButton.x;
						m_mouse.y = event.mouseButton.y;
						break;

					default:
						break;
				}

				m_eventHandler.trigger(EVENT_MOUSEUP, 0, 0);
				break;

			case sf::Event::MouseWheelMoved:
				if (event.mouseWheel.delta > 0)
				{
					m_mouse.press.wheelUp = true;
					m_mouse.held.wheelUp = false;
					m_mouse.up.wheelUp = false;
					m_mouse.x = event.mouseWheel.x; // ???
					m_mouse.y = event.mouseWheel.y; // ???
				}
				else
				{
					m_mouse.press.wheelDown = true;
					m_mouse.held.wheelDown = false;
					m_mouse.up.wheelDown = false;
					m_mouse.x = event.mouseWheel.x; // ???
					m_mouse.y = event.mouseWheel.y; // ???
				}

				m_eventHandler.trigger(EVENT_MOUSEWHEEL, 0, 0);
				m_mouse.press.wheelUp = false; // ?
				m_mouse.press.wheelDown = false; // ?
				break;

			case sf::Event::TextEntered:
				m_eventHandler.trigger(EVENT_TEXTENTERED, event.text.unicode, 0);
				break;

			case sf::Event::Resized:
				m_eventHandler.trigger(EVENT_VIDEORESIZE, event.size.width, event.size.height);
				break;

			case sf::Event::Closed:
				m_windowClosed = true;
				m_eventHandler.trigger(EVENT_QUIT, 0, 0);
				return;
				break;

			default:
				break;
		}
	}

	m_mouse.x = sf::Mouse::getPosition(*video->getWindow()).x;
	m_mouse.y = sf::Mouse::getPosition(*video->getWindow()).y;
}
