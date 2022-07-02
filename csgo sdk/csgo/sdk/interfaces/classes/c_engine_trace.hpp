#pragma once
#include <xmmintrin.h>
#include "..\..\matrix3x4.hpp"
#include "..\..\vec3.hpp"


namespace csgo
{
	enum contents : uint32_t {
		contents_empty = 0,
		contents_solid = 0x1,
		contents_window = 0x2,
		contents_aux = 0x4,
		contents_grate = 0x8,
		contents_slime = 0x10,
		contents_water = 0x20,
		contents_blocklos = 0x40,
		contents_opaque = 0x80,
		last_visible_contents = contents_opaque,
		all_visible_contents = ( last_visible_contents | ( last_visible_contents - 1 ) ),
		contents_testfogvolume = 0x100,
		contents_unused = 0x200,
		contents_blocklight = 0x400,
		contents_team1 = 0x800,
		contents_team2 = 0x1000,
		contents_ignore_nodraw_opaque = 0x2000,
		contents_moveable = 0x4000,
		contents_areaportal = 0x8000,
		contents_playerclip = 0x10000,
		contents_monsterclip = 0x20000,
		contents_current_0 = 0x40000,
		contents_current_90 = 0x80000,
		contents_current_180 = 0x100000,
		contents_current_270 = 0x200000,
		contents_current_up = 0x400000,
		contents_current_down = 0x800000,
		contents_origin = 0x1000000,
		contents_monster = 0x2000000,
		contents_debris = 0x4000000,
		contents_detail = 0x8000000,
		contents_translucent = 0x10000000,
		contents_ladder = 0x20000000,
		contents_hitbox = 0x40000000
	};

	enum mask : uint32_t {
		mask_all = ( 0xffffffff ),
		mask_solid = ( contents_solid | contents_moveable | contents_window | contents_monster | contents_grate ),
		mask_playersolid = ( contents_solid | contents_moveable | contents_playerclip | contents_window | contents_monster | contents_grate ),
		mask_npcsolid = ( contents_solid | contents_moveable | contents_monsterclip | contents_window | contents_monster | contents_grate ),
		mask_npcfluid = ( contents_solid | contents_moveable | contents_monsterclip | contents_window | contents_monster ),
		mask_water = ( contents_water | contents_moveable | contents_slime ),
		mask_opaque = ( contents_solid | contents_moveable | contents_opaque ),
		mask_opaque_and_npcs = ( mask_opaque | contents_monster ),
		mask_blocklos = ( contents_solid | contents_moveable | contents_blocklos ),
		mask_blocklos_and_npcs = ( mask_blocklos | contents_monster ),
		mask_visible = ( mask_opaque | contents_ignore_nodraw_opaque ),
		mask_visible_and_npcs = ( mask_opaque_and_npcs | contents_ignore_nodraw_opaque ),
		mask_shot = ( contents_solid | contents_moveable | contents_monster | contents_window | contents_debris | contents_hitbox ),
		mask_shot_brushonly = ( contents_solid | contents_moveable | contents_window | contents_debris ),
		mask_shot_hull = ( contents_solid | contents_moveable | contents_monster | contents_window | contents_debris | contents_grate ),
		mask_shot_portal = ( contents_solid | contents_moveable | contents_window | contents_monster ),
		mask_solid_brushonly = ( contents_solid | contents_moveable | contents_window | contents_grate ),
		mask_playersolid_brushonly = ( contents_solid | contents_moveable | contents_window | contents_playerclip | contents_grate ),
		mask_npcsolid_brushonly = ( contents_solid | contents_moveable | contents_window | contents_monsterclip | contents_grate ),
		mask_npcworldstatic = ( contents_solid | contents_window | contents_monsterclip | contents_grate ),
		mask_npcworldstatic_fluid = ( contents_solid | contents_window | contents_monsterclip ),
		mask_splitareaportal = ( contents_water | contents_slime ),
		mask_current = ( contents_current_0 | contents_current_90 | contents_current_180 | contents_current_270 | contents_current_up | contents_current_down ),
		mask_deadsolid = ( contents_solid | contents_playerclip | contents_window | contents_grate )
	};

	class i_handle_entity;
	class i_client_entity;
	class i_collideable;

	struct plane_t {
		vec3_t m_normal;
		float m_dist;
		uint8_t m_type;
		uint8_t m_sign_bits;
		uint8_t pad[ 2 ];
	};

	struct surface_t {
		const char* m_name;
		short m_surface_props;
		uint8_t m_flags;
	};

	class base_trace_t {
	public:
		vec3_t m_startpos;
		vec3_t m_endpos;
		plane_t m_plane;

		float m_fraction;

		uint32_t m_contents;
		uint16_t m_disp_flags;

		bool m_allsolid;
		bool m_startsolid;
	};

	class trace_t : public base_trace_t {
	public:
		int get_entity_index( ) const { }

		bool did_hit( ) const {
			return m_fraction < 1 || m_allsolid || m_startsolid;
		}

		bool is_visible( ) const {
			return m_fraction > 0.97f;
		}

	public:
		float m_fractionleftsolid;
		surface_t m_surface;
		int m_hitgroup;
		short m_physicsbone;
		uint16_t m_world_surface_index;
		i_client_entity* m_hit_entity;
		int m_hitbox;

		trace_t( ) { }

	private:
		trace_t( const trace_t& other ) :
			m_fractionleftsolid( other.m_fractionleftsolid ),
			m_surface( other.m_surface ),
			m_hitgroup( other.m_hitgroup ),
			m_physicsbone( other.m_physicsbone ),
			m_world_surface_index( other.m_world_surface_index ),
			m_hit_entity( other.m_hit_entity ),
			m_hitbox( other.m_hitbox ) {
			m_startpos = other.m_startpos;
			m_endpos = other.m_endpos;
			m_plane = other.m_plane;
			m_fraction = other.m_fraction;
			m_contents = other.m_contents;
			m_disp_flags = other.m_disp_flags;
			m_allsolid = other.m_allsolid;
			m_startsolid = other.m_startsolid;
		}
	};

	enum trace_type : uint32_t
	{
		trace_everything = 0,
		trace_world_only,
		trace_entities_only,
		trace_everything_filter_props
	};

	class i_trace_filter {
	public:
		virtual bool should_hit_entity( i_handle_entity* ent, uint32_t contents_mask ) = 0;
		virtual uint32_t get_trace_type( ) const = 0;
	};

	class c_trace_filter : public i_trace_filter
	{
	public:
		bool should_hit_entity( i_handle_entity* entity_handle, uint32_t contents_mask )
		{
			return ( entity_handle != skip );
		}

		uint32_t get_trace_type( ) const
		{
			return trace_type::trace_everything;
		}

		void* skip;
	};

	class c_trace_filter_no_players : public c_trace_filter
	{
	public:
		c_trace_filter_no_players( ) {}
		virtual bool should_hit_entity( i_handle_entity* entity_handle, uint32_t contents_mask ) override
		{
			return false;
		}
	};

	class c_trace_filter_one_Entity : public i_trace_filter
	{
	public:
		bool should_hit_entity( i_handle_entity* entity_handle, uint32_t contents_mask )
		{
			return ( entity_handle == entity );
		}

		uint32_t get_trace_type( ) const
		{
			return trace_type::trace_everything;
		}

		void* entity;
	};

	class c_trace_filter_skip_entity : public i_trace_filter
	{
	public:

		c_trace_filter_skip_entity( i_handle_entity* entity_handle )
		{
			skip = entity_handle;
		}

		bool should_hit_entity( i_handle_entity* entity_handle, uint32_t contents_mask )
		{
			return entity_handle != skip;
		}

		virtual uint32_t get_trace_type( ) const
		{
			return trace_type::trace_everything;
		}

		void* skip;
	};

	class c_trace_filter_world_only : public i_trace_filter
	{
	public:

		bool should_hit_entity( i_handle_entity* entity_handle, uint32_t contents_mask )
		{
			return false;
		}

		virtual uint32_t get_trace_type( ) const
		{
			return trace_type::trace_world_only;
		}

	};

	struct ray_t {
		vec3_t start;
		vec3_t delta;
		vec3_t start_offset;
		vec3_t extents;

		const matrix3x4_t* world_axis_transform{};

		bool is_ray{};
		bool is_swept{};

		void init( const vec3_t src, const vec3_t end ) {
			delta = end - src;
			is_swept = delta.length( ) != 0.f;
			extents.x = extents.y = extents.z = 0.0f;
			world_axis_transform = nullptr;
			is_ray = true;
			start_offset.x = start_offset.y = start_offset.z = 0.0f;
			start = src;
		}

		void init( vec3_t const& start, vec3_t const& end, vec3_t const& mins, vec3_t const& maxs ) {
			world_axis_transform = nullptr;
			delta = end - start;
			extents = maxs - mins;
			extents *= 0.5f;

			is_swept = delta.length_sqr( ) != 0.0f;
			is_ray = extents.length_sqr( ) < 1e-6f;

			start_offset = maxs + mins;
			start_offset *= 0.5f;
			this->start = start + start_offset;
			start_offset *= -1.0f;
		}
	};

	class c_engine_trace
	{
	public:
		virtual int get_point_contents( const vec3_t& pos, uint32_t mask = 0xffffffff /* mask_all */, i_handle_entity * ent = nullptr ) = 0; // 0
		virtual int get_point_contents_world_only( const vec3_t& pos, uint32_t mask = 0xffffffff ) = 0; // 1
		virtual int get_point_contents_collideable( i_collideable* collide, const vec3_t& pos ) = 0; // 2
		virtual void clip_ray_to_entity( const ray_t& ray, uint32_t mask, i_handle_entity* ent, trace_t* trace ) = 0; // 3
		virtual void clip_ray_to_collideable( const ray_t& ray, uint32_t mask, i_collideable* collide, trace_t* trace ) = 0; // 4
		virtual void trace_ray( const ray_t& ray, uint32_t mask, i_trace_filter* filter, trace_t* trace ) = 0; // 5
	};

}

