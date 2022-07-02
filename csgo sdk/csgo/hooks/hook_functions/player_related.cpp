#include "../hooks.hpp"
#include "../../features/features.hpp"
#include "../../includes.hpp"
#include "../../sdk/includes.hpp"

void __fastcall hooks::update_client_side_animation( void* ecx ) {
	static auto o_update_client_side_animation = c_hooks.players_hook.get_original<hooks::update_client_side_animation_fn>( c_hooks.vtable_indexes.update_client_side_animation );

	const auto e = ( csgo::c_base_player* )ecx;

	if ( !e || e->is_dormant( ) )
		return;	

	o_update_client_side_animation( ecx );
}

void __fastcall hooks::do_extra_bones_processing( void* ecx, void* edx, int a2, int a3, int a4, int a5, int a6, int a7 ) {
	static auto o_do_extra_bones_processing = c_hooks.players_hook.get_original<hooks::do_extra_bones_processing_fn>( c_hooks.vtable_indexes.do_extra_bones_processing );

	const auto e = ( csgo::c_base_player* ) ecx;
	if ( !e ) {
		o_do_extra_bones_processing( ecx, edx, a2, a3, a4, a5, a6, a7 );
		return;
	}

	auto animstate = e->get_animstate( );

	if ( !animstate || !animstate->m_entity ) {
		o_do_extra_bones_processing( ecx, edx, a2, a3, a4, a5, a6, a7 );
		return;
	}

	/* prevent call to do_procedural_foot_plant */
	const auto o_on_ground = animstate->m_on_ground;

	animstate->m_on_ground = false;

	o_do_extra_bones_processing( ecx, edx, a2, a3, a4, a5, a6, a7 );

	animstate->m_on_ground = o_on_ground;
}

bool __fastcall hooks::setup_bones( void* ecx, void* edx, matrix3x4_t* bone_to_world_out, int max_bones, int bone_mask, float curtime ) {
	static auto o_setup_bones = c_hooks.players_hook.get_original<hooks::setup_bones_fn>( c_hooks.vtable_indexes.setup_bones );

	return o_setup_bones( ecx, edx, bone_to_world_out, max_bones, bone_mask, curtime );
}

void hooks::hook_players( ) {

	for ( int i = 1; i < csgo::i::engine->get_max_clients( ); ++i )
	{
		auto player = csgo::c_base_player::get_player_by_index( i );

		if ( !player
			|| !player->is_alive( )
			|| player->is_dormant( ) )
		{
			if ( c_hooks.hooked_players[ i ] ) {
				/* unhook indexes */
				c_hooks.players_hook.unhook_index( c_hooks.vtable_indexes.update_client_side_animation );
				c_hooks.players_hook.unhook_index( c_hooks.vtable_indexes.do_extra_bones_processing );
				c_hooks.players_hook.unhook_index( c_hooks.vtable_indexes.setup_bones );
			}

			c_hooks.hooked_players[ i ] = false;
			continue;
		}


		if ( c_hooks.hooked_players[ i ] ) {
			/* unhook indexes */
			c_hooks.players_hook.unhook_index( c_hooks.vtable_indexes.update_client_side_animation );
			c_hooks.players_hook.unhook_index( c_hooks.vtable_indexes.do_extra_bones_processing );
			c_hooks.players_hook.unhook_index( c_hooks.vtable_indexes.setup_bones );
		}

		if ( !c_hooks.hooked_players[ i ] )
		{
			/* setup hook */
			c_hooks.players_hook.setup( player );

			/* hook indexes */
			c_hooks.players_hook.hook_index( c_hooks.vtable_indexes.update_client_side_animation, hooks::update_client_side_animation );
			c_hooks.players_hook.hook_index( c_hooks.vtable_indexes.do_extra_bones_processing, hooks::do_extra_bones_processing );
			c_hooks.players_hook.hook_index( c_hooks.vtable_indexes.setup_bones, hooks::setup_bones );

			c_hooks.hooked_players[ i ] = true;
		}
	}
}

void hooks::unhook_players( ) {

	for ( int i = 1; i < csgo::i::engine->get_max_clients( ); ++i ) {
		if ( c_hooks.hooked_players[ i ] ) {
			c_hooks.players_hook.unhook_index( c_hooks.vtable_indexes.update_client_side_animation );
			c_hooks.players_hook.unhook_index( c_hooks.vtable_indexes.do_extra_bones_processing );
			c_hooks.players_hook.unhook_index( c_hooks.vtable_indexes.setup_bones );
		}
	}

}