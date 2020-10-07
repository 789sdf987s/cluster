#pragma once
#include "../../../dependencies/minhook/MinHook.h"
#include "../interfaces/interfaces.h"
#include "../../../game/classes/usercmd.h"
#include "../../../game/classes/view_setup.h"
#include "../../../game/definitions.h"
#include "../../../game/classes/models.h"
#include "../../../game/interfaces/game_event.h"

#define REGISTERS void* ecx, void* edx
#define CREATE_HOOK_HEADER(type, class_name, name, parameters, ...)  class class_name { \
													public: \
														static type hook( parameters, __VA_ARGS__ ); \
														static inline decltype( &hook ) original; \
														static inline bool create_hook( void* to_hook ) { \
															bool success = MH_CreateHook( to_hook, &hook, reinterpret_cast< void** >( &original )) == MH_OK; \
															if ( success ) \
																g_console.message( "hooked %s", name ); \
															else \
																g_console.error( "failed to hook %s", name ); \
															return success; \
														} \
													};

class c_hooks {
public:
	bool hook_all();
	void unhook_all();
	bool is_unhooking = false;

	CREATE_HOOK_HEADER(bool __fastcall, c_create_move, "create_move", REGISTERS, float input_sample_frametime, c_usercmd* cmd);
	CREATE_HOOK_HEADER(void __fastcall, c_paint_traverse, "paint_traverse", REGISTERS, unsigned int panel, bool force_repaint, bool allow_force);
	CREATE_HOOK_HEADER(long __fastcall, c_end_scene, "end_scene", REGISTERS, IDirect3DDevice9* device);
	CREATE_HOOK_HEADER(long __fastcall, c_reset, "reset", REGISTERS, IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* presentation_parameters);
	CREATE_HOOK_HEADER(void __fastcall, c_frame_stage_notify, "frame_stage_notify", REGISTERS, client_frame_stage_t stage);
	CREATE_HOOK_HEADER(void __fastcall, c_override_view, "override_view", REGISTERS, c_view_setup* view);
	CREATE_HOOK_HEADER(void __fastcall, c_check_file_crcs_with_server, "check_file_crcs_with_server", REGISTERS);
	CREATE_HOOK_HEADER(bool __fastcall, c_loose_file_allowed, "loose_file_allowed", REGISTERS);
	CREATE_HOOK_HEADER(void __fastcall, c_draw_model_execute, "draw_model_execute", REGISTERS, void* ctx, void* state, model_render_info_t& info, matrix_t* bone_to_world);
	CREATE_HOOK_HEADER(void __fastcall, c_lock_cursor, "lock_cursor", REGISTERS);
	CREATE_HOOK_HEADER(float __fastcall, c_get_viewmodel_fov, "get_viewmodel_fov", REGISTERS);
	CREATE_HOOK_HEADER(void __fastcall, c_get_color_modulation, "get_color_modulation", REGISTERS, float* r, float* g, float* b);
	CREATE_HOOK_HEADER(void __fastcall, c_get_screen_aspect_ratio, "get_screen_aspect_ratio", REGISTERS, int w, int h);
	CREATE_HOOK_HEADER(bool __fastcall, c_is_using_static_prop_debug, "is_using_static_prop_debug", REGISTERS);
	CREATE_HOOK_HEADER(void __fastcall, c_fire_event, "fire_event", REGISTERS, i_game_event* event, bool done_broadcast);
	CREATE_HOOK_HEADER(bool __fastcall, c_convar_get_bool, "convar_get_bool", REGISTERS);
	CREATE_HOOK_HEADER(int __fastcall, c_do_post_screen_effects, "do_post_screen_effects", REGISTERS, c_view_setup* view_setup);
	CREATE_HOOK_HEADER(bool __fastcall, c_is_connected, "is_connected", REGISTERS);
	CREATE_HOOK_HEADER(void __fastcall, c_fire_events, "fire_events", REGISTERS);

	class c_wnd_proc {
	public:
		static __forceinline void set() {
			original = reinterpret_cast<WNDPROC>(SetWindowLongA(FindWindowA("Valve001", NULL), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(hook)));
			g_console.message("set wnd_proc");
		}

		static __forceinline void restore() {
			SetWindowLongA(FindWindowA("Valve001", NULL), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(original));
		}

		static LRESULT __stdcall hook(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param);
		static inline WNDPROC original;
	};

	__forceinline void* get_virtual(void* _class, unsigned int index) {
		return reinterpret_cast<void*>((*static_cast<int**>(_class))[index]);
	}
};

extern c_hooks g_hooks;
