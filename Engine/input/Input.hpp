#ifndef INPUT_HPP
#define INPUT_HPP


#include "InputInterface.hpp"


class Input : public IInput
{
	public:
		Input();
		~Input();
		void OnTick();
		void ReleaseAll();
		void ReleaseKeys();
		void ReleaseMouse();
		Key* GetKey(const KeyInfo* key_struct, unsigned int id_number);
		bool is_window_closed();
		KeyInfo* get_key_press();
		KeyInfo* get_key_held();
		KeyInfo* get_key_up();
		MouseInfo* get_mouse();

	private:
		void PollEvents();
};


#endif // INPUT_HPP
