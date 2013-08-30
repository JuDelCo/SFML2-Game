#pragma once
#ifndef INPUT_HPP
#define INPUT_HPP


#include "InputData.hpp"
#include "../helpers/Event.hpp"


namespace sf
{
    class RenderWindow;
}


class Input
{
	public:
		Input();
		~Input();
		void onTick(sf::RenderWindow* window);
		void releaseAll();
		void releaseKeys();
		void releaseMouse();
		Key* getKey(const KeyInfo* keyStruct, unsigned int numberId);
		bool isWindowClosed();
		KeyInfo* getKeyPress();
		KeyInfo* getKeyHeld();
		KeyInfo* getKeyUp();
		MouseInfo* getMouse();

        EventManager3<void, int, int, int> m_eventHandler;

    protected:
		bool m_windowClosed;
		KeyInfo m_keyPress;
		KeyInfo m_keyHeld;
		KeyInfo m_keyUp;
		MouseInfo m_mouse;

	private:
		void pollEvents(sf::RenderWindow* window);
};


#endif // INPUT_HPP
