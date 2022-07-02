#pragma once
#include "..\..\..\utils\vfunc.hpp"
#include "..\..\studio.hpp"

namespace csgo {

	class c_model_info {
	public:

		model_t* get_model( int index ) {
			using o_fn = model_t * ( __thiscall* )( void*, int );
			return get_vfunc< o_fn >( this, 1 )( this, index );
		}

		std::int32_t get_model_index( const char* name ) {
			using o_fn = std::int32_t( __thiscall* )( void*, const char* );
			return get_vfunc< o_fn >( this, 2 )( this, name );
		}

		const char* get_model_name( const model_t* mdl ) {
			using o_fn = const char* ( __thiscall* )( void*, const model_t* );
			return get_vfunc< o_fn >( this, 3 )( this, mdl );
		}

		studiohdr_t* studio_mdl( model_t* mdl ) {
			using o_fn = studiohdr_t * ( __thiscall* )( void*, model_t* );
			return get_vfunc< o_fn >( this, 32 )( this, mdl );
		}
	};

}
