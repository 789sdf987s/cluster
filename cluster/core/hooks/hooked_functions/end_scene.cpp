#include <mutex>
#include <intrin.h>
#include "../hooks.h"
#include "../../../features/features.h"
#include "../../../features/helpers/renderer.h"

long __fastcall c_hooks::c_end_scene::hook(REGISTERS, IDirect3DDevice9* device) {
	static std::uintptr_t gameoverlay_return_address = 0;

	if (!gameoverlay_return_address) {
		MEMORY_BASIC_INFORMATION info;
		VirtualQuery(_ReturnAddress(), &info, sizeof(MEMORY_BASIC_INFORMATION));

		char mod[MAX_PATH];
		GetModuleFileNameA(static_cast<HMODULE>(info.AllocationBase), mod, MAX_PATH);

		if (strstr(mod, "gameoverlay"))
			gameoverlay_return_address = reinterpret_cast<std::uintptr_t>(_ReturnAddress());
	}

	if (gameoverlay_return_address != reinterpret_cast<std::uintptr_t>(_ReturnAddress()))
		return original(ecx, edx, device);

	static std::once_flag menu_init_flag, render_init_flag;
	std::call_once(menu_init_flag, &c_menu::impl_init, &g_features.menu, FindWindowA("Valve001", "Counter-Strike: Global Offensive"), device);
	std::call_once(render_init_flag, &c_renderer::initialize, &g_renderer, device);

	g_renderer.setup_state();
	g_features.visuals.populate_render_list();

	if (g_features.menu.is_open) {
		g_features.menu.new_frame();
		{
			g_features.menu.populate_render_list();
		}
		g_features.menu.end_frame_and_render();
	}

	g_renderer.reset_state();

	return original(ecx, edx, device);
}