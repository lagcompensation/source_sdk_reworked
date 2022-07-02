#pragma once
#include "..\includes.hpp"
#include "..\sdk\datamap.hpp"

namespace csgo
{
	class utils
	{
	public:
		void destroy_fonts( );
		void create_fonts( );
		std::uintptr_t pattern_scan( void* module, const char* signature );
		std::uint8_t* pattern_scan_c( void* module, const char* signature );
		DWORD pattern_scan_byte( void* module, BYTE* mask, char* szMask );
		unsigned int find_in_data_map( csgo::datamap_t* m_map, const char* name );
		bool world_to_screen( const vec3_t& origin, vec3_t& screen );
	};
	extern utils c_utils;
};