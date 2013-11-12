// Copyright (c) 2013 Juan Delgado (JuDelCo)
// License: zlib/libpng License
// zlib/libpng License web page: http://opensource.org/licenses/Zlib

#include "Input.hpp"
#include <string.h>
#include "../Defines.hpp"
#include "../video/Video.hpp"

Input::Input()
{
	m_windowClosed = false;

	releaseAll();
}

void Input::onTick(RenderWindowPtr window)
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

	memcpy(&m_keyPress, &KEY_CONFIG, sizeof(KeyInfo));
	memcpy(&m_keyUp, &KEY_CONFIG, sizeof(KeyInfo));

	pollEvents(window);
}

void Input::releaseAll()
{
	releaseKeys();
	releaseMouse();
}

void Input::releaseKeys()
{
	memcpy(&m_keyPress, &KEY_CONFIG, sizeof(KeyInfo));
	memcpy(&m_keyHeld, &KEY_CONFIG, sizeof(KeyInfo));
	memcpy(&m_keyUp, &KEY_CONFIG, sizeof(KeyInfo));
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

KeyPtr Input::getKey(KeyInfoPtr keyStruct, unsigned int numberId)
{
	return KeyPtr(((Key*)(keyStruct.get())) + numberId);
}

bool Input::isWindowClosed()
{
	return m_windowClosed;
}

KeyInfoPtr Input::getKeyPress()
{
	return KeyInfoPtr(&m_keyPress);
}

KeyInfoPtr Input::getKeyHeld()
{
	return KeyInfoPtr(&m_keyHeld);
}

KeyInfoPtr Input::getKeyUp()
{
	return KeyInfoPtr(&m_keyUp);
}

bool Input::isKeyPress(KeyId key)
{
	return getKey(getKeyPress(), key)->value;
}

bool Input::isKeyHeld(KeyId key)
{
	return getKey(getKeyHeld(), key)->value;
}

bool Input::isKeyUp(KeyId key)
{
	return getKey(getKeyUp(), key)->value;
}

MouseInfoPtr Input::getMouse()
{
	return MouseInfoPtr(&m_mouse);
}

MouseKeyPtr Input::getMousePress()
{
	return MouseKeyPtr(&m_mouse.press);
}

MouseKeyPtr Input::getMouseHeld()
{
	return MouseKeyPtr(&m_mouse.held);
}

MouseKeyPtr Input::getMouseUp()
{
	return MouseKeyPtr(&m_mouse.up);
}

sf::Vector2i Input::getMousePos()
{
	return sf::Vector2i(m_mouse.x, m_mouse.y);
}

sf::Vector2i Input::getMousePosRel()
{
	return sf::Vector2i(m_mouse.xRel, m_mouse.yRel);
}

void Input::pollEvents(RenderWindowPtr window)
{
	sf::Event event;

	while (window->pollEvent(event))
	{
		if(event.type == sf::Event::MouseMoved)
		{
			m_mouse.xRel = m_mouse.x - event.mouseMove.x;
			m_mouse.yRel = m_mouse.y - event.mouseMove.y;
			m_mouse.x = event.mouseMove.x;
			m_mouse.y = event.mouseMove.y;

			EventMouseMotion.emit(getMouse());
		}
		else if(event.type == sf::Event::KeyPressed)
		{
			for (unsigned int x = 0; x < NUMBER_OF_KEYS; ++x)
			{
				KeyPtr keyDown = getKey(getKeyPress(), x);
				KeyPtr keyHeld = getKey(getKeyHeld(), x);

				if (keyDown->sdlKey == event.key.code)
				{
					keyDown->value = true;
					keyHeld->value = true;

					EventKeyDown.emit(event.key.code);
				}
			}
		}
		else if(event.type == sf::Event::KeyReleased)
		{
			for (unsigned int x = 0; x < NUMBER_OF_KEYS; ++x)
			{
				KeyPtr keyUp = getKey(getKeyUp(), x);
				KeyPtr keyHeld = getKey(getKeyHeld(), x);

				if (keyUp->sdlKey == event.key.code)
				{
					keyUp->value = true;
					keyHeld->value = false;

					EventKeyUp.emit(event.key.code);
				}
			}
		}
		else if(event.type == sf::Event::MouseButtonPressed)
		{
			if(event.mouseButton.button == sf::Mouse::Left)
			{
				m_mouse.press.left = true;
				m_mouse.held.left = true;
				m_mouse.x = event.mouseButton.x;
				m_mouse.y = event.mouseButton.y;
			}
			else if(event.mouseButton.button == sf::Mouse::Middle)
			{
				m_mouse.press.middle = true;
				m_mouse.held.middle = true;
				m_mouse.x = event.mouseButton.x;
				m_mouse.y = event.mouseButton.y;
			}
			else if(event.mouseButton.button == sf::Mouse::Right)
			{
				m_mouse.press.right = true;
				m_mouse.held.right = true;
				m_mouse.x = event.mouseButton.x;
				m_mouse.y = event.mouseButton.y;
			}

			EventMouseDown.emit(getMouse());
		}
		else if(event.type == sf::Event::MouseButtonReleased)
		{
			if(event.mouseButton.button == sf::Mouse::Left)
			{
				m_mouse.up.left = true;
				m_mouse.held.left = false;
				m_mouse.x = event.mouseButton.x;
				m_mouse.y = event.mouseButton.y;
			}
			else if(event.mouseButton.button == sf::Mouse::Middle)
			{
				m_mouse.up.middle = true;
				m_mouse.held.middle = false;
				m_mouse.x = event.mouseButton.x;
				m_mouse.y = event.mouseButton.y;
			}
			else if(event.mouseButton.button == sf::Mouse::Right)
			{
				m_mouse.up.right = true;
				m_mouse.held.right = false;
				m_mouse.x = event.mouseButton.x;
				m_mouse.y = event.mouseButton.y;
			}

			EventMouseUp.emit(getMouse());
		}
		else if(event.type == sf::Event::TextEntered)
		{
			EventTextEntered.emit(event.text.unicode);
		}
		else if(event.type == sf::Event::MouseWheelMoved)
		{
			if (event.mouseWheel.delta > 0)
			{
				m_mouse.press.wheelUp = true;
				m_mouse.held.wheelUp = false;
				m_mouse.up.wheelUp = false;

				EventMouseWheel.emit(true);
			}
			else
			{
				m_mouse.press.wheelDown = true;
				m_mouse.held.wheelDown = false;
				m_mouse.up.wheelDown = false;

				EventMouseWheel.emit(false);
			}

			// Unset "KeyPress" of mouse wheel after the event because doesn't have a "KeyUp"
			m_mouse.press.wheelUp = false;
			m_mouse.press.wheelDown = false;
		}
		else if(event.type == sf::Event::MouseEntered)
		{
			EventMouseFocus.emit();
		}
		else if(event.type == sf::Event::MouseLeft)
		{
			releaseMouse();

			EventMouseBlur.emit();
		}
		else if(event.type == sf::Event::GainedFocus)
		{
			EventKeyFocus.emit();
		}
		else if(event.type == sf::Event::LostFocus)
		{
			releaseKeys();

			EventKeyBlur.emit();
		}
		else if(event.type == sf::Event::Resized)
		{
			EventVideoResize.emit(sf::Vector2i(event.size.width, event.size.height));
		}
		else if(event.type == sf::Event::Closed)
		{
			m_windowClosed = true;

			EventQuit.emit();

			return;
		}
	}

	m_mouse.x = sf::Mouse::getPosition(*window).x;
	m_mouse.y = sf::Mouse::getPosition(*window).y;
}
