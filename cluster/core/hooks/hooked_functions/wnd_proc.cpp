#include "../hooks.h"
#include "../../../features/features.h"
#include "../../../../dependencies/imgui/win32/imgui_impl_win32.h"
#include "../../interfaces/interfaces.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

LRESULT __stdcall c_hooks::c_wnd_proc::hook( HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param ) {
	if ( message == WM_KEYDOWN && w_param == VK_INSERT )
		g_features.menu.is_open = !g_features.menu.is_open;

	if ( g_interfaces.engine->is_in_game( ) ?
		( g_features.menu.is_open && ImGui_ImplWin32_WndProcHandler( hwnd, message, w_param, l_param ) ) :
		( ImGui_ImplWin32_WndProcHandler( hwnd, message, w_param, l_param ) || g_features.menu.is_open ) )
		return true;

	return CallWindowProcA( original, hwnd, message, w_param, l_param );
}
