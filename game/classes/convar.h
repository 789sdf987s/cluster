#pragma once

class c_convar {
public:
	bool get_bool() {
		using original_fn = bool(__thiscall*)(c_convar*);
		return (*(original_fn**)this)[13](this);
	}
};
