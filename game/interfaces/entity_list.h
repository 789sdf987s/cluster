#pragma once

class i_entity_list {
public:
	void* get_client_entity( int index ) {
		using original_fn = void* ( __thiscall* )( i_entity_list*, int );
		return ( *( original_fn** ) this ) [ 3 ]( this, index );
	}

	void* get_client_entity_handle( void* handle ) {
		using original_fn = void* ( __thiscall* )( i_entity_list*, void* );
		return ( *( original_fn** ) this ) [ 4 ]( this, handle );
	}

	int get_highest_index( ) {
		using original_fn = int( __thiscall* )( i_entity_list* );
		return ( *( original_fn** ) this ) [ 6 ]( this );
	}
};