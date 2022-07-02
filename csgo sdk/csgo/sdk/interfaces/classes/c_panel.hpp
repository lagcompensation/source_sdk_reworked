#pragma once
#include "..\..\..\utils\vfunc.hpp"

namespace csgo {

	class c_panel
	{
	public:
		const char* get_name( unsigned int vguiPanel )
		{
			typedef const char* ( __thiscall * o_fn ) ( void*, unsigned int );
			return get_vfunc< o_fn >( this, 36 ) ( this, vguiPanel );
		}
#ifdef get_class_name
#undef get_class_name
#endif
		const char* get_class_name( unsigned int vguiPanel )
		{
			typedef const char* ( __thiscall * o_fn ) ( void*, unsigned int );
			return get_vfunc< o_fn >( this, 37 ) ( this, vguiPanel );
		}
	};

}
