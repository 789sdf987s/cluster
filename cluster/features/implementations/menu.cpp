#include "menu.h"

void c_menu::create_context( ) {
	IMGUI_CHECKVERSION( );
	ImGui::CreateContext( );
}

void c_menu::set_style( ) {
	ImGui::StyleColorsDark( );
}

void c_menu::impl_init( HWND hwnd, IDirect3DDevice9* device ) {
	ImGui_ImplWin32_Init( hwnd );
	ImGui_ImplDX9_Init( device );
}

void c_menu::new_frame( ) {
	ImGui_ImplDX9_NewFrame( );
	ImGui_ImplWin32_NewFrame( );
	ImGui::NewFrame( );
}

void c_menu::populate_render_list( ) {
	ImGui::SetNextWindowSize( { 500, 600 }, ImGuiCond_Once );
	ImGui::SetNextWindowPos( { ImGui::GetIO( ).DisplaySize.x * 0.5f, ImGui::GetIO( ).DisplaySize.y * 0.5f }, ImGuiCond_Once, { 0.5f, 0.5f } );

	ImGui::Begin( "cluster", &is_open, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar );
	{
		SECTION_START( title_bar ) {
			ImGui::Text( "cluster" );
			ImGui::SameLine( ImGui::GetWindowWidth( ) - ImGui::CalcTextSize( "admin | lifetime" ).x - 10 );
			ImGui::Text( "admin | lifetime" );
			ImGui::Separator( );
		} SECTION_END( title_bar );
	}
	ImGui::End( );
}

void c_menu::end_frame_and_render( ) {
	ImGui::EndFrame( );
	ImGui::Render( );
	ImGui_ImplDX9_RenderDrawData( ImGui::GetDrawData( ) );
}

void c_menu::pre_reset( ) {
	ImGui_ImplDX9_InvalidateDeviceObjects( );
}

void c_menu::post_reset( ) {
	ImGui_ImplDX9_CreateDeviceObjects( );
}

void c_menu::shutdown( ) {
	ImGui_ImplDX9_Shutdown( );
	ImGui_ImplWin32_Shutdown( );
	ImGui::DestroyContext( );
}