#pragma once
#include <cstdint>
#include "..\..\..\utils\vfunc.hpp"
#include "c_globalvars.hpp"

namespace csgo
{

	enum framestage_t : int
	{
		frame_undefined = -1,
		frame_start, // 0
		frame_net_update_start, // 1
		frame_net_update_postdataupdate_start, // 2
		frame_net_update_postdataupdate_end, // 3
		frame_net_update_end, // 4
		frame_render_start, // 5
		frame_render_end // 6
	};

	struct recv_table_t;
	struct recv_prop_t;

	struct recv_table_t {
		recv_prop_t* m_props;
		int m_num_props;
		void* m_decoder;
		char* m_net_table_name;
		std::uint8_t pad[ 0x2 ];
	};

	struct recv_prop_t {
		char* m_var_name;
		int m_recv_type;
		int m_flags;
		int m_string_buffer_size;
		bool m_inside_array;
		const void* m_extra_data;
		recv_prop_t* m_array_prop;
		void* m_array_length_proxy;
		void* m_proxy_fn;
		void* m_data_table_proxy_fn;
		recv_table_t* m_data_table;
		int m_offset;
		int m_element_stride;
		int m_num_elements;
		const char* m_parent_array_prop_name;
	};

	using create_client_class_t = void* ( * )( int ent_num, int serial_num );
	using create_event_t = void* ( * )( );

	class client_class_t {
	public:
		create_client_class_t m_create_fn;
		create_event_t m_create_event_fn;
		char* m_network_name;
		recv_table_t* m_recv_table;
		client_class_t* m_next;
		int m_class_id;
	};

	class c_clientdll
	{
	protected:
		~c_clientdll( ) = default;
	public:
		virtual int connect( void* factory, c_globalvars* globals ) = 0;
		virtual int disconnect( ) = 0;
		virtual int init( void* factory, c_globalvars* globals ) = 0;
		virtual void post_init( ) = 0;
		virtual void shutdown( ) = 0;
		virtual void level_init_pre_entity( char const* map_name ) = 0;
		virtual void level_init_post_entity( ) = 0;
		virtual void level_shutdown( ) = 0;
		virtual client_class_t* get_all_classes( ) = 0;
	};


}