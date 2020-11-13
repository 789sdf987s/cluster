#pragma once
#include "../../../dependencies/minhook/MinHook.h"
#include "../interfaces/interfaces.h"
#include "../../../game/classes/usercmd.h"
#include "../../../game/classes/view_setup.h"
#include "../../../game/definitions.h"
#include "../../../game/classes/models.h"
#include "../../../game/interfaces/game_event.h"
#include "../../../game/classes/bit_buffer.h"

#define REGISTERS void* ecx, void* edx
#define CREATE_HOOK_HEADER(type, class_name, name, parameters, ...)  class class_name { \
													public: \
														static type hook(parameters, __VA_ARGS__); \
														static inline decltype(&hook) original; \
														static inline bool create_hook(void* to_hook) { \
															MH_STATUS success = MH_CreateHook(to_hook, &hook, reinterpret_cast<void**>(&original)); \
															if (success == MH_OK) \
																g_console.message("hooked %s", name); \
															else \
																g_console.error("failed to hook %s (%s)", name, MH_StatusToString(success)); \
															return success == MH_OK; \
														} \
														static inline bool create_hook(const std::string& module_name, const std::string& signature) { \
															std::uint8_t* scanned_signature = g_utilities.signature_scan(module_name, signature); \
															if (!scanned_signature) { \
																g_console.error("failed to find signature to hook %s", name); \
																return false; \
															} \
															return create_hook(scanned_signature); \
														} \
														static inline bool create_hook(void* interface_, unsigned int index) { \
															return create_hook(reinterpret_cast<void*>((*static_cast<int**>(interface_))[index])); \
														} \
													};

class c_hooks {
public:
	bool hook_all( );
	void unhook_all( );
	bool is_unhooking = false;

	CREATE_HOOK_HEADER( bool __fastcall, c_create_move, "create_move", REGISTERS, float input_sample_frametime, c_usercmd* cmd );
	CREATE_HOOK_HEADER( void __fastcall, c_paint_traverse, "paint_traverse", REGISTERS, unsigned int panel, bool force_repaint, bool allow_force );
	CREATE_HOOK_HEADER( long __fastcall, c_end_scene, "end_scene", REGISTERS, IDirect3DDevice9* device );
	CREATE_HOOK_HEADER( long __fastcall, c_reset, "reset", REGISTERS, IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* presentation_parameters );
	CREATE_HOOK_HEADER( void __fastcall, c_frame_stage_notify, "frame_stage_notify", REGISTERS, client_frame_stage_t stage );
	CREATE_HOOK_HEADER( void __fastcall, c_override_view, "override_view", REGISTERS, c_view_setup* view );
	CREATE_HOOK_HEADER( void __fastcall, c_check_file_crcs_with_server, "check_file_crcs_with_server", REGISTERS );
	CREATE_HOOK_HEADER( bool __fastcall, c_loose_file_allowed, "loose_file_allowed", REGISTERS );
	CREATE_HOOK_HEADER( void __fastcall, c_draw_model_execute, "draw_model_execute", REGISTERS, void* ctx, void* state, model_render_info_t& info, matrix_t* bone_to_world );
	CREATE_HOOK_HEADER( void __fastcall, c_lock_cursor, "lock_cursor", REGISTERS );
	CREATE_HOOK_HEADER( float __fastcall, c_get_viewmodel_fov, "get_viewmodel_fov", REGISTERS );
	CREATE_HOOK_HEADER( void __fastcall, c_get_color_modulation, "get_color_modulation", REGISTERS, float* r, float* g, float* b );
	CREATE_HOOK_HEADER( void __fastcall, c_get_screen_aspect_ratio, "get_screen_aspect_ratio", REGISTERS, int w, int h );
	CREATE_HOOK_HEADER( bool __fastcall, c_is_using_static_prop_debug, "is_using_static_prop_debug", REGISTERS );
	CREATE_HOOK_HEADER( void __fastcall, c_fire_event, "fire_event", REGISTERS, i_game_event* event, bool done_broadcast );
	CREATE_HOOK_HEADER( bool __fastcall, c_convar_get_bool, "convar_get_bool", REGISTERS );
	CREATE_HOOK_HEADER( int __fastcall, c_do_post_screen_effects, "do_post_screen_effects", REGISTERS, c_view_setup* view_setup );
	CREATE_HOOK_HEADER( bool __fastcall, c_is_connected, "is_connected", REGISTERS );
	CREATE_HOOK_HEADER( void __fastcall, c_fire_events, "fire_events", REGISTERS );
	CREATE_HOOK_HEADER( bool __fastcall, c_is_hltv, "is_hltv", REGISTERS );
	CREATE_HOOK_HEADER( int __fastcall, c_list_leaves_in_box, "list_leaves_in_box", REGISTERS, const vector3_t& mins, const vector3_t& maxs, unsigned short* list, int list_max );
	CREATE_HOOK_HEADER( bool __fastcall, c_is_following_entity, "is_following_entity", REGISTERS );
	CREATE_HOOK_HEADER( bool __fastcall, c_should_skip_animation_frame, "should_skip_animation_frame", REGISTERS );
	CREATE_HOOK_HEADER( void __fastcall, c_standard_blending_rules, "standard_blending_rules", REGISTERS, void* studio_hdr, vector3_t* position, void* quaternion, float current_time, int bone_mask );
	CREATE_HOOK_HEADER( void __fastcall, c_update_client_side_animations, "update_client_side_animations", REGISTERS );
	CREATE_HOOK_HEADER( void __fastcall, c_do_procedural_foot_plant, "do_procedural_foot_plant", REGISTERS, int a1, int a2, int a3, int a4 );
	CREATE_HOOK_HEADER( bool __fastcall, c_setup_bones, "setup_bones", REGISTERS, matrix_t* bone_to_world_out, int max_bones, int bone_mask, float current_time );
	CREATE_HOOK_HEADER( vector3_t* __fastcall, c_get_view_angles, "get_view_angles", REGISTERS );
	CREATE_HOOK_HEADER( void __fastcall, c_run_command, "run_command", REGISTERS, entity_t* entity, c_usercmd* cmd, void* move_helper );
	CREATE_HOOK_HEADER( bool __fastcall, c_write_user_cmd_to_buffer, "wirte_user_cmd_to_buffer", REGISTERS, int slot, bf_write* buffer, int from, int to, bool is_new_cmd );
	CREATE_HOOK_HEADER( void __fastcall, c_calc_view_bob, "calc_view_bob", REGISTERS, vector3_t& eye_origin );
	CREATE_HOOK_HEADER( void __fastcall, c_calc_view, "calc_view", REGISTERS, vector3_t& eye_origin, vector3_t& eye_angles, float& z_near, float& z_far, float& fov );
	CREATE_HOOK_HEADER( bool __fastcall, c_should_interpolate, "should_interpolate", REGISTERS );
	CREATE_HOOK_HEADER( void __fastcall, c_play_step_sound, "play_step_sound", REGISTERS, vector3_t& origin, void* surface, float volume, bool force );

	class c_wnd_proc {
	public:
		static __forceinline void set( ) {
			original = reinterpret_cast< WNDPROC >( SetWindowLongA( FindWindowA( "Valve001", NULL ), GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( hook ) ) );
			g_console.message( "set wnd_proc" );
		}

		static __forceinline void restore( ) {
			SetWindowLongA( FindWindowA( "Valve001", NULL ), GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( original ) );
		}

		static LRESULT __stdcall hook( HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param );
		static inline WNDPROC original;
	};
};

extern c_hooks g_hooks;
