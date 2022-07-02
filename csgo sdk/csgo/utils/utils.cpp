#include "utils.hpp"
#include <iostream>
#include <Psapi.h>
#pragma comment(lib, "psapi.lib")

#define INRANGE(x,a,b)   (x >= a && x <= b)
#define GET_BYTE( x )    (GET_BITS(x[0]) << 4 | GET_BITS(x[1]))
#define GET_BITS( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))

namespace csgo
{
	utils c_utils;

	void utils::destroy_fonts( ) {
		csgo::render::fonts::def->Release( );
		csgo::render::fonts::watermark->Release( );
		csgo::render::fonts::esp_def->Release( );
		csgo::render::fonts::esp_sec->Release( );
	}

	void utils::create_fonts( ) {
		csgo::render::create_font( ( void** ) & csgo::render::fonts::def, "Tahoma", 32, true );
		csgo::render::create_font( ( void** ) & csgo::render::fonts::watermark, "Tahoma", 16, false );
		csgo::render::create_font( ( void** ) & csgo::render::fonts::esp_def, "Tahoma", 12, FW_NORMAL );
		csgo::render::create_font( ( void** ) & csgo::render::fonts::esp_sec, "Arial", 14, false );
	}

	std::uintptr_t utils::pattern_scan( void* module, const char* signature )
	{
		/* antario? */
		const char* pat = signature;
		DWORD first_match = 0;
		DWORD range_start = reinterpret_cast< DWORD >( module );
		MODULEINFO module_info;
		GetModuleInformation( GetCurrentProcess( ), reinterpret_cast< HMODULE >( range_start ), &module_info, sizeof( MODULEINFO ) );
		DWORD range_end = range_start + module_info.SizeOfImage;
		for ( DWORD pCur = range_start; pCur < range_end; pCur++ )
		{
			if ( !*pat )
				return first_match;

			if ( *( PBYTE ) pat == '\?' || *( BYTE* ) pCur == GET_BYTE( pat ) )
			{
				if ( !first_match )
					first_match = pCur;

				if ( !pat[ 2 ] )
					return first_match;

				if ( *( PWORD ) pat == '\?\?' || *( PBYTE ) pat != '\?' )
					pat += 3;

				else
					pat += 2;
			}
			else
			{
				pat = signature;
				first_match = 0;
			}
		}
		return NULL;
	}

	std::uint8_t* utils::pattern_scan_c( void* module, const char* signature )
	{
		static auto pattern_to_byte = [ ] ( const char* pattern ) {
			auto bytes = std::vector<int>{};
			auto start = const_cast< char* >( pattern );
			auto end = const_cast< char* >( pattern ) + strlen( pattern );

			for ( auto current = start; current < end; ++current ) {
				if ( *current == '?' ) {
					++current;
					if ( *current == '?' )
						++current;
					bytes.push_back( -1 );
				}
				else {
					bytes.push_back( strtoul( current, &current, 16 ) );
				}
			}
			return bytes;
		};

		auto dos_header = ( PIMAGE_DOS_HEADER ) module;
		auto nt_headers = ( PIMAGE_NT_HEADERS ) ( ( std::uint8_t* )module + dos_header->e_lfanew );

		auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
		auto pattern_bytes = pattern_to_byte( signature );
		auto scan_bytes = reinterpret_cast< std::uint8_t* >( module );

		auto s = pattern_bytes.size( );
		auto d = pattern_bytes.data( );

		for ( auto i = 0ul; i < size_of_image - s; ++i ) {
			bool found = true;
			for ( auto j = 0ul; j < s; ++j ) {
				if ( scan_bytes[ i + j ] != d[ j ] && d[ j ] != -1 ) {
					found = false;
					break;
				}
			}
			if ( found ) {
				return &scan_bytes[ i ];
			}
		}
		return nullptr;
	}

	DWORD utils::pattern_scan_byte( void* module, BYTE* mask, char* szMask )
	{
		auto wait_on_module_handle = [ ] ( void* m_module ) -> DWORD {
			DWORD module_handle = NULL;
			while ( !module_handle )
			{
				module_handle = ( DWORD ) m_module;
				if ( !module_handle )
					Sleep( 50 );
			}
			return module_handle;
		};

		auto compare = [ ] ( const BYTE* data, const BYTE* mask, const char* szMask ) -> bool {
			for ( ; *szMask; ++szMask, ++mask, ++data )
			{
				if ( *szMask == 'x' && *mask != *data )
				{
					return false;
				}
			}
			return ( *szMask ) == 0;
		};

		DWORD address = wait_on_module_handle( module );
		MODULEINFO module_info; GetModuleInformation( GetCurrentProcess( ), ( HMODULE ) address, &module_info, sizeof( MODULEINFO ) );
		DWORD length = module_info.SizeOfImage;
		for ( DWORD c = 0; c < length; c += 1 )
		{
			if ( compare( ( BYTE* ) ( address + c ), mask, szMask ) )
			{
				return ( DWORD ) ( address + c );
			}
		}

		std::cout << "failed to scan pattern" << std::endl;
		return 0;

	}

	unsigned int utils::find_in_data_map( csgo::datamap_t* m_map, const char* name )
	{
		while ( m_map )
		{
			for ( int i = 0; i < m_map->data_fields; i++ )
			{
				if ( m_map->data_description[ i ].field_name == NULL )
					continue;

				if ( strcmp( name, m_map->data_description[ i ].field_name ) == 0 )
					return m_map->data_description[ i ].field_offset[ 0 ];

				if ( m_map->data_description[ i ].field_type == 10 )
				{
					if ( m_map->data_description[ i ].td )
					{
						unsigned int offset;

						if ( ( offset = find_in_data_map( m_map->data_description[ i ].td, name ) ) != 0 )
							return offset;
					}
				}
			}
			m_map = m_map->base_map;
		}

		return 0;
	}

	bool utils::world_to_screen( const vec3_t& origin, vec3_t& screen )
	{
		const auto screen_transform = [ &origin, &screen ] ( ) -> bool
		{
			static std::uintptr_t view_matrix;
			if ( !view_matrix )
			{
				view_matrix = static_cast< std::uintptr_t >( c_utils.pattern_scan( GetModuleHandleA( "client.dll" ), "0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9" ) );
				view_matrix += 3;
				view_matrix = *reinterpret_cast< std::uintptr_t* >( view_matrix );
				view_matrix += 176;
			}

			const matrix3x4_t& w2s_matrix = *reinterpret_cast< matrix3x4_t* >( view_matrix );
			screen.x = w2s_matrix.m_values[ 0 ][ 0 ] * origin.x + w2s_matrix.m_values[ 0 ][ 1 ] * origin.y + w2s_matrix.m_values[ 0 ][ 2 ] * origin.z + w2s_matrix.m_values[ 0 ][ 3 ];
			screen.y = w2s_matrix.m_values[ 1 ][ 0 ] * origin.x + w2s_matrix.m_values[ 1 ][ 1 ] * origin.y + w2s_matrix.m_values[ 1 ][ 2 ] * origin.z + w2s_matrix.m_values[ 1 ][ 3 ];

			float w = w2s_matrix.m_values[ 3 ][ 0 ] * origin.x + w2s_matrix.m_values[ 3 ][ 1 ] * origin.y + w2s_matrix.m_values[ 3 ][ 2 ] * origin.z + w2s_matrix.m_values[ 3 ][ 3 ];

			if ( w < 0.001f )
			{
				screen.x *= 100000;
				screen.y *= 100000;
				return true;
			}

			float invw = 1.f / w;
			screen.x *= invw;
			screen.y *= invw;

			return false;
		};

		if ( !screen_transform( ) )
		{
			int screen_width, screen_height;
			csgo::i::engine->get_screen_size( screen_width, screen_height );

			screen.x = ( screen_width * 0.5f ) + ( screen.x * screen_width ) * 0.5f;
			screen.y = ( screen_height * 0.5f ) - ( screen.y * screen_height ) * 0.5f;

			return true;
		}

		return false;
	}

};
