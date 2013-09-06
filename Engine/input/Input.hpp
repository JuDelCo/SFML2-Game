#pragma once
#ifndef INPUT_HPP
#define INPUT_HPP


#include <SFML/Graphics.hpp>
#include "InputData.hpp"
#include "../helpers/Event.hpp"


class Input
{
	public:
		Input();
		~Input();
		void onTick(sf::RenderWindow* window);
		void releaseAll();
		void releaseKeys();
		void releaseMouse();
		bool isWindowClosed();
		KeyInfo* getKeyPress();
		KeyInfo* getKeyHeld();
		KeyInfo* getKeyUp();
		MouseInfo* getMouse();
		sf::Vector2i getMousePos();

		EventManager3<void, int, int, int> m_eventHandler;

	protected:
		Key* getKey(const KeyInfo* keyStruct, unsigned int numberId);

		bool m_windowClosed;
		KeyInfo m_keyPress;
		KeyInfo m_keyHeld;
		KeyInfo m_keyUp;
		MouseInfo m_mouse;

	private:
		void pollEvents(sf::RenderWindow* window);
};


#endif // INPUT_HPP
