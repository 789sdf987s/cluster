#pragma once
#include "../../cluster/vector/vector3.h"

class preview_image_retval_t;
class image_format;
class i_material_var;
class vertex_format_t;
class material_var_flags_t;
class material_property_types_t;
class key_values;

class i_material {
public:
	virtual const char* get_name() const = 0;
	virtual const char* get_texture_group_name() const = 0;
	virtual preview_image_retval_t get_preview_image_properties(int* width, int* height, image_format* imageFormat, bool* isTranslucent) const = 0;
	virtual preview_image_retval_t get_preview_image(unsigned char* data, int width, int height, image_format imageFormat) const = 0;
	virtual int get_mapping_width() = 0;
	virtual int get_mapping_height() = 0;
	virtual int get_num_animation_frames() = 0;
	virtual bool in_material_page(void) = 0;
	virtual void get_material_offset(float* pOffset) = 0;
	virtual void get_material_scale(float* pScale) = 0;
	virtual i_material* get_material_page(void) = 0;
	virtual i_material_var* find_var(const char* varName, bool* found, bool complain = true) = 0;
	virtual void increment_reference_count(void) = 0;
	virtual void decrement_reference_count(void) = 0;
	inline void add_ref() { increment_reference_count(); }
	inline void release() { decrement_reference_count(); }
	virtual int get_enumeration_id(void) const = 0;
	virtual void get_low_res_color_sample(float s, float t, float* color) const = 0;
	virtual void recompute_state_snapshots() = 0;
	virtual bool is_translucent() = 0;
	virtual bool is_alpha_tested() = 0;
	virtual bool is_vertex_lit() = 0;
	virtual vertex_format_t get_vertex_format() const = 0;
	virtual bool has_proxy(void) const = 0;
	virtual bool uses_env_cubemap(void) = 0;
	virtual bool needs_tangent_space(void) = 0;
	virtual bool needs_power_of_two_frame_buffer_texture(bool bCheckSpecificToThisFrame = true) = 0;
	virtual bool needs_full_frame_buffer_texture(bool bCheckSpecificToThisFrame = true) = 0;
	virtual bool needs_software_skinning(void) = 0;
	virtual void alpha_modulate(float alpha) = 0;
	virtual void color_modulate(float r, float g, float b) = 0;
	virtual void set_material_var_flag(material_var_flags_t flag, bool on) = 0;
	virtual bool get_material_var_flag(material_var_flags_t flag) const = 0;
	virtual void get_reflectivity(vector3_t& reflect) = 0;
	virtual bool get_property_flag(material_property_types_t  type) = 0;
	virtual bool is_two_sided() = 0;
	virtual void set_shader(const char* pShaderName) = 0;
	virtual int get_num_passes(void) = 0;
	virtual int get_texture_memory_bytes(void) = 0;
	virtual void refresh() = 0;
	virtual bool needs_lightmap_blend_alpha(void) = 0;
	virtual bool needs_software_lighting(void) = 0;
	virtual int shader_param_count() const = 0;
	virtual i_material_var** get_shader_params(void) = 0;
	virtual bool is_error_material() const = 0;
	virtual void unused() = 0;
	virtual float get_alpha_modulation() = 0;
	virtual void get_color_modulation(float* r, float* g, float* b) = 0;
	virtual bool is_translucent_under_modulation(float fAlphaModulation = 1.0f) const = 0;
	virtual i_material_var* find_var_fast(char const* pVarName, unsigned int* pToken) = 0;
	virtual void set_shader_and_params(key_values* pKeyValues) = 0;
	virtual const char* get_shader_name() const = 0;
	virtual void delete_if_unreferenced() = 0;
	virtual bool is_sprite_card() = 0;
	virtual void call_bind_proxy(void* proxyData) = 0;
	virtual void refresh_preserving_material_vars() = 0;
	virtual bool was_reloaded_from_whitelist() = 0;
	virtual bool set_temp_excluded(bool bSet, int nExcludedDimensionLimit) = 0;
	virtual int get_reference_count() const = 0;
};
