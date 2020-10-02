#include <Windows.h>
#include "cluster/cluster.h"

BOOL APIENTRY DllMain(HMODULE module_handle, DWORD call_reason, LPVOID reserved) {
	switch (call_reason) {
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(module_handle);
		return g_utilities.create_thread(g_cluster.load, module_handle);

	case DLL_PROCESS_DETACH:
		g_cluster.unload();
		return TRUE;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		return FALSE;
	}
}