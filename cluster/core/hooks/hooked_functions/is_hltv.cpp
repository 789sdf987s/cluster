#include "../hooks.h"
#include <intrin.h>

bool __fastcall c_hooks::c_is_hltv::hook(REGISTERS) {
	if (g_hooks.is_unhooking)
		return original(ecx, edx);

	const std::uint8_t* return_address = static_cast<uint8_t*>(_ReturnAddress());

	static std::uint8_t* re_evaluate_anim_lod = g_utilities.signature_scan("client.dll", "84 C0 0F 85 ? ? ? ? A1 ? ? ? ? 8B B7");
	static std::uint8_t* setup_velocity = g_utilities.signature_scan("client.dll", "84 C0 75 38 8B 0D ? ? ? ? 8B 01 8B 80 ? ? ? ?");
	static std::uint8_t* accumulate_layers = g_utilities.signature_scan("client.dll", "84 C0 75 0D F6 87");

	if (return_address == re_evaluate_anim_lod ||
		return_address == setup_velocity ||
		return_address == accumulate_layers)
		return true;

	return original(ecx, edx);
}
