#pragma once
#include "..\..\vec3.hpp"

namespace csgo {

	class c_base_entity;
	class c_movedata;

	class c_movement {
	public:
	public:
		virtual ~c_movement( void ) = 0;
		virtual void process_movement( c_base_entity* player, c_movedata* move_data ) = 0;
		virtual void reset( void ) = 0;
		virtual void start_track_prediction_errors( c_base_entity* player ) = 0;
		virtual void finish_track_prediction_errors( c_base_entity* player ) = 0;
		virtual void diff_print( char const* fmt, ... ) = 0;
		virtual vec3_t const& get_player_mins( bool ducked ) const = 0;
		virtual vec3_t const& get_player_maxs( bool ducked ) const = 0;
		virtual vec3_t const& get_player_view_offset( bool ducked ) const = 0;
		virtual bool is_moving_player_stuck( void ) const = 0;
		virtual void* get_moving_player( void ) const = 0;
		virtual void unblock_pusher( c_base_entity* player, c_base_entity* pusher ) = 0;
		virtual void setup_movement_bounds( c_movedata* move_data ) = 0;
	};

}
