#include "menu.h"

void c_menu::create_context( ) {
	IMGUI_CHECKVERSION( );
	ImGui::CreateContext( );
}

void c_menu::set_style( ) {
	ImGui::StyleColorsDark( );

	ImGuiStyle* style = &ImGui::GetStyle( );
	ImVec4* colors = style->Colors;

	colors [ ImGuiCol_Text ] = ImVec4( 1.00f, 1.00f, 1.00f, 1.00f );
	colors [ ImGuiCol_TextDisabled ] = ImVec4( 0.50f, 0.50f, 0.50f, 1.00f );
	colors [ ImGuiCol_WindowBg ] = ImVec4( 0.00f, 0.00f, 0.00f, 0.78f );
	colors [ ImGuiCol_ChildBg ] = ImVec4( 0.15f, 0.15f, 0.15f, 0.6f );
	colors [ ImGuiCol_PopupBg ] = ImVec4( 0.00f, 0.00f, 0.00f, 0.78f );
	colors [ ImGuiCol_Border ] = ImVec4( 1.00f, 0.00f, 0.86f, 0.78f );
	colors [ ImGuiCol_BorderShadow ] = ImVec4( 0.00f, 0.00f, 0.00f, 0.00f );
	colors [ ImGuiCol_FrameBg ] = ImVec4( 0.18f, 0.18f, 0.18f, 1.00f );
	colors [ ImGuiCol_FrameBgHovered ] = ImVec4( 0.22f, 0.22f, 0.21f, 1.00f );
	colors [ ImGuiCol_FrameBgActive ] = ImVec4( 0.23f, 0.23f, 0.24f, 1.00f );
	colors [ ImGuiCol_TitleBg ] = ImVec4( 0.04f, 0.04f, 0.04f, 1.00f );
	colors [ ImGuiCol_TitleBgActive ] = ImVec4( 0.16f, 0.29f, 0.48f, 1.00f );
	colors [ ImGuiCol_TitleBgCollapsed ] = ImVec4( 0.00f, 0.00f, 0.00f, 0.51f );
	colors [ ImGuiCol_MenuBarBg ] = ImVec4( 0.14f, 0.14f, 0.14f, 1.00f );
	colors [ ImGuiCol_ScrollbarBg ] = ImVec4( 0.02f, 0.02f, 0.02f, 0.53f );
	colors [ ImGuiCol_ScrollbarGrab ] = ImVec4( 0.18f, 0.18f, 0.18f, 1.00f );
	colors [ ImGuiCol_ScrollbarGrabHovered ] = ImVec4( 0.20f, 0.20f, 0.19f, 1.00f );
	colors [ ImGuiCol_ScrollbarGrabActive ] = ImVec4( 0.21f, 0.21f, 0.22f, 1.00f );
	colors [ ImGuiCol_CheckMark ] = ImVec4( 1.00f, 0.00f, 0.86f, 0.78f );
	colors [ ImGuiCol_SliderGrab ] = ImVec4( 1.00f, 0.00f, 0.86f, 0.78f );
	colors [ ImGuiCol_SliderGrabActive ] = ImVec4( 1.00f, 0.14f, 0.88f, 0.78f );
	colors [ ImGuiCol_Button ] = ImVec4( 1.00f, 0.00f, 0.86f, 0.78f );
	colors [ ImGuiCol_ButtonHovered ] = ImVec4( 1.00f, 0.18f, 0.89f, 0.68f );
	colors [ ImGuiCol_ButtonActive ] = ImVec4( 1.00f, 0.33f, 0.91f, 0.78f );
	colors [ ImGuiCol_Header ] = ImVec4( 1.00f, 0.00f, 0.86f, 0.78f );
	colors [ ImGuiCol_HeaderHovered ] = ImVec4( 1.00f, 0.18f, 0.89f, 0.78f );
	colors [ ImGuiCol_HeaderActive ] = ImVec4( 1.00f, 0.33f, 0.91f, 0.78f );
	colors [ ImGuiCol_Separator ] = ImVec4( 1.00f, 0.00f, 0.86f, 0.78f );
	colors [ ImGuiCol_SeparatorHovered ] = ImVec4( 1.00f, 0.00f, 0.86f, 0.78f );
	colors [ ImGuiCol_SeparatorActive ] = ImVec4( 1.00f, 0.00f, 0.86f, 0.78f );
	colors [ ImGuiCol_ResizeGrip ] = ImVec4( 1.00f, 0.00f, 0.86f, 0.78f );
	colors [ ImGuiCol_ResizeGripHovered ] = ImVec4( 1.00f, 0.18f, 0.89f, 0.78f );
	colors [ ImGuiCol_ResizeGripActive ] = ImVec4( 1.00f, 0.33f, 0.91f, 0.78f );
	colors [ ImGuiCol_Tab ] = ImVec4( 1.00f, 0.00f, 0.86f, 0.34f );
	colors [ ImGuiCol_TabHovered ] = ImVec4( 1.00f, 0.18f, 0.89f, 0.78f );
	colors [ ImGuiCol_TabActive ] = ImVec4( 1.00f, 0.33f, 0.91f, 0.78f );
	colors [ ImGuiCol_TabUnfocused ] = ImVec4( 0.07f, 0.10f, 0.15f, 0.97f );
	colors [ ImGuiCol_TabUnfocusedActive ] = ImVec4( 0.14f, 0.26f, 0.42f, 1.00f );
	colors [ ImGuiCol_PlotLines ] = ImVec4( 0.61f, 0.61f, 0.61f, 1.00f );
	colors [ ImGuiCol_PlotLinesHovered ] = ImVec4( 1.00f, 0.43f, 0.35f, 1.00f );
	colors [ ImGuiCol_PlotHistogram ] = ImVec4( 0.90f, 0.70f, 0.00f, 1.00f );
	colors [ ImGuiCol_PlotHistogramHovered ] = ImVec4( 1.00f, 0.60f, 0.00f, 1.00f );
	colors [ ImGuiCol_TextSelectedBg ] = ImVec4( 0.26f, 0.59f, 0.98f, 0.35f );
	colors [ ImGuiCol_DragDropTarget ] = ImVec4( 1.00f, 1.00f, 0.00f, 0.90f );
	colors [ ImGuiCol_NavHighlight ] = ImVec4( 0.26f, 0.59f, 0.98f, 1.00f );
	colors [ ImGuiCol_NavWindowingHighlight ] = ImVec4( 1.00f, 1.00f, 1.00f, 0.70f );
	colors [ ImGuiCol_NavWindowingDimBg ] = ImVec4( 0.80f, 0.80f, 0.80f, 0.20f );
	colors [ ImGuiCol_ModalWindowDimBg ] = ImVec4( 0.80f, 0.80f, 0.80f, 0.35f );

	style->ChildRounding = 0.f;
	style->FrameRounding = 0.f;
	style->GrabRounding = 0.f;
	style->PopupRounding = 0.f;
	style->ScrollbarRounding = 0.f;
	style->TabRounding = 0.f;
	style->WindowRounding = 0.f;

	style->ChildBorderSize = 1.f;
	style->FrameBorderSize = 1.f;
	style->PopupBorderSize = 1.f;
	style->TabBorderSize = 1.f;
	style->WindowBorderSize = 1.f;
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
	ImGui::SetNextWindowSize( { 522.f, 600.f }, ImGuiCond_Once );
	ImGui::SetNextWindowPos( { ImGui::GetIO( ).DisplaySize.x * 0.5f, ImGui::GetIO( ).DisplaySize.y * 0.5f }, ImGuiCond_Once, { 0.5f, 0.5f } );

	ImGui::Begin( "cluster", &is_open, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize );
	{
		SECTION_START( title_bar ) {
			ImGui::SetCursorPosY( ImGui::GetCursorPosY( ) - 4.f );
			ImGui::Text( "cluster" );
			ImGui::SetCursorPosY( ImGui::GetCursorPosY( ) - 1.f );
			ImGui::Separator( );
			ImGui::NewLine( );
		} SECTION_END( title_bar );

		static unsigned short selected_tab = 0;
		SECTION_START( tabs ) {
			ImGui::PushStyleVar( ImGuiStyleVar_FrameBorderSize, 0.f );

			const auto render_tab = [ ] ( const std::string& name, bool active ) -> bool {
				ImGui::SameLine( );
				ImGui::PushStyleColor( ImGuiCol_Button, active ? ImGui::GetStyleColorVec4( ImGuiCol_ButtonActive ) : ImVec4( 0.35f, 0.35f, 0.35f, 0.75f ) );
				bool result = ImGui::ButtonEx( name.c_str( ), { 75.f, 20.f }, ImGuiButtonFlags_BackgroundLine );
				ImGui::PopStyleColor( );

				return result;
			};

			if ( render_tab( "legitbot", selected_tab == 0 ) )
				selected_tab = 0;

			if ( render_tab( "ragebot", selected_tab == 1 ) )
				selected_tab = 1;

			if ( render_tab( "visuals", selected_tab == 2 ) )
				selected_tab = 2;

			if ( render_tab( "misc", selected_tab == 3 ) )
				selected_tab = 3;

			if ( render_tab( "skins", selected_tab == 4 ) )
				selected_tab = 4;

			if ( render_tab( "extra", selected_tab == 5 ) )
				selected_tab = 5;

			ImGui::PopStyleVar( );
			ImGui::Spacing( );
			ImGui::Spacing( );
		} SECTION_END( tabs );

		const static ImVec2 window_size = ImGui::GetWindowSize( );
		SECTION_START( content ) {
			switch ( selected_tab ) {
				case 0:
					{
						SECTION_START( legitbot ) {

						} SECTION_END( legitbot );
						break;
					}
				case 1:
					{
						SECTION_START( ragebot ) {

						} SECTION_END( ragebot );
						break;
					}
				case 2:
					{
						SECTION_START( visuals ) {
							GROUPBOX_START( "players", DEFAULT_SIZE ) {
								ImGui::Checkbox( "enable##visuals_players", &g_config_system.visuals.enable );
								ImGui::Checkbox( "box", &g_config_system.visuals.box );
							} GROUPBOX_END;

							ImGui::SameLine( );

							GROUPBOX_START( "world", DEFAULT_SIZE ) {

							} GROUPBOX_END;

							ImGui::Spacing( );

							GROUPBOX_START( "removals", DEFAULT_SIZE ) {

							} GROUPBOX_END;

							ImGui::SameLine( );

							GROUPBOX_START( "misc", DEFAULT_SIZE ) {
								if ( ImGui::Button( "save" ) ) {
									if ( !g_config_system.save( "tcfg" ) )
										MessageBoxA( NULL, "", "", 0 ); //fuck
								}

								if ( ImGui::Button( "load" ) ) {
									if ( !g_config_system.load( "tcfg" ) )
										MessageBoxA( NULL, "", "", 0 ); //fuck
								}
							} GROUPBOX_END;
						} SECTION_END( visuals );
						break;
					}
				case 3:
					{
						SECTION_START( misc ) {

						} SECTION_END( misc );
						break;
					}
				case 4:
					{
						SECTION_START( music ) {

						} SECTION_END( music );
						break;
					}
				case 5:
					{
						SECTION_START( extra ) {

						} SECTION_END( extra );
						break;
					}
			}
		} SECTION_END( content );
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