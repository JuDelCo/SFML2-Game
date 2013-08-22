#ifndef INPUT_INTERFACE_HPP
#define INPUT_INTERFACE_HPP


#include "InputData.hpp"
#include "../helpers/Event.hpp"


class IInput
{
	public:
		virtual ~IInput() {};
		virtual void OnTick() = 0;
		virtual void ReleaseAll() = 0;
		virtual void ReleaseKeys() = 0;
		virtual void ReleaseMouse() = 0;
		virtual Key* GetKey(const KeyInfo* key_struct, unsigned int id_number) = 0;
		virtual bool is_window_closed() = 0;
		virtual KeyInfo* get_key_press() = 0;
		virtual KeyInfo* get_key_held() = 0;
		virtual KeyInfo* get_key_up() = 0;
		virtual MouseInfo* get_mouse() = 0;
		EventManager3<void, int, int, int> event_handler_;

	protected:
		bool window_closed_;
		KeyInfo key_press_;
		KeyInfo key_held_;
		KeyInfo key_up_;
		MouseInfo mouse_;
};


#endif // INPUT_INTERFACE_HPP
