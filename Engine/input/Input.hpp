// Copyright (c) 2013 Juan Delgado (JuDelCo)
// License: zlib/libpng License
// zlib/libpng License web page: http://opensource.org/licenses/Zlib

#pragma once
#ifndef INPUT_HPP
#define INPUT_HPP

#include <SFML/Graphics.hpp>
#include "InputData.hpp"
#include "../helpers/Event.hpp"

typedef std::shared_ptr<sf::RenderWindow> RenderWindowPtr;

class Input
{
	public:
		typedef std::shared_ptr<Input> Ptr;

		Input();
		~Input() {}

		void onTick(RenderWindowPtr window);
		void releaseAll();
		void releaseKeys();
		void releaseMouse();
		bool isWindowClosed();
		KeyInfoPtr getKeyPress();
		KeyInfoPtr getKeyHeld();
		KeyInfoPtr getKeyUp();
		bool isKeyPress(KeyId key);
		bool isKeyHeld(KeyId key);
		bool isKeyUp(KeyId key);
		MouseInfoPtr getMouse();
		MouseKeyPtr getMousePress();
		MouseKeyPtr getMouseHeld();
		MouseKeyPtr getMouseUp();
		sf::Vector2i getMousePos();
		sf::Vector2i getMousePosRel();

		EventManager<void (MouseInfoPtr)> EventMouseMotion;
		EventManager<void (MouseInfoPtr)> EventMouseDown;
		EventManager<void (MouseInfoPtr)> EventMouseUp;
		EventManager<void (bool)> EventMouseWheel;
		EventManager<void (int)> EventKeyDown;
		EventManager<void (int)> EventKeyUp;
		EventManager<void (sf::Uint32)> EventTextEntered;
		EventManager<void ()> EventMouseFocus;
		EventManager<void ()> EventMouseBlur;
		EventManager<void ()> EventKeyFocus;
		EventManager<void ()> EventKeyBlur;
		EventManager<void (sf::Vector2i)> EventVideoResize;
		EventManager<void ()> EventQuit;

	protected:
		KeyPtr getKey(KeyInfoPtr keyStruct, unsigned int numberId);

		bool m_windowClosed;
		KeyInfo m_keyPress;
		KeyInfo m_keyHeld;
		KeyInfo m_keyUp;
		MouseInfo m_mouse;

	private:
		void pollEvents(RenderWindowPtr window);
};

#endif // INPUT_HPP
