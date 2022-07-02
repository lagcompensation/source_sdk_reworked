#include "../hooks.hpp"
#include "../../features/features.hpp"
#include "../../includes.hpp"
#include "../../sdk/includes.hpp"

void __fastcall hooks::frame_stage_notify( void* ecx, void* edx, int stage )
{
	static auto o_frame_stage_notify = c_hooks.clientdll_hook.get_original< hooks::frame_stage_notify_fn >( c_hooks.vtable_indexes.frame_stage_notify );

	if ( !csgo::i::engine->is_in_game( ) || !csgo::g_local ) {
		o_frame_stage_notify( ecx, edx, stage );
		return;
	}

	/* switching stages */
	switch ( stage ) {
		case csgo::frame_start: {

		} break;
		case csgo::frame_net_update_start: {

		} break;
		case csgo::frame_net_update_postdataupdate_start: {

		} break;
		case csgo::frame_net_update_postdataupdate_end: {

		} break;
		case csgo::frame_net_update_end: {

		} break;
		case csgo::frame_render_start: {

		} break;
		case csgo::frame_render_end: {

		} break;
	}

	o_frame_stage_notify( ecx, edx, stage );
}
