#include <intrin.h>
#include <time.h>
#include "hooks.hpp"
#include "../features/features.hpp"
#include "../includes.hpp"
#include "../sdk/includes.hpp"
#include "../utils/vftable_hook/vftable_hook.hpp"

/* include imgui */
#include "../menu/imgui/imgui.h"
#include "../menu/imgui/imgui_internal.h"
#include "../menu/imgui/impl/imgui_impl_dx9.h"
#include "../menu/imgui/impl/imgui_impl_win32.h"

hooks c_hooks;
void hooks::init( ) {

	/* get window handle */
	c_hooks.csgo_window = FindWindowA( _( "Valve001" ), nullptr );

	/* get local_player */
	csgo::g_local = *( csgo::c_local_player* ) ( csgo::c_utils.pattern_scan_c( GetModuleHandleA( _( "client.dll" ) ), _( "8B 0D ? ? ? ? 83 FF FF 74 07" ) ) + 2 );

	/* create fonts */
	csgo::c_utils.create_fonts( );

	/* hook wnd_proc */
	c_hooks.original_wndproc = SetWindowLongPtrA( c_hooks.csgo_window, GWLP_WNDPROC, ( LONG_PTR ) hooks::wnd_proc );

	/* initialize hooks functions */
	c_hooks.clientdll_hook.setup( csgo::i::clientdll );
	c_hooks.clientmode_hook.setup( csgo::i::clientmode );
	c_hooks.directx_hook.setup( csgo::i::dev );
	c_hooks.surface_hook.setup( csgo::i::surface );
	c_hooks.mdlrender_hook.setup( csgo::i::model_render );
	c_hooks.inputinternal_hook.setup( csgo::i::input_internal );
	c_hooks.bsptreequery_hook.setup( csgo::i::engine->get_bsp_tree_query( ) );

	/* hook functions */
	c_hooks.clientdll_hook.hook_index( c_hooks.vtable_indexes.create_move, hooks::create_move_hook );
	c_hooks.clientdll_hook.hook_index( c_hooks.vtable_indexes.frame_stage_notify, hooks::frame_stage_notify );
	c_hooks.clientmode_hook.hook_index( c_hooks.vtable_indexes.override_view, hooks::override_view );
	c_hooks.directx_hook.hook_index( c_hooks.vtable_indexes.end_scene, hooks::end_scene );
	c_hooks.directx_hook.hook_index( c_hooks.vtable_indexes.reset, hooks::reset );
	c_hooks.surface_hook.hook_index( c_hooks.vtable_indexes.lock_cursor, hooks::lock_cursor );
	c_hooks.mdlrender_hook.hook_index( c_hooks.vtable_indexes.draw_model_exec, hooks::draw_model_exec );
	c_hooks.inputinternal_hook.hook_index( c_hooks.vtable_indexes.set_key_code_state, hooks::set_key_code_state );
	c_hooks.inputinternal_hook.hook_index( c_hooks.vtable_indexes.set_mouse_code_state, hooks::set_mouse_code_state );
	c_hooks.bsptreequery_hook.hook_index( c_hooks.vtable_indexes.list_leaves_in_box, hooks::list_leaves_in_box );

	/* hook players */
	c_hooks.hook_players( );
}

void hooks::restore( ) {

	/* start animating back */ {
		if ( csgo::g_local ) {
			csgo::g_local->m_bClientSideAnimation( ) = true;
		}
	}

	/* restore hook functions */
	c_hooks.clientdll_hook.unhook_index( c_hooks.vtable_indexes.create_move );
	c_hooks.clientdll_hook.unhook_index( c_hooks.vtable_indexes.frame_stage_notify );
	c_hooks.clientmode_hook.unhook_index( c_hooks.vtable_indexes.override_view );
	c_hooks.directx_hook.unhook_index( c_hooks.vtable_indexes.end_scene );
	c_hooks.directx_hook.unhook_index( c_hooks.vtable_indexes.reset );
	c_hooks.surface_hook.unhook_index( c_hooks.vtable_indexes.lock_cursor );
	c_hooks.mdlrender_hook.unhook_index( c_hooks.vtable_indexes.draw_model_exec );
	c_hooks.inputinternal_hook.unhook_index( c_hooks.vtable_indexes.set_key_code_state );
	c_hooks.inputinternal_hook.unhook_index( c_hooks.vtable_indexes.set_mouse_code_state );
	c_hooks.bsptreequery_hook.unhook_index( c_hooks.vtable_indexes.list_leaves_in_box );

	/* unhook players */
	c_hooks.unhook_players( );

	/* restore wnd_proc */
	SetWindowLongPtrA( c_hooks.csgo_window, GWLP_WNDPROC, c_hooks.original_wndproc );

}