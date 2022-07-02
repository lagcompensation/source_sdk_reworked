#include <Windows.h>
#include <string>
#include "interfaces.hpp"
#include "..\..\utils\utils.hpp"

namespace i_manager
{
	/* credits: gladiatorcheatz */
	class interface_reg
	{
	private:

		using InstantiateInterfaceFn = void* ( * )( );

	public:

		InstantiateInterfaceFn create_fn;
		const char* name;

		interface_reg* next;
	};

	template<typename T>
	static T* get_interface( const char* modName, const char* ifaceName, bool exact = false )
	{
		T* i_interface = nullptr;
		interface_reg* interface_reg_list;
		int partMatchLen = strlen( ifaceName );

		DWORD interface_fn = reinterpret_cast< DWORD >( GetProcAddress( GetModuleHandleA( modName ), _( "CreateInterface" ) ) );

		if ( !interface_fn )
			return nullptr;

		unsigned int jmp_start = ( unsigned int ) ( interface_fn ) +4;
		unsigned int jmp_target = jmp_start + *( unsigned int* ) ( jmp_start + 1 ) + 5;

		interface_reg_list = **reinterpret_cast< interface_reg * ** >( jmp_target + 6 );

		for ( interface_reg* cur = interface_reg_list; cur; cur = cur->next )
		{
			if ( exact == true )
			{
				if ( strcmp( cur->name, ifaceName ) == 0 )
					i_interface = reinterpret_cast< T* >( cur->create_fn( ) );
			}
			else
			{
				if ( !strncmp( cur->name, ifaceName, partMatchLen ) && std::atoi( cur->name + partMatchLen ) > 0 )
					i_interface = reinterpret_cast< T* >( cur->create_fn( ) );
			}
		}
		return i_interface;
	}

}

namespace csgo
{
	interfaces_manager interfaces;

	namespace i
	{
		c_clientdll* clientdll;
		c_clientmode* clientmode;
		c_cvar* cvar;
		c_engine* engine;
		c_engine_trace* engine_trace;
		c_entitylist* entitylist;
		c_globalvars* globalvars;
		c_input* input;
		c_input_system* input_system;
		DWORD* input_internal;
		c_material_system* material_system;
		c_model_info* model_info;
		c_model_render* model_render;
		c_move_helper* move_helper;
		c_movement* movement;
		c_panel* panel;
		c_prediction* prediction;
		i_surface* surface;
		c_clientstate* clientstate;
		IDirect3DDevice9* dev;
	};

	void interfaces_manager::init( ) {
		/* initialize interfaces */
		i::clientdll = i_manager::get_interface<csgo::c_clientdll>( _( "client.dll" ), _( "VClient018" ), true );
		i::clientmode = *( csgo::c_clientmode * * ) ( c_utils.pattern_scan( GetModuleHandleA( _( "client.dll" ) ), _( "B9 ? ? ? ? E8 ? ? ? ? 84 C0 0F 85 ? ? ? ? 53" ) ) + 1 );
		i::clientmode = *( csgo::c_clientmode** )( ( *( DWORD** )( i::clientdll ) )[ 10 ] + 0x5 );
		i::cvar = i_manager::get_interface<csgo::c_cvar>( _( "vstdlib.dll" ), _( "VEngineCvar007" ), true );
		i::engine = i_manager::get_interface<csgo::c_engine>( _( "engine.dll" ), _( "VEngineClient014" ), true );
		i::engine_trace = i_manager::get_interface<csgo::c_engine_trace>( _( "engine.dll" ), _( "EngineTraceClient004" ), true );
		i::entitylist = i_manager::get_interface<csgo::c_entitylist>( _( "client.dll" ), _( "VClientEntityList003" ), true );
		i::globalvars = **( csgo::c_globalvars * ** ) ( ( *( DWORD * * ) i::clientdll )[ 0 ] + 0x1F );
		i::input = *( csgo::c_input * * ) ( c_utils.pattern_scan( GetModuleHandleA( _( "client.dll" ) ), _( "B9 ? ? ? ? F3 0F 11 04 24 FF 50 10" ) ) + 1 );
		i::input_system = i_manager::get_interface<csgo::c_input_system>( _( "inputsystem.dll" ), _( "InputSystemVersion001" ), true );
		i::input_internal = i_manager::get_interface<DWORD>( _( "vgui2.dll" ), _( "VGUI_InputInternal" ), false );
		i::material_system = i_manager::get_interface<csgo::c_material_system>( _( "materialsystem.dll" ), _( "VMaterialSystem080" ), true );
		i::model_info = i_manager::get_interface<csgo::c_model_info>( _( "engine.dll" ), _( "VModelInfoClient004" ), true );
		i::model_render = i_manager::get_interface<csgo::c_model_render>( _( "engine.dll" ), _( "VEngineModel016" ), true );
		i::move_helper = **( c_move_helper * ** ) ( c_utils.pattern_scan( GetModuleHandleA( _( "client.dll" ) ), _( "8B 0D ?? ?? ?? ?? 8B 46 08 68" ) ) + 2 );
		i::movement = i_manager::get_interface< csgo::c_movement >( _( "client.dll" ), _( "GameMovement001" ), true );
		i::panel = i_manager::get_interface< csgo::c_panel >( _( "vgui2.dll" ), _( "VGUI_Panel009" ), true );
		i::prediction = i_manager::get_interface< csgo::c_prediction >( _( "client.dll" ), _( "VClientPrediction001" ), true );
		i::surface = i_manager::get_interface<csgo::i_surface>( _( "vguimatsurface.dll" ), _( "VGUI_Surface031" ), true );

		i::clientstate = **( csgo::c_clientstate * ** ) ( c_utils.pattern_scan( GetModuleHandleA( _( "engine.dll" ) ), _( "A1 ? ? ? ? 8B 80 ? ? ? ? C3" ) ) + 1 );
		i::dev = **( IDirect3DDevice9 * ** ) ( c_utils.pattern_scan( GetModuleHandleA( _( "shaderapidx9.dll" ) ), _( "A1 ? ? ? ? 50 8B 08 FF 51 0C" ) ) + 1 );
	}

};
