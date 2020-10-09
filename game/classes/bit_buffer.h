#pragma once
#include <cstring>
#include <cstdint>

class bf_write {
public:
	bf_write() = default;

	unsigned long* data;
	int	data_bytes;
	int	data_bits;
	int	current_bit;
};

class bf_read {
public:
	std::uintptr_t base_address;
	std::uintptr_t current_offset;

	bf_read(std::uintptr_t address) : base_address(address), current_offset(0U) {}

	void set_offset(std::uintptr_t offset) {
		current_offset = offset;
	}

	void skip(std::uintptr_t length) {
		current_offset += length;
	}

	int read_byte() {
		char value = *(char*)(base_address + current_offset);
		++current_offset;
		return value;
	}

	bool read_bool() {
		bool value = *(bool*)(base_address + current_offset);
		++current_offset;
		return value;
	}

	const char* read_string() {
		char buffer[256];
		char length = *(char*)(base_address + current_offset);
		++current_offset;
		std::memcpy(buffer, (void*)(base_address + current_offset), length > 255 ? 255 : length);
		buffer[length > 255 ? 255 : length] = '\0';
		current_offset += length + 1;
		return buffer;
	}
};
