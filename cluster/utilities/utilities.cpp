#include "utilities.h"

bool c_utilities::create_thread(THREAD_FUNCTION function(void*), void* parameter) {
	HANDLE thread_handle = CreateThread(NULL, 0, function, parameter, 0, NULL);
	if (thread_handle == NULL)
		return false;

	CloseHandle(thread_handle);
	return true;
}

void c_utilities::wait_for_modules(const std::vector<std::string>& modules) {
	unsigned short found_modules;

	do {
		found_modules = 0;

		for (const std::string& current_module_name : modules) {
			HMODULE current_module_handle = GetModuleHandleA(current_module_name.c_str());

			if (current_module_handle != NULL)
				found_modules++;
		}

		this->sleep(MODULE_WAIT_CHECK_DELAY);
	} while (found_modules != modules.size());
}

void c_utilities::sleep(unsigned int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void c_utilities::critical_error(const std::string& message) {
	MessageBoxA(NULL, message.c_str(), "critical error", MB_OK);
	_Exit(EXIT_FAILURE);
}

std::uint8_t* c_utilities::signature_scan(const std::string& module_name, const std::string& signature) {
	const std::optional<HMODULE> module_handle = g_module_manager.get_handle(module_name);
	if (!module_handle.has_value())
		return {};

	static auto pattern_to_byte = [](const char* pattern) {
		std::vector<int> bytes;
		char* start = const_cast<char*>(pattern);
		char* end = const_cast<char*>(pattern) + std::strlen(pattern);

		for (char* current = start; current < end; ++current) {
			if (*current == '?') {
				++current;

				if (*current == '?')
					++current;

				bytes.push_back(-1);
			}
			else
				bytes.push_back(std::strtoul(current, &current, 16));
		}

		return bytes;
	};

	const PIMAGE_DOS_HEADER dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(module_handle.value());
	const PIMAGE_NT_HEADERS nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(module_handle.value()) + dos_header->e_lfanew);

	const DWORD size_of_image = nt_headers->OptionalHeader.SizeOfImage;
	std::vector<int> pattern_bytes = pattern_to_byte(signature.c_str());
	std::uint8_t* scan_bytes = reinterpret_cast<std::uint8_t*>(module_handle.value());

	size_t s = pattern_bytes.size();
	int* d = pattern_bytes.data();

	for (unsigned long i = 0ul; i < size_of_image - s; ++i) {
		bool found = true;

		for (auto j = 0ul; j < s; ++j) {
			if (scan_bytes[i + j] != d[j] && d[j] != -1) {
				found = false;
				break;
			}
		}

		if (found)
			return &scan_bytes[i];
	}

	return {};
}

c_utilities g_utilities;