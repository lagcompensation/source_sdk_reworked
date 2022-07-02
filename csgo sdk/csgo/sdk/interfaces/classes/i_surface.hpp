#pragma once
#include "..\..\..\utils\vfunc.hpp"

namespace csgo {
	class i_surface {
	public:
		void unlock_cursor( void ) {
			using unlockcusor_fn = void( __thiscall* )( void* );
			csgo::get_vfunc< unlockcusor_fn >( this, 66 )( this );
		}

		void lock_cursor( void ) {
			using lockcusor_fn = void( __thiscall* )( void* );
			csgo::get_vfunc< lockcusor_fn >( this, 67 )( this );
		}

		void get_cursor_pos( int& x, int& y ) {
			using get_cursor_pos_fn = void( __thiscall* )( void*, int&, int& );
			csgo::get_vfunc< get_cursor_pos_fn >( this, 100 )( this, x, y );
		}
	};
}