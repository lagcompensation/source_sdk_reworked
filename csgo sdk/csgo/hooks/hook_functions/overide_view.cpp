#include "../hooks.hpp"
#include "../../features/features.hpp"
#include "../../includes.hpp"
#include "../../sdk/includes.hpp"

void __fastcall hooks::override_view( void* _this, int edx, csgo::c_view_setup* view )
{
	static auto o_overrideview = c_hooks.clientmode_hook.get_original< hooks::override_view_fn >( c_hooks.vtable_indexes.override_view );

	if ( !csgo::i::engine->is_in_game( ) || !csgo::i::engine->is_connected( ) || !csgo::g_local ) {
		o_overrideview( csgo::i::clientmode, edx, view );
		return;
	}

	o_overrideview( csgo::i::clientmode, edx, view );
}
