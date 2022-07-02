#pragma once
#include "..\..\..\utils\vfunc.hpp"
#include "..\..\classes\c_material.hpp"

namespace csgo {

	class c_material_system {
	public:

		c_material* find_material( const char* name, const char* group = nullptr ) {
			using o_fn = c_material * ( __thiscall* )( void*, const char*, const char* );
			return get_vfunc< o_fn >( this, 84 )( this, name, group );
		}

	};

}
