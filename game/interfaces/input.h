#pragma once
class vector3_t;

class i_input {
public:
	char pad [ 172 ];
	bool pad2;
	bool is_camera_in_third_person;
	char pad3 [ 2 ];
	vector3_t camera_offset;
};
