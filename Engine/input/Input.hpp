#pragma once
#ifndef INPUT_HPP
#define INPUT_HPP


#include "InputInterface.hpp"





class Input : public IInput
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

	private:
		void pollEvents(sf::RenderWindow* window);
};


#endif // INPUT_HPP
