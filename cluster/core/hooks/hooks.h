#pragma once

class c_hooks {
public:
	bool hook_all( );
	void unhook_all( );
};

extern c_hooks g_hooks;