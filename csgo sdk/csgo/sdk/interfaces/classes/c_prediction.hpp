#pragma once
#include "..\..\..\utils\vfunc.hpp"
#include "..\..\vec3.hpp"

namespace csgo {

	class c_base_entity;
	class c_base_player;
	class c_usercmd;

	class c_move_helper;

	class c_movedata
	{
	public:
		bool m_first_run_of_functions : 1;
		bool m_game_code_moved_player : 1;
		int m_player_handle;
		int m_impulse_command;
		vec3_t m_view_angles;
		vec3_t m_abs_view_angles;
		int m_buttons;
		int m_old_buttons;
		float m_forward_move;
		float m_side_move;
		float m_up_move;
		float m_max_speed;
		float m_client_max_speed;
		vec3_t m_velocity;
		vec3_t m_angles;
		vec3_t m_old_angles;
		float m_out_step_height;
		vec3_t m_out_wish_vel;
		vec3_t m_out_jump_vel;
		vec3_t m_constraint_center;
		float m_constraint_radius;
		float m_constraint_width;
		float m_constraint_speed_factor;
		float m_flunknown[ 5 ];
		vec3_t m_abs_origin;
	};

	class c_prediction {
	public:

		void get_local_viewangles( vec3_t& angle ) {
			using fn = void( __thiscall* )( void*, vec3_t& );
			get_vfunc< fn >( this, 12 )( this, angle );
		}

		void set_local_viewangles( vec3_t& angle ) {
			using fn = void( __thiscall* )( void*, vec3_t& );
			get_vfunc< fn >( this, 13 )( this, angle );
		}

		void update( int start_frame, bool valid_frame, int inc_ack, int out_cmd ) {
			using fn = void( __thiscall* )( void*, int, bool, int, int );
			get_vfunc< fn >( this, 3 )( this, start_frame, valid_frame, inc_ack, out_cmd );
		}

		void check_moving_ground( c_base_player* player, double frametime ) {
			using fn = void( __thiscall* )( void*, c_base_player*, double );
			get_vfunc< fn >( this, 18 )( this, player, frametime );
		}

		void setup_move( c_base_player* player, c_usercmd* ucmd, c_move_helper* helper, void* movedata ) {
			using fn = void( __thiscall* )( void*, c_base_player*, c_usercmd*, c_move_helper*, void* );
			get_vfunc< fn >( this, 20 )( this, player, ucmd, helper, movedata );
		}

		void finish_move( c_base_player* player, c_usercmd* ucmd, void* movedata ) {
			using fn = void( __thiscall* )( void*, c_base_player*, c_usercmd*, void* );
			get_vfunc< fn >( this, 21 )( this, player, ucmd, movedata );
		}

		uint8_t pad_0x1[ 0x8 ];
		bool m_in_prediction;
		uint8_t pad_0x2[ 0x1 ];
		bool m_engine_paused;
		uint8_t pad_0x3[ 13 ];
		bool m_is_first_time_predicted;

	};

}
