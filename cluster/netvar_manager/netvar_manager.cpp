#include "netvar_manager.h"

void c_netvar_manager::initialize(netvar_table_map& table_map) {
	std::map< std::string, std::map< uintptr_t, std::string > > var_dump;
	for (c_client_class* client_class = g_interfaces.client->get_client_classes(); client_class; client_class = client_class->next_ptr) {
		c_recv_table* table = reinterpret_cast<c_recv_table*>(client_class->recvtable_ptr);
		const char* table_name = table->table_name;
		const uint32_t table_name_hash = g_hasher.hash(table_name);

		if (table == nullptr)
			continue;

		add_props_for_table(table_map, table_name_hash, table_name, table, var_dump);
	}
}

void c_netvar_manager::add_props_for_table(netvar_table_map& table_map, const uint32_t table_name_hash, const std::string& table_name, c_recv_table* table, std::map<std::string, std::map<uintptr_t, std::string>>& var_dump, const size_t child_offset) {
	for (int i = 0; i < table->props_count; ++i) {
		c_recv_prop& prop = table->props[i];

		if (prop.data_table && prop.elements_count > 0) {
			if (std::string(prop.prop_name).substr(0, 1) == std::string("0"))
				continue;

			add_props_for_table(table_map, table_name_hash, table_name, prop.data_table, var_dump, prop.offset + child_offset);
		}

		const std::string name = prop.prop_name;

		if (name.substr(0, 1) != "m")
			continue;

		const uint32_t name_hash = g_hasher.hash(prop.prop_name);
		const unsigned int offset = uintptr_t(prop.offset) + child_offset;

		table_map[table_name_hash][name_hash] = offset;
	}
}

uintptr_t c_netvar_manager::get_netvar(const uint32_t table, const uint32_t prop) {
	static netvar_table_map map = {};
	if (map.empty())
		initialize(map);

	if (map.find(table) == map.end())
		return 0;

	netvar_key_value_map& table_map = map.at(table);
	if (table_map.find(prop) == table_map.end())
		return 0;

	return table_map.at(prop);
}

c_netvar_manager g_netvar_manager;