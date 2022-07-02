#pragma once
#include "../utils/vfunc_hook/vfunc_hook.hpp"

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

/* pre-define sdk classes/structs/etc. */
class vec3_t;
class matrix3x4_t;
namespace csgo {
	class c_view_setup;
	struct draw_model_state_t;
	struct model_render_info_t;
};

class hooks
{
public:
	void init( );
	void restore( );
public:
	/* virtual table indexes */
	struct vtable_indexes
	{
		const int create_move = 22;
		const int frame_stage_notify = 37;
		const int override_view = 18;
		const int end_scene = 42;
		const int reset = 16;
		const int lock_cursor = 67;
		const int draw_model_exec = 21;
		const int set_key_code_state = 91;
		const int set_mouse_code_state = 92;
		const int list_leaves_in_box = 6;
		const int update_client_side_animation = 223;
		const int do_extra_bones_processing = 197;
		const int setup_bones = 13;
	}vtable_indexes;

public:
	/* original functions */
	typedef void( __fastcall* create_move_fn )( void*, int, int, float, bool );
	typedef void( __fastcall* frame_stage_notify_fn ) ( void*, void*, int );
	typedef void( __fastcall* override_view_fn ) ( void*, int, csgo::c_view_setup* );
	typedef long( __stdcall* end_scene_fn )( IDirect3DDevice9* );
	typedef long( __stdcall* reset_fn )( IDirect3DDevice9*, D3DPRESENT_PARAMETERS* );
	typedef void( __fastcall* lock_cursor_fn ) ( void* );
	typedef void( __fastcall* draw_model_exec_fn )( void*, int, void*, const csgo::draw_model_state_t&, const csgo::model_render_info_t&, matrix3x4_t* );
	typedef void( __thiscall* set_key_code_state_fn ) ( void*, int, bool );
	typedef void( __thiscall* set_mouse_code_state_fn ) ( void*, int, int );
	typedef int( __thiscall* list_leaves_in_box_fn )( void*, const vec3_t&, const vec3_t&, unsigned short*, int );
	typedef void( __thiscall* update_client_side_animation_fn ) ( void* );
	typedef void( __thiscall* do_extra_bones_processing_fn ) ( void*, void*, int, int, int, int, int, int );
	typedef bool( __thiscall* setup_bones_fn )( void*, void*, matrix3x4_t*, int, int, float );

private:
	/* hook functions */
	static void __stdcall create_move( int sequence_number, float input_sample_frametime, bool active, bool& send_packet );
	static void __fastcall create_move_hook( void* _this, int, int sequence_number, float input_sample_frametime, bool active );
	static void __fastcall frame_stage_notify( void* ecx, void* edx, int stage );
	static void __fastcall override_view( void* _this, int edx, csgo::c_view_setup* view );
	static long __stdcall wnd_proc( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam );
	static long __stdcall end_scene( IDirect3DDevice9* device );
	static long __stdcall reset( IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* presentation_parameters );
	static void __fastcall lock_cursor( void* ecx, void* edx );
	static void __fastcall draw_model_exec( void* _this, int edx, void* ctx, const csgo::draw_model_state_t& state, const csgo::model_render_info_t& info, matrix3x4_t* custom_bone_to_world = nullptr );
	static void __fastcall set_key_code_state( void* _this, void* edx, int code, bool down );
	static void __fastcall set_mouse_code_state( void* _this, void* edx, int code, int state );
	static int __fastcall list_leaves_in_box( void* bsp, void* edx, vec3_t& mins, vec3_t& maxs, unsigned short* list, int list_max );
	static void __fastcall update_client_side_animation( void* ecx );
	static void __fastcall do_extra_bones_processing( void* ecx, void* edx, int a2, int a3, int a4, int a5, int a6, int a7 );
	static bool __fastcall setup_bones( void* ecx, void* edx, matrix3x4_t* bone_to_world_out, int max_bones, int bone_mask, float curtime );
	static void hook_players( );
	static void unhook_players( );
public:
	/* vfunction hooks */
	vfunc_hook clientdll_hook;
	vfunc_hook clientmode_hook;
	vfunc_hook directx_hook;
	vfunc_hook surface_hook;
	vfunc_hook mdlrender_hook;
	vfunc_hook inputinternal_hook;
	vfunc_hook bsptreequery_hook;
	vfunc_hook players_hook;

public:
	/* public vars */
	HWND csgo_window = nullptr;
	long original_wndproc;

private:
	/* private vars */
	bool hooked_players[ 65 ];

};
extern hooks c_hooks;
