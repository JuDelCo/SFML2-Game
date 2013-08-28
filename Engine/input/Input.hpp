#pragma once
#ifndef INPUT_HPP
#define INPUT_HPP


#include "InputInterface.hpp"


class Input : public IInput
{
	public:
		Input();
		~Input();
		void onTick();
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
		void pollEvents();
};


#endif // INPUT_HPP
