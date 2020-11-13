#include "console.h"

bool c_console::create_console( const std::string& title ) {
	if ( !AllocConsole( ) )
		return false;

	freopen_s( reinterpret_cast< _iobuf** >( __acrt_iob_func( 0 ) ), "conin$", "r", static_cast< _iobuf* >( __acrt_iob_func( 0 ) ) );
	freopen_s( reinterpret_cast< _iobuf** >( __acrt_iob_func( 1 ) ), "conout$", "w", static_cast< _iobuf* >( __acrt_iob_func( 1 ) ) );
	freopen_s( reinterpret_cast< _iobuf** >( __acrt_iob_func( 2 ) ), "conout$", "w", static_cast< _iobuf* >( __acrt_iob_func( 2 ) ) );

	std_out_handle = GetStdHandle( STD_OUTPUT_HANDLE );
	return SetConsoleTitleA( title.c_str( ) );
}

void c_console::queue_close( ) {
	this->is_close_queued = true;
}

void c_console::close_if_queued( ) {
	if ( !this->is_close_queued )
		return;

	fclose( static_cast< _iobuf* >( __acrt_iob_func( 0 ) ) );
	fclose( static_cast< _iobuf* >( __acrt_iob_func( 1 ) ) );
	fclose( static_cast< _iobuf* >( __acrt_iob_func( 2 ) ) );

	FreeConsole( );
}

void c_console::message( const char* message, ... ) {
	if ( strlen( message ) > MAX_LOG_SIZE )
		g_utilities.critical_error( "length of message to log is over MAX_LOG_SIZE" );

	va_list arguments;

	va_start( arguments, message );
	memset( buffer, '\0', sizeof( buffer ) );
	vsprintf_s( buffer, message, arguments );

	SetConsoleTextAttribute( std_out_handle, COLOR_DARK_WHITE );
	std::cout << "[" << g_utilities.get_time_formatted( "%d.%m.%Y %H:%M:%S" ) << "] [" << GetCurrentThreadId( ) << "] message: " << buffer << "\n";
	SetConsoleTextAttribute( std_out_handle, COLOR_DARK_WHITE );

	va_end( arguments );
}

void c_console::warning( const char* warning, ... ) {
	if ( strlen( warning ) > MAX_LOG_SIZE )
		g_utilities.critical_error( "length of warning to log is over MAX_LOG_SIZE" );

	va_list arguments;

	va_start( arguments, warning );
	memset( buffer, '\0', sizeof( buffer ) );
	vsprintf_s( buffer, warning, arguments );

	SetConsoleTextAttribute( std_out_handle, COLOR_DARK_YELLOW );
	std::cout << "[" << g_utilities.get_time_formatted( "%d.%m.%Y %H:%M:%S" ) << "] [" << GetCurrentThreadId( ) << "] warning: " << buffer << "\n";
	SetConsoleTextAttribute( std_out_handle, COLOR_DARK_WHITE );

	va_end( arguments );
}

void c_console::error( const char* error, ... ) {
	if ( strlen( error ) > MAX_LOG_SIZE )
		g_utilities.critical_error( "length of error to log is over MAX_LOG_SIZE" );

	va_list arguments;

	va_start( arguments, error );
	memset( buffer, '\0', sizeof( buffer ) );
	vsprintf_s( buffer, error, arguments );

	SetConsoleTextAttribute( std_out_handle, COLOR_DARK_RED );
	std::cout << "[" << g_utilities.get_time_formatted( "%d.%m.%Y %H:%M:%S" ) << "] [" << GetCurrentThreadId( ) << "] error: " << buffer << "\n";
	SetConsoleTextAttribute( std_out_handle, COLOR_DARK_WHITE );

	va_end( arguments );
}

void c_console::special( const char* special, ... ) {
	if ( strlen( special ) > MAX_LOG_SIZE )
		g_utilities.critical_error( "length of special to log is over MAX_LOG_SIZE" );

	va_list arguments;

	va_start( arguments, special );
	memset( buffer, '\0', sizeof( buffer ) );
	vsprintf_s( buffer, special, arguments );

	SetConsoleTextAttribute( std_out_handle, COLOR_DARK_PURPLE );
	std::cout << "[" << g_utilities.get_time_formatted( "%d.%m.%Y %H:%M:%S" ) << "] [" << GetCurrentThreadId( ) << "] " << buffer << "\n";
	SetConsoleTextAttribute( std_out_handle, COLOR_DARK_WHITE );

	va_end( arguments );
}

c_console g_console;