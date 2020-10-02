#pragma once
#include <string>
#include <fstream>
#include <string>

class c_config_system {
public:
	struct {
		bool enable;
		bool box;
	} visuals;

	bool save(const std::string file_name);
	bool load(const std::string file_name);
};

extern c_config_system g_config_system;