#include "../hooks.hpp"
#include "../../features/features.hpp"
#include "../../includes.hpp"
#include "../../sdk/includes.hpp"

/* draw model execute */
void __fastcall hooks::draw_model_exec( void* _this, int edx, void* ctx, const csgo::draw_model_state_t& state, const csgo::model_render_info_t& info, matrix3x4_t* custom_bone_to_world )
{
	static auto o_draw_model_exec = c_hooks.mdlrender_hook.get_original< hooks::draw_model_exec_fn >( c_hooks.vtable_indexes.draw_model_exec );

	if ( csgo::i::model_render->is_forced_mat( ) || !csgo::i::engine->is_in_game( ) || !csgo::i::engine->is_connected( ) || !csgo::g_local )
		return o_draw_model_exec( csgo::i::model_render, edx, ctx, state, info, custom_bone_to_world );


	o_draw_model_exec( csgo::i::model_render, edx, ctx, state, info, custom_bone_to_world );
	csgo::i::model_render->force_mat( nullptr );
}


/* credits unknowncheats : Disable model occulusion */
int __fastcall hooks::list_leaves_in_box( void* bsp, void* edx, vec3_t& mins, vec3_t& maxs, unsigned short* list, int list_max )
{
	static auto o_list_leaves_in_box = c_hooks.bsptreequery_hook.get_original<hooks::list_leaves_in_box_fn>( c_hooks.vtable_indexes.list_leaves_in_box );

	if ( !csgo::i::engine->is_in_game( ) )
		return o_list_leaves_in_box( bsp, mins, maxs, list, list_max );

	static auto r_list_leaves_in_box = csgo::c_utils.pattern_scan( GetModuleHandleA( _( "client.dll" ) ), _( "89 44 24 14 EB 08 C7 44 24 ? ? ? ? ? 8B 45" ) );
	if ( _ReturnAddress( ) != ( void* )r_list_leaves_in_box )
		return o_list_leaves_in_box( bsp, mins, maxs, list, list_max );

	struct renderable_info_t {
		csgo::i_client_renderable* renderable;
		void* alpha_property;
		int enum_count;
		int render_frame;
		unsigned short first_shadow;
		unsigned short leaf_list;
		short area;
		uint16_t flags;
		uint16_t flags2;
		vec3_t bloated_abs_mins;
		vec3_t bloated_abs_maxs;
		vec3_t abs_mins;
		vec3_t abs_maxs;
		int pad;
	};

	auto info = *( renderable_info_t** )( ( uintptr_t )_AddressOfReturnAddress( ) + 0x14 );
	if ( !info || !info->renderable )
		return o_list_leaves_in_box( bsp, mins, maxs, list, list_max );

	auto base_entity = info->renderable->get_client_unknown( )->get_base_entity( );
	if ( !base_entity || base_entity->get_client_class( )->m_class_id != csgo::class_id_cs_player )
		return o_list_leaves_in_box( bsp, mins, maxs, list, list_max );

	info->flags &= ~0x100;
	info->flags2 |= 0xC0;

	#define max_coord_float ( 16384.0f )
	#define min_coord_float ( -max_coord_float )

	static const vec3_t map_min = vec3_t( min_coord_float, min_coord_float, min_coord_float );
	static const vec3_t map_max = vec3_t( max_coord_float, max_coord_float, max_coord_float );

	auto ret = o_list_leaves_in_box( bsp, map_min, map_max, list, list_max );
	return ret;
}
