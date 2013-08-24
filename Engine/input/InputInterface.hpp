#ifndef INPUT_INTERFACE_HPP
#define INPUT_INTERFACE_HPP


#include "InputData.hpp"
#include "../helpers/Event.hpp"


class IInput
{
	public:
		virtual ~IInput() {};
		virtual void onTick() = 0;
		virtual void releaseAll() = 0;
		virtual void releaseKeys() = 0;
		virtual void releaseMouse() = 0;
		virtual Key* getKey(const KeyInfo* keyStruct, unsigned int numberId) = 0;
		virtual bool isWindowClosed() = 0;
		virtual KeyInfo* getKeyPress() = 0;
		virtual KeyInfo* getKeyHeld() = 0;
		virtual KeyInfo* getKeyUp() = 0;
		virtual MouseInfo* getMouse() = 0;
		EventManager3<void, int, int, int> m_eventHandler;

	protected:
		bool m_windowClosed;
		KeyInfo m_keyPress;
		KeyInfo m_keyHeld;
		KeyInfo m_keyUp;
		MouseInfo m_mouse;
};


#endif // INPUT_INTERFACE_HPP
