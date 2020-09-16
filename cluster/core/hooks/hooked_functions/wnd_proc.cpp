#include "../hooks.h"
#include "../../../../dependencies/imgui/win32/imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

LRESULT __stdcall c_hooks::c_wnd_proc::hook( HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param ) {
	if ( ImGui_ImplWin32_WndProcHandler( hwnd, message, w_param, l_param ) )
		return true;

	return CallWindowProcA( original, hwnd, message, w_param, l_param );
}
