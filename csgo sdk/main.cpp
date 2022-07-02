#include "csgo/includes.hpp"

void init_chams_mat( ) {
	/// DEFAULT
	{
		std::ofstream( "csgo/materials/material_default.vmt" ) << (
			R"#("VertexLitGeneric"
{
  "$basetexture" "vgui/white_additive"
  "$ignorez"      "0"
  "$nofog"        "1"
  "$model"        "1"
  "$nocull"       "0"
  "$selfillum"    "1"
  "$halflambert"  "1"
  "$znearer"      "0"
  "$flat"         "1"
  "$envmap"       ""
}
)#" );
		std::ofstream( "csgo/materials/material_default_xyz.vmt" ) << (
			R"#("VertexLitGeneric"
{
  "$basetexture" "vgui/white_additive"
  "$ignorez"      "1"
  "$nofog"        "1"
  "$model"        "1"
  "$nocull"       "0"
  "$selfillum"    "1"
  "$halflambert"  "1"
  "$znearer"      "0"
  "$flat"         "1"
  "$envmap"       ""
}
)#" );
	}

	/// FLAT
	{
		std::ofstream( "csgo/materials/material_flat.vmt" ) << (
			R"#("UnlitGeneric"
{
  "$basetexture" "vgui/white_additive"
  "$ignorez"      "0"
  "$nofog"        "1"
  "$model"        "1"
  "$nocull"       "0"
  "$selfillum"    "1"
  "$halflambert"  "1"
  "$znearer"      "0"
  "$flat"         "1"
  "$envmap"       ""
}
)#" );
		std::ofstream( "csgo/materials/material_flat_xyz.vmt" ) << (
			R"#("UnlitGeneric"
{
  "$basetexture" "vgui/white_additive"
  "$ignorez"      "1"
  "$nofog"        "1"
  "$model"        "1"
  "$nocull"       "0"
  "$selfillum"    "1"
  "$halflambert"  "1"
  "$znearer"      "0"
  "$flat"         "1"
  "$envmap"       ""
}
)#" );
	}

	/// METALLIC
	{
		std::ofstream( "csgo/materials/material_metallic.vmt" ) << (
			R"#("VertexLitGeneric"
{
  "$basetexture" "vgui/white_additive"
  "$ignorez"      "0"
  "$envmap"       "env_cubemap"
  "$normalmapalphaenvmapmask" "1"
  "$envmapcontrast"  "1"
  "$nofog"        "1"
  "$model"        "1"
  "$nocull"       "0"
  "$selfillum"    "1"
  "$halflambert"  "1"
  "$znearer"      "0"
  "$flat"         "1"
}
)#" );
		std::ofstream( "csgo/materials/material_metallic_xyz.vmt" ) << (
			R"#("VertexLitGeneric"
{
  "$basetexture" "vgui/white_additive"
  "$ignorez"      "1"
  "$envmap"       "env_cubemap"
  "$normalmapalphaenvmapmask" "1"
  "$envmapcontrast"  "1"
  "$nofog"        "1"
  "$model"        "1"
  "$nocull"       "0"
  "$selfillum"    "1"
  "$halflambert"  "1"
  "$znearer"      "0"
  "$flat"         "1"
}
)#" );

	}

	/// REFLECTIVE
	{
		std::ofstream( "csgo/materials/material_reflective.vmt" ) << R"#("UnlitGeneric"
{

  "$basetexture" "vgui/white_additive"
  "$no_fullbright" "0"
  "$ignorez"      "0"
  "$envmap"       "env_cubemap"
  "$nofog"        "1"
  "$model"        "1"
  "$nocull"       "0"
  "$selfillum"    "1"
  "$halflambert"  "1"
  "$znearer"      "0"
  "$flat"         "1"
}
)#";

		std::ofstream( "csgo/materials/material_reflective_xyz.vmt" ) << R"#("UnlitGeneric"
{

  "$basetexture" "vgui/white_additive"
  "$no_fullbright" "0"
  "$ignorez"      "1"
  "$envmap"       "env_cubemap"
  "$nofog"        "1"
  "$model"        "1"
  "$nocull"       "0"
  "$selfillum"    "1"
  "$halflambert"  "1"
  "$znearer"      "0"
  "$flat"         "1"
}
)#";
	}

	/// GLOW
	{
		std::ofstream( "csgo/materials/material_glow.vmt" ) << R"#("VertexLitGeneric" {

"$additive" "1"
"$envmap" "models/effects/cube_white"
"$envmaptint" "[1 0 1]"
"$envmapfresnel" "1"
"$envmapfresnelminmaxexp" "[0 1 5]"
"$alpha" "1"
})#";
	}
	// $envmapfresnelminmaxexp was default vec3_t( 0, 1, 2 ) on material_glow
}

void csgo_init( HMODULE mod ) {

	/* wait for all modules to load */
	while ( !GetModuleHandleA( "serverbrowser.dll" ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );

	/* initialize csgo hack */
	csgo::interfaces.init( );
	csgo::netvars::init( );
	c_hooks.init( );

	/* wait for unload key */
	while ( !GetAsyncKeyState( VK_END ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );

	/* unload */
	c_hooks.restore( );

	FreeLibraryAndExitThread( mod, 0 );

}

BOOL WINAPI DllMain( HINSTANCE instance, DWORD reason, LPVOID reserved ) {
	/* attach hack dll */
	if ( reason == DLL_PROCESS_ATTACH )
		CreateThread( nullptr, 0, LPTHREAD_START_ROUTINE( csgo_init ), HMODULE( instance ), 0, nullptr );

	return TRUE;
}
