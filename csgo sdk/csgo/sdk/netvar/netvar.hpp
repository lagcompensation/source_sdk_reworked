#pragma once
#include <map>
#include <string>
#include <unordered_map>


namespace csgo
{
	struct recv_table_t;
	struct recv_prop_t;
	namespace netvars {
		struct netvar_data_t {
			bool m_datamap_var; // we can't do proxies on stuff from datamaps :).
			recv_prop_t* m_prop_ptr;
			std::size_t m_offset;

			netvar_data_t( ) : m_datamap_var{ }, m_prop_ptr{ }, m_offset{ } { }
		};

		extern std::unordered_map< std::string, int > m_client_ids;
		extern std::unordered_map< std::string, std::unordered_map< std::string, netvar_data_t > > m_offsets;

		bool init( );
		void store_table( const std::string& name, recv_table_t* table, std::size_t offset = 0 );
		int get_client_id( const std::string& network_name );
		int get( const std::string& table, const std::string& prop );
		int get_offset( const char* name );
	}
}


#define NETVAR( type, func, name ) \
type& func( ) { \
	static auto offset = netvars::get_offset( name ); \
	return *( type* ) ( uintptr_t( this ) + offset ); \
}

#define NETVAR_OFFSET( type, func, name, off ) \
type& func( ) { \
	static auto offset = netvars::get_offset( name ); \
	return *( type* ) ( uintptr_t( this ) + offset + off ); \
}

#define OFFSET( type, name, offset ) \
type& name##( ) { \
	return *( type* ) ( uintptr_t( this ) + offset ); \
}

#define POFFSET( type, name, offset ) \
type* name##( ) { \
	return ( t ) ( uintptr_t( this ) + offset ); \
}

