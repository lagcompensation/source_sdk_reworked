#include "../hooks.hpp"
#include "../../features/features.hpp"
#include "../../includes.hpp"
#include "../../sdk/includes.hpp"

void __fastcall hooks::set_key_code_state( void* _this, void* edx, int code, bool down )
{
	static auto o_set_key_code_state = c_hooks.inputinternal_hook.get_original< hooks::set_key_code_state_fn >( c_hooks.vtable_indexes.set_key_code_state );

	if ( menu.input_should_listen && down )
	{
		menu.input_should_listen = false;
		if ( menu.input_received_key_value )
			*menu.input_received_key_value = code;
	}

	return o_set_key_code_state( _this, code, down );
}

void __fastcall hooks::set_mouse_code_state( void* _this, void* edx, int code, int state )
{
	static auto o_set_mouse_code_state = c_hooks.inputinternal_hook.get_original< hooks::set_key_code_state_fn >( c_hooks.vtable_indexes.set_mouse_code_state );

	if ( menu.input_should_listen && state == csgo::button_pressed )
	{
		menu.input_should_listen = false;
		if ( menu.input_received_key_value )
			*menu.input_received_key_value = code;
	}

	return o_set_mouse_code_state( _this, code, state );
}
