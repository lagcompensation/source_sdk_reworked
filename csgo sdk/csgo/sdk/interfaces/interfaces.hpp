#pragma once
#include <d3d9.h>

/* include classes */
#include "classes\c_clientdll.hpp"
#include "classes\c_clientmode.hpp"
#include "classes\c_cvar.hpp"
#include "classes\c_engine.hpp"
#include "classes\c_engine_trace.hpp"
#include "classes\c_entitylist.hpp"
#include "classes\c_globalvars.hpp"
#include "classes\c_input.hpp"
#include "classes\c_input_system.hpp"
#include "classes\c_material_system.h"
#include "classes\c_model_info.hpp"
#include "classes\c_model_render.hpp"
#include "classes\c_move_helper.hpp"
#include "classes\c_movement.hpp"
#include "classes\c_panel.hpp"
#include "classes\c_prediction.hpp"
#include "classes\i_surface.hpp"

namespace csgo
{
	namespace i
	{
		extern c_clientdll* clientdll;
		extern c_clientmode* clientmode;
		extern c_cvar* cvar;
		extern c_engine* engine;
		extern c_engine_trace* engine_trace;
		extern c_entitylist* entitylist;
		extern c_globalvars* globalvars;
		extern c_input* input;
		extern c_input_system* input_system;
		extern DWORD* input_internal;
		extern c_material_system* material_system;
		extern c_model_info* model_info;
		extern c_model_render* model_render;
		extern c_move_helper* move_helper;
		extern c_movement* movement;
		extern c_panel* panel;
		extern c_prediction* prediction;
		extern i_surface* surface;
		extern c_clientstate* clientstate;
		extern IDirect3DDevice9* dev;
	};

	class interfaces_manager
	{
	public:
		void init( );
	};
	extern interfaces_manager interfaces;
}
