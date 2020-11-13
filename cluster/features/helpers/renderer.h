#pragma once
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#include <algorithm>
#include "../../color/color.h"
#include "../../vertex/vertex.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

enum e_text_alignment : unsigned int {
	DEFAULT = ( 1 << 0 ),
	VERTICAL_TOP = ( 1 << 1 ),
	VERTICAL_BOTTOM = ( 1 << 2 ),
	VERTICAL_CENTER = ( 1 << 3 ),
	HORIZONTAL_LEFT = ( 1 << 4 ),
	HORIZONTAL_RIGHT = ( 1 << 5 ),
	HORIZONTAL_CENTER = ( 1 << 6 )
};

enum e_text_flags : unsigned int {
	NONE = ( 1 << 0 ),
	DROPSHADOW = ( 1 << 1 ),
	OUTLINE = ( 1 << 2 )
};

class text_size_t {
public:
	unsigned short width, height;

	text_size_t( ) = default;
	text_size_t( int width, int height ) {
		this->width = width;
		this->height = height;
	}

	inline text_size_t& operator+=( const text_size_t& other ) {
		this->width = this->width + other.width;
		this->height = this->height + other.height;

		return *this;
	}
};

class c_renderer {
private:
	IDirect3DDevice9* device;
	IDirect3DStateBlock9* state;
	IDirect3DVertexDeclaration9* vertex_declaration;
	IDirect3DVertexShader9* vertex_shader;

public:
	struct {
		ID3DXFont* tahoma;
		ID3DXFont* smallest_pixel_7;
	} fonts;

	void initialize( IDirect3DDevice9* device );
	void setup_state( );
	void reset_state( );
	void render_rectangle( int x, int y, int width, int height, const color_t color );
	void render_filled_rectangle( int x, int y, int width, int height, const color_t color );
	void render_line( int x, int y, int x2, int y2, const color_t color );
	text_size_t render_text( int x, int y, const unsigned int alignment, const e_text_flags flags, const std::string& str, ID3DXFont* font, color_t color );
	void render_circle( int x, int y, int radius, int segments, const color_t color );
	const text_size_t calculate_text_size( const std::string& str, ID3DXFont* font );
};

extern c_renderer g_renderer;