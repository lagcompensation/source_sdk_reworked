#include "../hooks.hpp"
#include "../../features/features.hpp"
#include "../../includes.hpp"
#include "../../sdk/includes.hpp"

/* lock cursor */
void __fastcall hooks::lock_cursor( void* ecx, void* edx )
{
	auto o_lockcursor = c_hooks.surface_hook.get_original< hooks::lock_cursor_fn >( c_hooks.vtable_indexes.lock_cursor );

	if ( !menu.opened )
		return o_lockcursor( csgo::i::surface );

	csgo::i::surface->unlock_cursor( );
}