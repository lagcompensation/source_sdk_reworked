#include "../hooks.hpp"
#include "../../features/features.hpp"
#include "../../includes.hpp"
#include "../../sdk/includes.hpp"

/* include imgui */
#include "../../menu/imgui/imgui.h"
#include "../../menu/imgui/imgui_internal.h"
#include "../../menu/imgui/impl/imgui_impl_dx9.h"
#include "../../menu/imgui/impl/imgui_impl_win32.h"

/* wnd proc */
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
long __stdcall hooks::wnd_proc( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	/* open menu */ {
		static bool m_pressed = false;
		const bool m_held = GetAsyncKeyState( VK_INSERT );
		if ( m_pressed != m_held ) {

			if ( m_held ) {
				menu.opened = !menu.opened;
			}

			m_pressed = m_held;
		}
	}

	/* our wndproc capture fn */
	if ( menu.d3d_init && menu.opened && ImGui_ImplWin32_WndProcHandler( hwnd, msg, wparam, lparam ) && !menu.input_should_listen )
		return true;

	/* call original wnd_proc to make game use input again */
	return CallWindowProcA( ( WNDPROC )c_hooks.original_wndproc, hwnd, msg, wparam, lparam );

}

/* directx */
long __stdcall hooks::end_scene( IDirect3DDevice9* device )
{
	static auto o_endscene = c_hooks.directx_hook.get_original< hooks::end_scene_fn >( c_hooks.vtable_indexes.end_scene );

	/* end_scene gets called twice by csgo so we call it once */
	static auto ret = _ReturnAddress( );
	if ( ret != _ReturnAddress( ) ) {
		return o_endscene( device );
	}

	/* initialize imgui style */
	if ( !menu.d3d_init ) {


		/* we already initialized, stop now  */
		menu.d3d_init = true;
	}

	/* backup render states */
	IDirect3DStateBlock9* stateBlock = nullptr;
	IDirect3DVertexDeclaration9* vertDec = nullptr;
	device->GetVertexDeclaration( &vertDec );
	device->CreateStateBlock( D3DSBT_PIXELSTATE, &stateBlock );

	/* begin imgui */
	ImGui_ImplDX9_NewFrame( );
	ImGui_ImplWin32_NewFrame( );
	ImGui::NewFrame( );

	/* draw our menu */


	/* end imgui */
	ImGui::Render( );
	ImGui::EndFrame( );
	ImGui_ImplDX9_RenderDrawData( ImGui::GetDrawData( ) );

	/* restore these */
	stateBlock->Apply( );
	stateBlock->Release( );
	device->SetVertexDeclaration( vertDec );

	return o_endscene( device );
}

long __stdcall hooks::reset( IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* presentation_parameters )
{
	static auto o_reset = c_hooks.directx_hook.get_original< hooks::reset_fn >( c_hooks.vtable_indexes.reset );

	/* destroy fonts */
	csgo::c_utils.destroy_fonts( );

	if ( !menu.d3d_init )
		return o_reset( device, presentation_parameters );

	ImGui_ImplDX9_InvalidateDeviceObjects( );

	auto hr = o_reset( device, presentation_parameters );

	if ( SUCCEEDED( hr ) ) {
		ImGui_ImplDX9_CreateDeviceObjects( );

		csgo::c_utils.create_fonts( );
	}

	return hr;
}
