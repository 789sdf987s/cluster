#include "menu.h"

void c_menu::create_context( ) {
	IMGUI_CHECKVERSION( );
	ImGui::CreateContext( );
}

void c_menu::setup_style( ) {
	ImGui::StyleColorsDark( );
}

void c_menu::impl_init( HWND window, IDirect3DDevice9* device ) {
	ImGui_ImplWin32_Init( window );
	ImGui_ImplDX9_Init( device );
}

void c_menu::render( ) {
	ImGui_ImplDX9_NewFrame( );
	ImGui_ImplWin32_NewFrame( );
	ImGui::NewFrame( );

	ImGui::Begin( "cluster", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings );
	{

		ImGui::End( );
	}

	ImGui::EndFrame( );
	ImGui::Render( );
	ImGui_ImplDX9_RenderDrawData( ImGui::GetDrawData( ) );
}

void c_menu::destory( ) {
	ImGui_ImplDX9_Shutdown( );
	ImGui_ImplWin32_Shutdown( );
	ImGui::DestroyContext( );
}

void c_menu::reset( bool is_pre_reset ) {
	if ( is_pre_reset )
		ImGui_ImplDX9_InvalidateDeviceObjects( );
	else
		ImGui_ImplDX9_CreateDeviceObjects( );
}
