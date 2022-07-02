#pragma once
#include "..\..\utils\vfunc.hpp"
#include "..\matrix3x4.hpp"
#include "..\vec3.hpp"

namespace csgo {

	enum material_var_flags_t : int32_t
	{
		material_var_debug = ( 1 << 0 ),
		material_var_no_debug_override = ( 1 << 1 ),
		material_var_no_draw = ( 1 << 2 ),
		material_var_use_in_fillrate_mode = ( 1 << 3 ),
		material_var_vertexcolor = ( 1 << 4 ),
		material_var_vertexalpha = ( 1 << 5 ),
		material_var_selfillum = ( 1 << 6 ),
		material_var_additive = ( 1 << 7 ),
		material_var_alphatest = ( 1 << 8 ),
		material_var_znearer = ( 1 << 10 ),
		material_var_model = ( 1 << 11 ),
		material_var_flat = ( 1 << 12 ),
		material_var_nocull = ( 1 << 13 ),
		material_var_nofog = ( 1 << 14 ),
		material_var_ignorez = ( 1 << 15 ),
		material_var_decal = ( 1 << 16 ),
		material_var_envmapsphere = ( 1 << 17 ), // obsolete
		material_var_unused = ( 1 << 18 ), // unused
		material_var_envmapcameraspace = ( 1 << 19 ), // obsolete
		material_var_basealphaenvmapmask = ( 1 << 20 ),
		material_var_translucent = ( 1 << 21 ),
		material_var_normalmapalphaenvmapmask = ( 1 << 22 ),
		material_var_needs_software_skinning = ( 1 << 23 ), // obsolete
		material_var_opaquetexture = ( 1 << 24 ),
		material_var_envmapmode = ( 1 << 25 ), // obsolete
		material_var_suppress_decals = ( 1 << 26 ),
		material_var_halflambert = ( 1 << 27 ),
		material_var_wireframe = ( 1 << 28 ),
		material_var_allowalphatocoverage = ( 1 << 29 ),
		material_var_alpha_modified_by_proxy = ( 1 << 30 ),
		material_var_vertexfog = ( 1 << 31 ),
	};

	class c_material_var {

		void set_vector_internal( const float x, const float y )
		{
			using o_fn = void( __thiscall* )( void*, float, float );
			return get_vfunc<o_fn>( this, 10 )( this, x, y );
		}

		void set_vector_internal( const float x, const float y, const float z )
		{
			using o_fn = void( __thiscall* )( void*, float, float, float );
			return get_vfunc<o_fn>( this, 11 )( this, x, y, z );
		}

	public:
		void set_float( const float val )
		{
			using o_fn = void( __thiscall* )( void*, float );
			return get_vfunc<o_fn>( this, 4 )( this, val );
		}

		void set_int( const int val )
		{
			using o_fn = void( __thiscall* )( void*, int );
			return get_vfunc<o_fn>( this, 5 )( this, val );
		}

		void set_string( char const* val )
		{
			using o_fn = void( __thiscall* )( void*, char const* );
			return get_vfunc<o_fn>( this, 6 )( this, val );
		}

		void set_matrix( matrix3x4_t& matrix )
		{
			using o_fn = void( __thiscall* )( void*, matrix3x4_t& );
			return get_vfunc<o_fn>( this, 6 )( this, matrix );
		}

		void set_vector_component( const float val, const int comp )
		{
			using o_fn = void( __thiscall* )( void*, float, int );
			return get_vfunc<o_fn>( this, 26 )( this, val, comp );
		}

		void set_vector( const vec2_t vector )
		{
			set_vector_internal( vector.x, vector.y );
		}

		void set_vector( const vec3_t vector )
		{
			set_vector_internal( vector.x, vector.y, vector.z );
		}
	};

	class c_material {
	public:

		const char* get_name( void ) {
			using o_fn = const char* ( __thiscall* )( void* );
			return get_vfunc< o_fn >( this, 0 )( this );
		}

		const char* get_texture_group_name( void ) {
			using o_fn = const char* ( __thiscall* )( void* );
			return get_vfunc< o_fn >( this, 1 )( this );
		}

		void increment_reference_count( void ) {
			using o_fn = void( __thiscall* )( void* );
			return get_vfunc< o_fn >( this, 12 )( this );
		}

		c_material_var* find_var( const char* var, bool* found, bool complain = true ) {
			using o_fn = c_material_var * ( __thiscall* )( void*, const char*, bool*, bool );
			return get_vfunc< o_fn >( this, 11 )( this, var, found, complain );
		}

		void alpha_modulate( float a ) {
			using o_fn = void( __thiscall* )( void*, float );
			return get_vfunc< o_fn >( this, 27 )( this, a );
		}

		void color_modulate( float r, float g, float b ) {
			using o_fn = void( __thiscall* )( void*, float, float, float );
			return get_vfunc< o_fn >( this, 28 )( this, r, g, b );
		}

		void set_material_var_flag( material_var_flags_t flag, bool state ) {
			using o_fn = void( __thiscall* )( void*, material_var_flags_t, bool );
			return get_vfunc< o_fn >( this, 29 )( this, flag, state );
		}

	};


}
