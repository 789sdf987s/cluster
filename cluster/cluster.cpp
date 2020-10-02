#include "cluster.h"

THREAD_FUNCTION c_cluster::load(void* parameter) {
	g_cluster.module_handle = static_cast<HMODULE>(parameter);

	if (!g_console.create_console("cluster"))
		g_utilities.critical_error("failed to create console");

	g_console.special("loading cluster, built at %s on %s", g_string_utilities.to_lower(__DATE__).c_str(), g_string_utilities.to_lower(__TIME__).c_str());
	g_utilities.wait_for_modules({ "client.dll", "serverbrowser.dll", "d3d9.dll", "engine.dll", "materialsystem.dll", "panorama.dll", "vgui2.dll" });
	g_console.message("found required modules");

	if (!g_interfaces.capture_all()) {
		g_console.error("failed to capture interfaces");
		FreeLibraryAndExitThread(g_cluster.module_handle, EXIT_FAILURE);
		return EXIT_FAILURE;
	}

	g_console.message("captured interfaces");

	g_features.menu.create_context();

	g_console.message("created menu context");

	g_features.menu.set_style();

	g_console.message("set menu style");

	g_cluster.is_hooked = true;
	if (!g_hooks.hook_all()) {
		g_console.error("failed to place hooks");
		FreeLibraryAndExitThread(g_cluster.module_handle, EXIT_FAILURE);
		return EXIT_FAILURE;
	}

	g_console.message("placed hooks");
	g_console.queue_close();

	while (!((GetAsyncKeyState(VK_END) & 0x8000) && (GetAsyncKeyState(VK_DELETE) & 0x8000)))
		g_utilities.sleep(50);

	FreeLibraryAndExitThread(g_cluster.module_handle, EXIT_FAILURE);
	return EXIT_SUCCESS;
}

void c_cluster::unload() {
	g_console.close_if_queued();

	if (!g_cluster.is_hooked)
		return;

	g_hooks.unhook_all();
}

c_cluster g_cluster;
