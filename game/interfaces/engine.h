#pragma once
#include <cstdint>
#include "../../cluster/vector/vector3.h"

struct player_info_t {
	int64_t __pad0;

	union {
		int64_t x_uid;
		struct {
			int x_uid_low;
			int x_uid_high;
		};
	};

	char name[128];
	int user_id;
	char guid[33];
	unsigned int friends_id;
	char friends_name[128];
	bool fake_player;
	bool is_hltv;
	unsigned int custom_files[4];
	unsigned char files_downloaded;
};

class i_engine {
public:
	void* get_net_channel_info() {
		using original_fn = void* (__thiscall*)(i_engine*);
		return (*(original_fn**)this)[78](this);
	}

	int get_local_player() {
		using original_fn = int(__thiscall*)(i_engine*);
		return (*(original_fn**)this)[12](this);
	}

	int get_player_for_user_id(int user_id) {
		using original_fn = int(__thiscall*)(i_engine*, int);
		return (*(original_fn**)this)[9](this, user_id);
	}

	void get_player_info(int index, player_info_t* info) {
		using original_fn = void(__thiscall*)(i_engine*, int, player_info_t*);
		return (*(original_fn**)this)[8](this, index, info);
	}

	void get_screen_size(int& width, int& height) {
		using original_fn = void(__thiscall*)(i_engine*, int&, int&);
		return (*(original_fn**)this)[5](this, width, height);
	}

	bool is_in_game() {
		using original_fn = bool(__thiscall*)(i_engine*);
		return (*(original_fn**)this)[26](this);
	}

	bool is_connected() {
		using original_fn = bool(__thiscall*)(i_engine*);
		return (*(original_fn**)this)[27](this);
	}

	void execute_cmd(const char* cmd) {
		using original_fn = void(__thiscall*)(i_engine*, const char*);
		return (*(original_fn**)this)[108](this, cmd); // this always seems to crash whilst debugging, just feel free to continue.
	}

	void set_view_angles(vector3_t& angles) {
		using original_fn = void(__thiscall*)(i_engine*, vector3_t&);
		return (*(original_fn**)this)[19](this, angles);
	}

	void get_view_angles(vector3_t& angles) {
		using original_fn = void(__thiscall*)(i_engine*, vector3_t&);
		return (*(original_fn**)this)[18](this, angles);
	}

	void*& world_to_screen_matrix() {
		using original_fn = void*& (__thiscall*)(i_engine*);
		return (*(original_fn**)this)[37](this);
	}

	bool is_taking_screenshot() {
		using original_fn = bool(__thiscall*)(i_engine*);
		return (*(original_fn**)this)[92](this);
	}

	int get_max_clients() {
		using original_fn = int(__thiscall*)(i_engine*);
		return (*(original_fn**)this)[20](this);
	}

	const char* get_level_name() {
		using original_fn = const char* (__thiscall*)(i_engine*);
		return (*(original_fn**)this)[53](this);
	}
};
