#pragma once
#include <Windows.h>
#include <d3d9.h>
#include "../../../dependencies/imgui/imgui.h"
#include "../../../dependencies/imgui/dx9/imgui_impl_dx9.h"
#include "../../../dependencies/imgui/win32/imgui_impl_win32.h"

class c_menu {
public:
	void create_context( );
	void setup_style( );
	void impl_init( HWND window, IDirect3DDevice9* device );
	void render( );
	void destory( );
	void reset( bool is_pre_reset );
};