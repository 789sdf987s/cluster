#pragma once
#include "../../cluster/vector/vector3.h"

class event_info_t;

class i_client_state {
public:
	char u0[156];
	void* net_channel;
	unsigned int challenge_nr;
	char u1[100];
	unsigned int signon_state_count;
	char u2[8];
	float next_cmd_time;
	unsigned int server_count;
	unsigned int current_sequence;
	char u3[84];
	unsigned int delta_tick;
	bool paused;
	char u4[3];
	unsigned int view_entity;
	unsigned int player_slot;
	char level_name[260];
	char level_name_short[80];
	char group_name[80];
	char u5[92];
	unsigned int max_clients;
	char u6[18824];
	float last_server_tick_time;
	bool in_simulation;
	char u7[3];
	unsigned int old_tick_count;
	float tick_remainder;
	float frame_time;
	int	last_outgoing_command;
	int choked_commands;
	int	last_command_ack;
	int	command_ack;
	int	sound_sequence;
	char u8[80];
	vector3_t view_angles;
	char u9[208];
	event_info_t* events;
};