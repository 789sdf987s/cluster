#include "math.h"

bool c_math::world_to_screen( const vector3_t& world, vector3_t& screen ) {
	if ( !this->screen_transform( world, screen ) )
		return false;

	int width, height;
	g_interfaces.engine->get_screen_size( width, height );

	screen.x = ( width * 0.5f ) + ( screen.x * width ) * 0.5f;
	screen.y = ( height * 0.5f ) - ( screen.y * height ) * 0.5f;

	return true;
}

bool c_math::screen_transform( const vector3_t& world, vector3_t& screen ) {
	static auto view_matrix = *reinterpret_cast< std::uintptr_t* >( g_utilities.signature_scan( "client.dll", "0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9" ) + 3 ) + 176;

	if ( !view_matrix )
		return false;

	const auto& world_matrix = *reinterpret_cast< view_matrix_t* >( view_matrix );

	screen.x = world_matrix.m [ 0 ][ 0 ] * world.x + world_matrix.m [ 0 ][ 1 ] * world.y + world_matrix.m [ 0 ][ 2 ] * world.z + world_matrix.m [ 0 ][ 3 ];
	screen.y = world_matrix.m [ 1 ][ 0 ] * world.x + world_matrix.m [ 1 ][ 1 ] * world.y + world_matrix.m [ 1 ][ 2 ] * world.z + world_matrix.m [ 1 ][ 3 ];
	screen.z = 0;

	const auto w = world_matrix.m [ 3 ][ 0 ] * world.x + world_matrix.m [ 3 ][ 1 ] * world.y + world_matrix.m [ 3 ][ 2 ] * world.z + world_matrix.m [ 3 ][ 3 ];

	if ( w < 0.001f ) {
		screen.x *= 100000;
		screen.y *= 100000;

		return false;
	}

	screen.x *= 1.f / w;
	screen.y *= 1.f / w;

	return true;
}

void c_math::angle_vectors( const vector3_t& angle, vector3_t& out ) {
	vector3_t sine, cosine;

	sin_cos( DEG_2_RAD( angle.x ), sine.x, cosine.x );
	sin_cos( DEG_2_RAD( angle.y ), sine.y, cosine.y );

	out.x = cosine.x * cosine.y;
	out.y = cosine.x * sine.y;
	out.z = -sine.x;
}

c_math g_math;