#pragma once
#include "..\..\vec3.hpp"
#include "c_panel.hpp"

namespace csgo {
	class c_base_entity;

	class c_view_setup
	{
	public:
		__int32 x; // 0x0000
		__int32 x_old; // 0x0004
		__int32 y; // 0x0008
		__int32 y_old; // 0x000C
		__int32 width; // 0x0010
		__int32 width_old; // 0x0014
		__int32 height; // 0x0018
		__int32 height_old; // 0x001C
		char pad_0x0020[ 0x90 ]; // 0x0020
		float fov; // 0x00B0
		float viewmodel_fov; // 0x00B4
		vec3_t origin; // 0x00B8
		vec3_t angles; // 0x00C4
		char pad_0x00D0[ 0x7C ]; // 0x00D0
	}; // size=0x014C

	class c_clientmode
	{
	public:
		virtual ~c_clientmode( )
		{
		}

		virtual int client_mode_cs_normal( void* ) = 0;
		virtual void init( ) = 0;
		virtual void init_viewport( ) = 0;
		virtual void shutdown( ) = 0;
		virtual void enable( ) = 0;
		virtual void disable( ) = 0;
		virtual void layout( ) = 0;
		virtual c_panel* get_viewport( ) = 0;
		virtual void* get_viewport_animatio_ncontroller( ) = 0;
		virtual void process_input( bool bactive ) = 0;
		virtual bool should_draw_detail_objects( ) = 0;
		virtual bool should_draw_entity( c_base_entity* entity ) = 0;
		virtual bool should_draw_local_player( c_base_entity* player ) = 0;
		virtual bool should_draw_particles( ) = 0;
		virtual bool should_draw_fog( void ) = 0;
		virtual void override_view( c_view_setup* setup ) = 0;
		virtual int key_input( int down, int key, const char* current_Binding ) = 0;
		virtual void start_message_mode( int type ) = 0;
		virtual c_panel* get_message_panel( ) = 0;
		virtual void override_mouse_input( float* x, float* y ) = 0;
		virtual bool create_move( float input_sample_time, void* usercmd ) = 0;
		virtual void level_init( const char* new_map ) = 0;
		virtual void level_shutdown( void ) = 0;
	};

}
