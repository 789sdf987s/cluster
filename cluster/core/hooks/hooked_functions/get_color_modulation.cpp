#include "../hooks.h"
#include "../../../hasher/hasher.h"

void __fastcall c_hooks::c_get_color_modulation::hook(REGISTERS, float* r, float* g, float* b) {
	if (g_hooks.is_unhooking)
		return original(ecx, edx, r, g, b);

	original(ecx, edx, r, g, b);

	const i_material* material = reinterpret_cast<i_material*>(ecx);

	if (!material)
		return;

	const auto group = g_hasher.hash(material->get_texture_group_name());

	if (group != g_hasher.hash_const("World textures") && group != g_hasher.hash_const("StaticProp textures") && group != g_hasher.hash_const("SkyBox textures"))
		return;

	const auto is_prop = group == g_hasher.hash_const("StaticProp textures");

	*r *= is_prop ? 0.3f : 0.2f;
	*g *= is_prop ? 0.3f : 0.2f;
	*b *= is_prop ? 0.3f : 0.2f;
}
