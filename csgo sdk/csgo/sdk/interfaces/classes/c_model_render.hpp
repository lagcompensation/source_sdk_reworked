#pragma once
#include "..\..\classes\c_material.hpp"
#include "..\..\matrix3x4.hpp"
#include "..\..\studio.hpp"
#include "..\..\vec3.hpp"
#include "c_engine_trace.hpp"

namespace csgo {
	class i_client_renderable;

	struct model_render_info_t
	{
		vec3_t origin;
		vec3_t angles;
		char pad[ 4 ];
		i_client_renderable* renderable;
		const model_t* model;
		const matrix3x4_t* model_to_world;
		const matrix3x4_t* lighting_offset;
		const vec3_t* lighting_origin;
		int flags;
		int entity_index;
		int skin;
		int body;
		int hitboxset;
		unsigned short instance;

		model_render_info_t( )
		{
			model_to_world = NULL;
			lighting_offset = NULL;
			lighting_origin = NULL;
		}
	};

	struct draw_model_state_t
	{
		studiohdr_t* studio_hdr;
		void* studio_hw_data;
		i_client_renderable* renderable;
		const matrix3x4_t* model_to_World;
		void* decals;
		int draw_flags;
		int lod;
	};

	class c_model_render {
	public:
		virtual int draw_model( int flags, void* renderable, unsigned short instance, int entity_index, const model_t* model, vec3_t const& origin, vec3_t const& angles, int skin, int body, int hitboxset, const matrix3x4_t* modelToWorld = NULL, const matrix3x4_t* pLightingOffset = NULL ) = 0;
		virtual void force_mat( c_material* mat, int nOverrideType = 0, int nOverrides = 0 ) = 0;
		virtual bool is_forced_mat( void ) = 0;
		virtual void set_view_target( const studiohdr_t* studio_hdr, int body_index, const vec3_t& target ) = 0;
		virtual unsigned short create_instance( void* renderable, void* cache = nullptr ) = 0;
		virtual void destroy_instance( unsigned short handle ) = 0;
		virtual void set_static_lighting( unsigned short handle, void* _handle ) = 0;
		virtual void* get_static_lighting( unsigned short handle ) = 0;
		virtual bool change_instance( unsigned short handle, void* renderable ) = 0;
		virtual void add_decal( unsigned short handle, ray_t& ray, const vec3_t& decal_ip, int decal_index, int body, bool no_poke_throuh, int max_LOD_to_decal ) = 0;
		virtual void remove_all_decals( unsigned short handle ) = 0;
		virtual bool model_has_decals( unsigned short handle ) = 0;
		virtual void remove_all_decals_from_all_models( ) = 0;
		virtual matrix3x4_t* draw_model_shadow_setup( void* renderable, int body, int skin, void* info, matrix3x4_t* custom_bone_to_world = nullptr ) = 0;
		virtual void draw_model_shadow( void* renderable, void* info, matrix3x4_t* custom_bone_to_world = nullptr ) = 0;
		virtual bool recompute_static_lighting( unsigned short handle ) = 0;
		virtual void release_all_static_prop_color_data( void ) = 0;
		virtual void restore_all_static_prop_color_data( void ) = 0;
		virtual int draw_model_ex( model_render_info_t& info ) = 0;
		virtual int draw_model_ex_static_prop( model_render_info_t& info ) = 0;
		virtual bool draw_model_setup( model_render_info_t& info, draw_model_state_t *state, matrix3x4_t* bone_to_world_out ) = 0;
		virtual void draw_model_execute( void* ctx, draw_model_state_t& state, const model_render_info_t& info, matrix3x4_t* custom_bone_to_world = nullptr ) = 0;
		virtual void setup_lighting( const vec3_t& center ) = 0;
		virtual int draw_static_prop_array_fast( void* props, int count, bool shadow_depth ) = 0;
		virtual void suppress_engine_lighting( bool suppress ) = 0;
		virtual void setup_color_meshes( int total_verts ) = 0;
		virtual void setup_lighting_ex( const vec3_t& center, unsigned short handle ) = 0;
		virtual bool get_brightest_shadowing_light_source( const vec3_t& center, vec3_t& light_pos, vec3_t& light_brightness, bool allow_non_tagged_lights ) = 0;
		virtual void compute_lighting_state( int count, const void* query, void* state, void* env_cubemap_texture ) = 0;
		virtual void get_model_decal_handles( void* decals, int decal_stride, int count, const unsigned short* handles ) = 0;
		virtual void compute_static_lighting_state( int count, const void* query, void* state, void* decal_state, void* static_lightning, void* env_cubemap_texture, void* color_mesh_handles ) = 0;
		virtual void cleanup_static_lighting_state( int count, void* color_mesh_handles ) = 0;

	};
}
