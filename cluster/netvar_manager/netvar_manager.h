#pragma once
#include <map>
#include <string>
#include "../core/interfaces/interfaces.h"
#include "../hasher/hasher.h"

class c_netvar_manager {
private:
	using netvar_key_value_map = std::unordered_map<uint32_t, uintptr_t>;
	using netvar_table_map = std::unordered_map<uint32_t, netvar_key_value_map>;

public:
	void initialize(netvar_table_map& table_map);
	void add_props_for_table(netvar_table_map& table_map, const uint32_t table_name_hash, const std::string& table_name, c_recv_table* table, std::map<std::string, std::map<uintptr_t, std::string>>& var_dump, const size_t child_offset = 0);
	uintptr_t get_netvar(const uint32_t table, const uint32_t prop);
};

extern c_netvar_manager g_netvar_manager;