#pragma once
#include <Windows.h>
#include <functional>
#include <string>
#include <vector>
#include <thread>
#include <time.h>
#include <iomanip>
#include <sstream>
#include <optional>
#include "../module_manager/module_manager.h"

#define THREAD_FUNCTION DWORD WINAPI
#define MODULE_WAIT_CHECK_DELAY 25

class c_utilities {
public:
	bool create_thread( THREAD_FUNCTION function( void* ), void* parameter );
	void wait_for_modules( const std::vector<std::string>& modules );
	void sleep( unsigned int ms );
	void critical_error( const std::string& message );
	std::optional<std::uint8_t*> signature_scan( const std::string& module_name, const std::string& signature );

	inline std::string get_time_formatted( const std::string& format ) {
		time_t time = std::time( nullptr );
		tm local_time;
		localtime_s( &local_time, &time );

		std::stringstream ss;
		ss << std::put_time( &local_time, format.c_str( ) );
		return ss.str( );
	}
};

extern c_utilities g_utilities;