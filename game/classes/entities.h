#pragma once
#include <Windows.h>
#include "../../cluster/matrix/matrix.h"
#include "../../cluster/netvar_manager/netvar_manager.h"
#include "../../cluster/hasher/hasher.h"

#define INDEX_FROM(from, index, return_type, name) return_type name() { \
														using original_fn = return_type(__thiscall*)(void*); \
														return (*(original_fn**)from )[index]( from ); \
													};

#define INTERNAL_RELATIVE_OFFSET(return_type, offset, name) return_type name() { \
														return reinterpret_cast<return_type>(uintptr_t(this) + offset); \
													};

#define NETVAR(table, prop, name, type) type& name() { \
											static uintptr_t offset = 0; \
											if (!offset) \
												offset = g_netvar_manager.get_netvar(g_hasher.hash(table), g_hasher.hash(prop)); \
											return *reinterpret_cast<type*>(uintptr_t(this) + offset); \
										};

#define RELATIVE_OFFSET(return_type, offset, name) return_type& name() {\
														return *(return_type*)(uintptr_t(this) + offset); \
													};

#define BASE_ENTITY "DT_BaseEntity"
#define BASE_PLAYER "DT_BasePlayer"
#define CS_PLAYER "DT_CSPlayer"

class entity_t {
public:
	INTERNAL_RELATIVE_OFFSET(void*, 0x8, networkable);
	RELATIVE_OFFSET(matrix_t, 0x444, coordinate_frame);
	INTERNAL_RELATIVE_OFFSET(void*, 0x8, animating);
	INDEX_FROM(networkable(), 9, bool, is_dormant);
	INDEX_FROM(networkable(), 10, int, index);
	INDEX_FROM(this, 157, bool, is_player);
	INDEX_FROM(this, 165, bool, is_weapon);
	NETVAR(BASE_ENTITY, "m_vecMins", mins, vector3_t);
	NETVAR(BASE_ENTITY, "m_vecMaxs", maxs, vector3_t);
	NETVAR(BASE_PLAYER, "m_vecOrigin", origin, vector3_t);
	NETVAR(BASE_ENTITY, "m_bSpotted", is_spotted, bool);
	NETVAR(BASE_PLAYER, "m_vecViewOffset[0]", view_offset, vector3_t);
	NETVAR(BASE_PLAYER, "m_vecVelocity[0]", velocity, vector3_t);
	NETVAR(BASE_PLAYER, "m_aimPunchAngle", aim_punch_angle, vector3_t);
	NETVAR(BASE_PLAYER, "m_viewPunchAngle", view_punch_angle, vector3_t);
	NETVAR(BASE_ENTITY, "m_fEffects", effects, int);

	bool setup_bones(matrix_t* matrix, int max_bones, int mask, float setup_time) {
		using original_fn = bool(__thiscall*)(void*, matrix_t*, int, int, float);
		return (*(original_fn**)networkable())[13](networkable(), matrix, max_bones, mask, setup_time);
	}
};

class player_t : public entity_t {
public:
	INDEX_FROM(this, 10, vector3_t, abs_origin);
	NETVAR(CS_PLAYER, "m_fFlags", flags, int);
	NETVAR(CS_PLAYER, "m_flSimulationTime", simulation_time, float);
	NETVAR(CS_PLAYER, "m_iTeamNum", team, int);
	NETVAR(CS_PLAYER, "m_iHealth", health, int);
	NETVAR(CS_PLAYER, "m_iAccount", money, int);
	NETVAR(CS_PLAYER, "m_bIsScoped", is_scoped, bool);
	NETVAR(CS_PLAYER, "m_bIsDefusing", is_defusing, bool);
	NETVAR(CS_PLAYER, "m_bHasDefuser", has_defuser, bool);
	NETVAR(CS_PLAYER, "m_ArmorValue", armor, int);
	NETVAR(CS_PLAYER, "m_bHasHelmet", has_helmet, bool);
	NETVAR(CS_PLAYER, "m_bGunGameImmunity", is_immune, bool);
	NETVAR(CS_PLAYER, "m_nTickBase", tick_base, int);
	NETVAR(CS_PLAYER, "m_flDuckAmount", duck_amount, float);
	NETVAR(CS_PLAYER, "m_flLowerBodyYawTarget", lower_body_yaw_target, float);
	NETVAR(CS_PLAYER, "m_angEyeAngles", eye_angles, vector3_t);
};
