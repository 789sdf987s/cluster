#pragma once
#include <Windows.h>
#include <string>
#include <iostream>
#include "../utilities/utilities.h"

#define COLOR_DARK_RED 4
#define COLOR_DARK_YELLOW 6
#define COLOR_DARK_WHITE 7
#define COLOR_DARK_PURPLE 5
#define MAX_LOG_SIZE 512

class c_console {
public:
	bool create_console( const std::string& title );
	void queue_close( );
	void close_if_queued( );
	void message( const char* message, ... );
	void error( const char* error, ... );
	void warning( const char* warning, ... );
	void special( const char* special, ... );

private:
	HANDLE std_out_handle;
	char buffer [ MAX_LOG_SIZE + 1 ];
	bool is_close_queued;
};

extern c_console g_console;