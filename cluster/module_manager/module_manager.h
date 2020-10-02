#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include <optional>

class c_module_manager {
public:
	inline std::optional<HMODULE> get_handle(const std::string& module_name) {
		for (const std::pair<std::string, HMODULE>& current_pair : module_handles) {
			if (current_pair.first == module_name)
				return current_pair.second;
		}

		HMODULE module_handle = GetModuleHandleA(module_name.c_str());
		if (module_handle != NULL) {
			module_handles.push_back({ module_name, module_handle });
			return module_handle;
		}

		module_handle = LoadLibraryA(module_name.c_str());
		if (module_handle == NULL) {
			return { };
		}

		module_handles.push_back({ module_name, module_handle });
		return module_handle;
	}

private:
	std::vector<std::pair<std::string, HMODULE>> module_handles;
};

extern c_module_manager g_module_manager;