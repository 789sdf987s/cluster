#include "../hooks.h"
#include <intrin.h>

bool __fastcall c_hooks::c_is_following_entity::hook(REGISTERS) {
	if (g_hooks.is_unhooking)
		return original(ecx, edx);

	static std::uint8_t* address = g_utilities.signature_scan("client.dll", "E8 ? ? ? ? 83 7D FC 00 8B F8") + 0x1A;
	static std::uintptr_t relative_adress = *reinterpret_cast<std::uintptr_t*>(std::uintptr_t(address) + 0x1);
	static std::uint8_t* target_return_adress = address + 0x5 + relative_adress;

	if (static_cast<uint8_t*>(_ReturnAddress()) == target_return_adress && ecx)
		return true;

	return original(ecx, edx);
}
