#pragma once
#include <cstdint>
#include <cstddef>

class event_info_t {
public:
	std::uint16_t class_id;
	std::byte pad0[0x2];
	float fire_delay;
	std::byte pad1[0x4];
	void* client_class;
	std::byte pad2[0x28];
	event_info_t* next_info;
};