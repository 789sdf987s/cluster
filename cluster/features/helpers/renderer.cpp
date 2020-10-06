#include "renderer.h"

void c_renderer::initialize(IDirect3DDevice9* device) {
	this->device = device;

	D3DXCreateFontA(device, 12, 0, FW_EXTRABOLD, 1, false, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH, "Tahoma", &fonts.tahoma);
	D3DXCreateFontA(device, 11, 0, FW_EXTRALIGHT, 1, false, ANSI_CHARSET, OUT_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, DEFAULT_PITCH, "Smallest Pixel-7", &fonts.smallest_pixel_7);
}

void c_renderer::setup_state() {
	device->CreateStateBlock(D3DSBT_PIXELSTATE, &state);
	device->GetVertexDeclaration(&vertex_declaration);
	device->GetVertexShader(&vertex_shader);

	device->SetVertexShader(nullptr);
	device->SetPixelShader(nullptr);
	device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	device->SetRenderState(D3DRS_LIGHTING, false);
	device->SetRenderState(D3DRS_FOGENABLE, false);
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	device->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	device->SetRenderState(D3DRS_SCISSORTESTENABLE, true);
	device->SetRenderState(D3DRS_ZWRITEENABLE, false);
	device->SetRenderState(D3DRS_STENCILENABLE, false);

	device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, false);
	device->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, false);

	device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	device->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	device->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, true);
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_INVDESTALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	device->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);

	device->SetRenderState(D3DRS_SRGBWRITEENABLE, false);
	device->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);
}

void c_renderer::reset_state() {
	state->Apply();
	state->Release();
	device->SetVertexDeclaration(vertex_declaration);
	device->SetVertexShader(vertex_shader);
}

void c_renderer::render_rectangle(CS x, CS y, CS width, CS height, const color_t color) {
	render_filled_rectangle(x, y, width, 1, color);
	render_filled_rectangle(x, y, 1, height, color);
	render_filled_rectangle(x + width - 1, y, 1, height, color);
	render_filled_rectangle(x, y + height - 1, width, 1, color);
}

void c_renderer::render_filled_rectangle(CS x, CS y, CS width, CS height, const color_t color) {
	const vertex_t vertices[] = {
		{ x, y, color },
		{ x + width, y, color },
		{ x, y + height, color },
		{ x + width, y + height, color }
	};

	device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(vertex_t));
}

void c_renderer::render_line(CS x, CS y, CS x2, CS y2, const color_t color) {
	const vertex_t vertices[] = {
		{ x, y, color },
		{ x2, y2, color },
	};

	device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	device->DrawPrimitiveUP(D3DPT_LINELIST, 1, vertices, sizeof(vertex_t));
}

text_size_t c_renderer::render_text(unsigned short x, unsigned short y, const unsigned int alignment, const e_text_flags flags, const std::string& str, ID3DXFont* font, color_t color) {
	RECT rect = { 0, 0, 0, 0 };
	const text_size_t text_size = calculate_text_size(str, font);
	const auto draw_text = [text_size, alignment, flags, str, font](RECT& rect, color_t& color, unsigned short x, unsigned short y) {
		const auto set_rect = [](RECT& rect, CS x, CS y) {
			SetRect(&rect, x, y, x, y);
		};

		if (flags & NONE) {
			set_rect(rect, x, y);
			font->DrawTextA(nullptr, str.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, color.dx_color());
		}
		else if (flags & DROPSHADOW) {
			set_rect(rect, x + 1, y + 1);
			font->DrawTextA(nullptr, str.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, color_t(0, 0, 0, color.a).dx_color());

			set_rect(rect, x, y);
			font->DrawTextA(nullptr, str.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, color.dx_color());
		}
		else if (flags & OUTLINE) {
			const D3DCOLOR outline_color = color_t(0, 0, 0, color.a).dx_color();

			set_rect(rect, x, y + 1);
			font->DrawTextA(nullptr, str.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, outline_color);
			set_rect(rect, x + 1, y);
			font->DrawTextA(nullptr, str.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, outline_color);
			set_rect(rect, x, y - 1);
			font->DrawTextA(nullptr, str.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, outline_color);
			set_rect(rect, x - 1, y);
			font->DrawTextA(nullptr, str.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, outline_color);

			set_rect(rect, x + 1, y);
			font->DrawTextA(nullptr, str.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, outline_color);
			set_rect(rect, x, y + 1);
			font->DrawTextA(nullptr, str.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, outline_color);
			set_rect(rect, x - 1, y);
			font->DrawTextA(nullptr, str.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, outline_color);
			set_rect(rect, x, y - 1);
			font->DrawTextA(nullptr, str.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, outline_color);

			set_rect(rect, x + 1, y + 1);
			font->DrawTextA(nullptr, str.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, outline_color);
			set_rect(rect, x - 1, y - 1);
			font->DrawTextA(nullptr, str.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, outline_color);
			set_rect(rect, x + 1, y - 1);
			font->DrawTextA(nullptr, str.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, outline_color);
			set_rect(rect, x - 1, y + 1);
			font->DrawTextA(nullptr, str.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, outline_color);

			set_rect(rect, x, y);
			font->DrawTextA(nullptr, str.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, color.dx_color());
		}
	};

	if (alignment & DEFAULT) {
		draw_text(rect, color, x, y);
		return text_size;
	}

	if (alignment & VERTICAL_TOP)
		y -= text_size.height;
	else if (alignment & VERTICAL_CENTER)
		y -= text_size.height / 2;

	if (alignment & HORIZONTAL_LEFT)
		x -= text_size.width;
	else if (alignment & HORIZONTAL_CENTER)
		x -= text_size.width / 2;

	draw_text(rect, color, x, y);
	return text_size;
}

void c_renderer::render_circle(CS x, CS y, CS radius, CS segments, const color_t color) {
	vertex_t* vertices = new vertex_t[segments + 1];

	for (int i = 0; i <= segments; i++) {
		const float step = D3DX_PI * (static_cast<float>(i) / (static_cast<float>(segments) * 0.5f));

		vertices[i] = vertex_t(
			static_cast<float>(x + radius * cos(step)),
			static_cast<float>(y - radius * sin(step)),
			color);
	}

	device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	device->DrawPrimitiveUP(D3DPT_LINESTRIP, segments, vertices, sizeof(vertex_t));

	delete[] vertices;
}

const text_size_t c_renderer::calculate_text_size(const std::string& str, ID3DXFont* font) {
	RECT rect = { 0, 0, 0, 0 };
	font->DrawTextA(nullptr, str.c_str(), -1, &rect, DT_CALCRECT, D3DCOLOR_RGBA(0, 0, 0, 0));

	return {
		static_cast<const short>(rect.right - rect.left),
		static_cast<const short>(rect.bottom - rect.top)
	};
}

c_renderer g_renderer;