#pragma once
#include "..\includes.hpp"

#include <d3d9.h>
#include <d3dx9.h>

struct ImFont;

class ui
{
public:
	void draw( );

private:
	/* menu tabs/etc */
	void visuals_tab( );
	void misc_tab( );

public:
	void gui_init( HWND window, IDirect3DDevice9* device );

public:
	/* vars */
	bool input_should_listen = false;
	int* input_received_key_value = nullptr;
	bool d3d_init = false;
	bool opened = true;

};
extern ui menu;