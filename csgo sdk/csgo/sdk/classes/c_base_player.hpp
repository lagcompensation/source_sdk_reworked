#pragma once
#include "..\netvar\netvar.hpp"
#include "..\vec3.hpp"
#include "..\matrix3x4.hpp"
#include "..\..\utils\vfunc.hpp"
#include "..\..\utils\utils.hpp"
#include "..\interfaces\interfaces.hpp"

#include "c_base_entity.hpp"
#include "c_base_combat_weapon.hpp"

namespace csgo
{
	/* pre-define */
	class c_base_player;

	/* other enums */
	enum class_id : int {
		class_id_ai_base_npc = 0,
		class_id_c_ak47,
		class_id_base_animating,
		class_id_base_animating_overlay,
		class_id_base_attributable_item,
		class_id_base_button,
		class_id_base_combat_character,
		class_id_base_combat_weapon,
		class_id_base_cs_grenade,
		class_id_base_cs_grenade_projectile,
		class_id_base_door,
		class_id_base_entity,
		class_id_base_flex,
		class_id_base_grenade,
		class_id_base_particle_entity,
		class_id_base_player,
		class_id_base_prop_door,
		class_id_base_team_objective_resource,
		class_id_base_temp_entity,
		class_id_base_toggle,
		class_id_base_trigger,
		class_id_base_view_model,
		class_id_base_physics_trigger,
		class_id_base_weapon_world_model,
		class_id_beam,
		class_id_beam_spot_light,
		class_id_bone_follower,
		class_id_br_c4_target,
		class_id_breach_charge,
		class_id_breach_charge_projectile,
		class_id_breakable_prop,
		class_id_breakable_surface,
		class_id_bump_mine,
		class_id_bump_mine_projectile,
		class_id_c_c4,
		class_id_cascade_light,
		class_id_chicken,
		class_id_color_correction,
		class_id_color_correctionv_olume,
		class_id_cs_game_rules_proxy,
		class_id_cs_player,
		class_id_cs_player_resource,
		class_id_cs_ragdoll,
		class_id_cs_team,
		class_id_danger_zone,
		class_id_danger_zone_controller,
		class_id_deagle,
		class_id_decoy_grenade,
		class_id_decoy_projectile,
		class_id_drone,
		class_id_drone_gun,
		class_id_dynamic_light,
		class_id_dynamic_prop,
		class_id_econ_entity,
		class_id_econ_wearable,
		class_id_embers,
		class_id_entity_dissolve,
		class_id_entity_flame,
		class_id_entity_freezing,
		class_id_entity_particletrail,
		class_id_env_ambient_light,
		class_id_env_detail_controller,
		class_id_env_dof_controller,
		class_id_env_gas_canister,
		class_id_env_particle_script,
		class_id_env_projected_texture,
		class_id_env_quadratic_beam,
		class_id_env_screen_effect,
		class_id_env_screen_overlay,
		class_id_env_tonemap_controller,
		class_id_env_wind,
		class_id_fe_player_decal,
		class_id_fire_cracker_blast,
		class_id_fire_smoke,
		class_id_fire_trail,
		class_id_fish,
		class_id_fists,
		class_id_flashbang,
		class_id_fog_controller,
		class_id_footstep_control,
		class_id_func_dust,
		class_id_func_lod,
		class_id_func_area_portal_window,
		class_id_func_brush,
		class_id_func_conveyor,
		class_id_func_ladder,
		class_id_func_monitor,
		class_id_func_move_linear,
		class_id_func_occluder,
		class_id_func_reflective_glass,
		class_id_func_rotating,
		class_id_func_smoke_volume,
		class_id_func_track_train,
		class_id_game_rules_proxy,
		class_id_grass_burn,
		class_id_handle_test,
		class_id_he_grenade,
		class_id_hostage,
		class_id_hostage_carriable_prop,
		class_id_incendiary_grenade,
		class_id_inferno,
		class_id_info_ladder_dismount,
		class_id_info_map_region,
		class_id_info_overlay_accessor,
		class_id_item_healthshot,
		class_id_item_cash,
		class_id_item_dogtags,
		class_id_knife,
		class_id_knife_gg,
		class_id_light_glow,
		class_id_material_modify_control,
		class_id_melee,
		class_id_molotov_grenade,
		class_id_molotov_projectile,
		class_id_movie_display,
		class_id_paradrop_chopper,
		class_id_particle_fire,
		class_id_particle_performance_monitor,
		class_id_particle_system,
		class_id_phys_box,
		class_id_phys_box_multiplayer,
		class_id_physics_prop,
		class_id_physics_prop_multiplayer,
		class_id_phys_magnet,
		class_id_phys_prop_ammo_box,
		class_id_phys_prop_loot_crate,
		class_id_phys_prop_radar_jammer,
		class_id_phys_prop_weapon_upgrade,
		class_id_planted_c4,
		class_id_plasma,
		class_id_player_ping,
		class_id_player_resource,
		class_id_point_camera,
		class_id_point_commentarynode,
		class_id_point_worldtext,
		class_id_pose_controller,
		class_id_post_process_controller,
		class_id_precipitation,
		class_id_precipitation_blocker,
		class_id_predicted_view_model,
		class_id_prop_hallucination,
		class_id_prop_counter,
		class_id_prop_door_rotating,
		class_id_prop_jeep,
		class_id_prop_vehicle_driveable,
		class_id_ragdoll_manager,
		class_id_ragdoll_prop,
		class_id_ragdoll_prop_attached,
		class_id_rope_key_frame,
		class_id_scar17,
		class_id_scene_entity,
		class_id_sensor_grenade,
		class_id_sensor_grenade_projectile,
		class_id_shadow_control,
		class_id_slideshow_display,
		class_id_smoke_grenade,
		class_id_smoke_grenade_projectile,
		class_id_smoke_stack,
		class_id_snowball,
		class_id_snowball_pile,
		class_id_snowball_projectile,
		class_id_spatial_entity,
		class_id_spotlight_end,
		class_id_sprite,
		class_id_sprite_oriented,
		class_id_sprite_trail,
		class_id_statue_prop,
		class_id_steam_jet,
		class_id_sun,
		class_id_sun_light_shadow_control,
		class_id_survival_spawn_chopper,
		class_id_tablet,
		class_id_team,
		class_id_team_play_round_based_rules_proxy,
		class_id_te_armor_ricochet,
		class_id_te_base_beam,
		class_id_te_beam_ent_point,
		class_id_te_beam_ents,
		class_id_te_beam_follow,
		class_id_te_beam_laser,
		class_id_te_beam_points,
		class_id_te_beam_ring,
		class_id_te_beam_ring_point,
		class_id_te_beam_spline,
		class_id_te_blood_sprite,
		class_id_te_blood_stream,
		class_id_te_break_model,
		class_id_te_bsp_decal,
		class_id_te_bubbles,
		class_id_te_bubble_trail,
		class_id_te_client_projectile,
		class_id_te_decal,
		class_id_te_dust,
		class_id_te_dynamic_light,
		class_id_te_effect_dispatch,
		class_id_te_energy_splash,
		class_id_te_explosion,
		class_id_te_fire_bullets,
		class_id_te_fizz,
		class_id_te_foot_print_decal,
		class_id_te_foundry_helpers,
		class_id_te_gauss_explosion,
		class_id_te_glow_sprite,
		class_id_te_impact,
		class_id_te_kill_player_attachments,
		class_id_te_large_funnel,
		class_id_te_metal_sparks,
		class_id_te_muzzle_flash,
		class_id_te_particle_system,
		class_id_te_physics_prop,
		class_id_te_plant_bomb,
		class_id_te_player_animevent,
		class_id_te_player_decal,
		class_id_te_projected_decal,
		class_id_te_radio_icon,
		class_id_te_shatter_surface,
		class_id_te_show_line,
		class_id_te_sla,
		class_id_te_smoke,
		class_id_te_sparks,
		class_id_te_sprite,
		class_id_te_sprite_spray,
		class_id_test_proxytoggle_networkable,
		class_id_testtraceline,
		class_id_teworlddecal,
		class_id_trigger_player_movement,
		class_id_trigger_sound_operator,
		class_id_vgui_screen,
		class_id_vote_controller,
		class_id_water_bullet,
		class_id_water_bod_control,
		class_id_weapon_aug,
		class_id_weapon_awp,
		class_id_weapon_base_item,
		class_id_weapon_bizon,
		class_id_weapon_cs_base,
		class_id_weapon_cs_base_gun,
		class_id_weapon_cycler,
		class_id_weapon_elite,
		class_id_weapon_famas,
		class_id_weapon_five_seven,
		class_id_weapon_g3sg1,
		class_id_weapon_galil,
		class_id_weapon_galil_ar,
		class_id_weapon_glock,
		class_id_weapon_hkp2000,
		class_id_weapon_m249,
		class_id_weapon_m3,
		class_id_weapon_m4a1,
		class_id_weapon_mac10,
		class_id_weapon_mag7,
		class_id_weapon_mp5_navy,
		class_id_weapon_mp7,
		class_id_weapon_mp9,
		class_id_weapon_negev,
		class_id_weapon_nova,
		class_id_weapon_p228,
		class_id_weapon_p250,
		class_id_weapon_p90,
		class_id_weapon_sawedoff,
		class_id_weapon_scar20,
		class_id_weapon_scout,
		class_id_weapon_sg550,
		class_id_weapon_sg552,
		class_id_weapon_sg556,
		class_id_weapon_shield,
		class_id_weapon_ssg08,
		class_id_weapon_taser,
		class_id_weapon_tec9,
		class_id_weapon_tmp,
		class_id_weapon_ump45,
		class_id_weapon_usp,
		class_id_weapon_xm1014,
		class_id_world,
		class_id_world_vgui_text,
		class_id_dust_trail,
		class_id_movie_explosion,
		class_id_particle_smoke_grenade,
		class_id_rocket_trail,
		class_id_smoke_trail,
		class_id_spore_explosion,
		class_id_spore_trail
	};

	enum class movetypes {
		movetype_none = 0,
		movetype_isometric,
		movetype_walk,
		movetype_step,
		movetype_fly,
		movetype_flygravity,
		movetype_vphysics,
		movetype_push,
		movetype_noclip,
		movetype_ladder,
		movetype_observer,
		movetype_custom,
		movetype_last = movetype_custom,
		movetype_max_bits = 4
	};

	enum entityflags : int {
		fl_onground = ( 1 << 0 ),
		fl_ducking = ( 1 << 1 ),
		fl_waterjump = ( 1 << 2 ),
		fl_ontrain = ( 1 << 3 ),
		fl_inrain = ( 1 << 4 ),
		fl_frozen = ( 1 << 5 ),
		fl_atcontrols = ( 1 << 6 ),
		fl_client = ( 1 << 7 ),
		fl_fakeclient = ( 1 << 8 ),
		max_entityflags
	};

	class c_bone_acessor {
	public:
		int get_readable( ) {
			return m_readable;
		}

		void set_readable( int flags ) {
			m_readable = flags;
		}

		int get_writeable( ) {
			return m_writeable;
		}

		void set_writeable( int flags ) {
			m_writeable = flags;
		}

		const matrix3x4_t& get_bone( int bone ) const {
			return m_bones[ bone ];
		}

		matrix3x4_t& get_bone_for_write( int bone ) {
			return m_bones[ bone ];
		}

		matrix3x4_t* get_bone_arr_for_write( ) const {
			return m_bones;
		};

		void set_bone_arr_for_write( matrix3x4_t* bone ) {
			m_bones = bone;
		}

	private:
		const void* m_animating;
		matrix3x4_t* m_bones;
		int m_readable;
		int m_writeable;
	};

	struct animstate_pose_param_cache_t {
		std::uint8_t pad_0x0[ 0x4 ]; //0x0
		std::uint32_t m_idx; //0x4 
		char* m_name; //0x8

		void set_value( c_base_player* e, float val );
	};

	class animstate_t {
	public:
		std::uint8_t pad_0x0000[ 0x4 ]; //0x0000
		bool m_force_update; //0x0005 
		std::uint8_t pad_0x0006[ 0x5A ]; //0x0006
		c_base_player* m_entity; //0x0060 
		c_base_combat_weapon* m_weapon; //0x0064 
		c_base_combat_weapon* m_last_weapon; //0x0068 
		float m_last_clientside_anim_update; //0x006C 
		uint32_t m_last_clientside_anim_framecount; //0x0070 
		float m_last_clientside_anim_update_time_delta; //0x0074 
		float m_eye_yaw; //0x0078 
		float m_pitch; //0x007C 
		float m_abs_yaw; //0x0080 
		float m_feet_yaw; //0x0084 
		float m_body_yaw; //0x0088 
		float m_body_yaw_clamped; //0x008C 
		float m_feet_vel_dir_delta; //0x0090 
		uint8_t pad_0x0094[ 0x4 ]; //0x0094
		float m_feet_cycle; //0x0098 
		float m_feet_yaw_rate; //0x009C 
		uint8_t pad_0x00A0[ 0x4 ]; //0x00A0
		float m_duck_amount; //0x00A4 
		float m_landing_duck_additive; //0x00A8 
		uint8_t pad_0x00AC[ 0x4 ]; //0x00AC
		vec3_t m_origin; //0x00B0 
		vec3_t m_old_origin; //0x00BC 
		vec2_t m_vel2d; //0x00C8 
		uint8_t pad_0x00D0[ 0x10 ]; //0x00D0
		vec2_t m_last_accelerating_vel; //0x00E0 
		uint8_t pad_0x00E8[ 0x4 ]; //0x00E8
		float m_speed2d; //0x00EC 
		float m_up_vel; //0x00F0 
		float m_speed_normalized; //0x00F4 
		float m_run_speed; //0x00F8 
		float m_unk_feet_speed_ratio; //0x00FC 
		float m_time_since_move; //0x0100 
		float m_time_since_stop; //0x0104 
		bool m_on_ground; //0x0108 
		bool m_hit_ground; //0x0109 
		uint8_t pad_0x010A[ 0x4 ]; //0x010A
		float m_time_in_air; //0x0110 
		uint8_t pad_0x0114[ 0x6 ]; //0x0114
		float m_ground_fraction; //0x011C 
		uint8_t pad_0x0120[ 0x2 ]; //0x0120
		float m_unk_fraction; //0x0124 
		uint8_t pad_0x0128[ 0xC ]; //0x0128
		bool m_moving; //0x0134
		uint8_t pad_0x0135[ 0x7B ]; //0x0135
		animstate_pose_param_cache_t m_lean_yaw_pose; //0x1B0
		animstate_pose_param_cache_t m_speed_pose; //0x01BC
		animstate_pose_param_cache_t m_ladder_speed_pose; //0x01C8
		animstate_pose_param_cache_t m_ladder_yaw_pose; //0x01D4
		animstate_pose_param_cache_t m_move_yaw_pose; //0x01E0
		animstate_pose_param_cache_t m_run_pose; //0x01EC 
		animstate_pose_param_cache_t m_body_yaw_pose; //0x01F8
		animstate_pose_param_cache_t m_body_pitch_pose; //0x0204
		animstate_pose_param_cache_t m_dead_yaw_pose; //0x0210
		animstate_pose_param_cache_t m_stand_pose; //0x021C
		animstate_pose_param_cache_t m_jump_fall_pose; //0x0228
		animstate_pose_param_cache_t m_aim_blend_stand_idle_pose; //0x0234
		animstate_pose_param_cache_t m_aim_blend_crouch_idle_pose; //0x0240
		animstate_pose_param_cache_t m_strafe_yaw_pose; //0x024C
		animstate_pose_param_cache_t m_aim_blend_stand_walk_pose; //0x0258
		animstate_pose_param_cache_t m_aim_blend_stand_run_pose; //0x0264
		animstate_pose_param_cache_t m_aim_blend_crouch_walk_pose; //0x0270
		animstate_pose_param_cache_t m_move_blend_walk_pose; //0x027C
		animstate_pose_param_cache_t m_move_blend_run_pose; //0x0288
		animstate_pose_param_cache_t m_move_blend_crouch_pose; //0x0294
		uint8_t pad_0x02A0[ 0x4 ]; //0x02A0
		float m_vel_unk; //0x02A4 
		uint8_t pad_0x02A8[ 0x86 ]; //0x02A8
		float m_min_yaw; //0x0330 
		float m_max_yaw; //0x0334 
		float m_max_pitch; //0x0338 
		float m_min_pitch; //0x033C

		void reset( );
		void update( vec3_t& ang );
	}; //Size=0x0340

	struct animlayer_t {
		char pad_0x01[ 0x14 ];
		int	m_order;
		int	m_sequence;
		float m_previous_cycle;
		float m_weight;
		float m_weight_delta_rate;
		float m_playback_rate;
		float m_cycle;
		void* m_owner;
		char pad_0x02[ 0x4 ];
	};

	class dt_csplayer
	{
	public:
		NETVAR( vec3_t, m_angEyeAngles, "DT_CSPlayer->m_angEyeAngles[0]" );
		NETVAR( int32_t, m_iAccount, "DT_CSPlayer->m_iAccount" );         
		NETVAR( int32_t, m_ArmorValue, "DT_CSPlayer->m_ArmorValue" );                   
		NETVAR( bool, m_bHasDefuser, "DT_CSPlayer->m_bHasDefuser" );
		NETVAR( bool, m_bIsScoped, "DT_CSPlayer->m_bIsScoped" );              
		NETVAR( bool, m_bGunGameImmunity, "DT_CSPlayer->m_bGunGameImmunity" );
		NETVAR( bool, m_bHasHelmet, "DT_CSPlayer->m_bHasHelmet" );
		NETVAR( bool, m_bHasHeavyArmor, "DT_CSPlayer->m_bHasHeavyArmor" );     
		NETVAR( float_t, m_flFlashDuration, "DT_CSPlayer->m_flFlashDuration" );
		NETVAR( float_t, m_flFlashMaxAlpha, "DT_CSPlayer->m_flFlashMaxAlpha" );
		NETVAR( float_t, m_flLowerBodyYawTarget, "DT_CSPlayer->m_flLowerBodyYawTarget" );
		NETVAR( int32_t, m_iShotsFired, "DT_CSPlayer->m_iShotsFired" );
	};
	class c_base_player : public dt_csplayer, public c_base_entity {
	public:

		static __forceinline c_base_player* get_player_by_index( int index ) {
			return static_cast< c_base_player* >( get_entity_by_index( index ) );
		}

		/* DT_BaseAnimating */
		NETVAR( bool, m_bClientSideAnimation, "DT_BaseAnimating->m_bClientSideAnimation" );
		std::array<float, 24> & m_flPoseParameter( ) {
			static int _m_flPoseParameter = netvars::get_offset( "DT_BaseAnimating->m_flPoseParameter" );
			return *( std::array<float, 24>* )( uintptr_t( this ) + _m_flPoseParameter );
		}

		/* datamap */
		float_t m_flNextAttack( ) {
			static unsigned int _m_flNextAttack = c_utils.find_in_data_map( get_pred_desc_map( ), "m_flNextAttack" );
			return *( float_t* ) ( ( uintptr_t ) this + _m_flNextAttack );
		}

		int32_t m_nMoveType( ) {
			static unsigned int _m_nMoveType = c_utils.find_in_data_map( get_pred_desc_map( ), "m_nMoveType" );
			return *( int32_t* ) ( ( uintptr_t ) this + _m_nMoveType );
		}

		uint32_t& m_iEFlags( )
		{
			static unsigned int _m_iEFlags = c_utils.find_in_data_map( get_pred_desc_map( ), "m_iEFlags" );
			return *( uint32_t* ) ( ( uintptr_t ) this + _m_iEFlags );
		}

		/* others */
		bool is_alive( ) {
			return ( this->m_iHealth( ) > 0 && this->m_lifeState( ) == 0 );
		}

		float_t m_flSpawnTime( ){
			return *( float_t* ) ( ( uintptr_t ) this + 0xA360 );
		}

		vec3_t get_eye_pos( ) {
			return m_vecOrigin( ) + m_vecViewOffset( );
		}

		animlayer_t* anim_overlays( ) {
			return *( animlayer_t * * ) ( ( uintptr_t ) this + 0x2990 );
		}

		animstate_t* get_animstate( ) {
			return *( animstate_t * * ) ( ( uintptr_t ) this + 0x9960 ); //0x3914
		}

		vec3_t& tp_angles( ) {
			static int m_tp_angles = ( netvars::get_offset( "DT_BasePlayer->deadflag" ) + 0x4 ); // 0x31D4 + 0x4
			return *( vec3_t* ) ( ( uintptr_t ) this + m_tp_angles );
		}

		vec3_t& get_abs_origin( ) {
			typedef vec3_t& ( __thiscall * o_fn )( void* );
			return get_vfunc< o_fn >( this, 10 )( this );
		}

		vec3_t& get_abs_angles( ) {
			typedef vec3_t& ( __thiscall * o_fn )( void* );
			return get_vfunc< o_fn >( this, 11 )( this );
		}

		void set_abs_origin( const vec3_t& origin )
		{
			using o_fn = void( __thiscall* )( void*, const vec3_t & origin );
			static o_fn set_abs_origin = ( o_fn ) csgo::c_utils.pattern_scan( GetModuleHandleA( "client.dll" ), "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8" );
			set_abs_origin( this, origin );
		}

		void set_abs_angles( vec3_t angles ) {
			using o_fn = void( __thiscall* )( c_base_player*, const vec3_t & angles );
			static o_fn set_abs_angles = ( o_fn ) csgo::c_utils.pattern_scan_byte( GetModuleHandleA( "client.dll" ), ( BYTE* )"\x55\x8B\xEC\x83\xE4\xF8\x83\xEC\x64\x53\x56\x57\x8B\xF1\xE8", "xxxxxxxxxxxxxxx" );
			set_abs_angles( this, angles );
		}

		void update_client_side_anim( ) {
			typedef void( __thiscall * o_fn )( void* );
			return get_vfunc<o_fn>( this, 224 )( this );
		}

		int active_weapon_index( ) {
			static int _m_hActiveWeapon = netvars::get_offset( "DT_BaseCombatCharacter->m_hActiveWeapon" ); // 0x2EF8
			return *( int* ) ( uintptr_t( this ) + _m_hActiveWeapon ) & 0xFFF;
		}

		c_base_combat_weapon* get_active_weapon( ) {
			return ( c_base_combat_weapon* ) ( i::entitylist->get_client_entity( this->active_weapon_index( ) ) );
		}

		void invalidate_bone_cache( ) {
			static auto model_bone_counter = csgo::c_utils.pattern_scan( GetModuleHandleA( "client.dll" ), "80 3D ?? ?? ?? ?? ?? 74 16 A1 ?? ?? ?? ?? 48 C7 81" ) + 10;
			*( uint32_t* ) ( ( uintptr_t ) ( this ) + 0x2924 ) = -FLT_MAX; // m_flLastBoneSetupTime = -FLT_MAX
			*( uint32_t* ) ( ( uintptr_t ) ( this ) + 0x2690 ) = **( unsigned long** ) model_bone_counter - 1; // m_iMostRecentModelBoneCounter = g_iModelBoneCounter - 1;
		}

		c_bone_acessor* get_bone_acessor( ) {
			return ( c_bone_acessor* ) ( ( uintptr_t ) this + 0x290C );
		}

		NETVAR( int32_t, m_iHealth, "DT_BasePlayer->m_iHealth" );
		NETVAR( int32_t, m_lifeState, "DT_BasePlayer->m_lifeState" );
		NETVAR( float_t, m_flMaxspeed, "DT_BasePlayer->m_flMaxspeed" );
		NETVAR( int32_t, m_fFlags, "DT_BasePlayer->m_fFlags" );
		NETVAR( float, m_flDuckAmount, "DT_BasePlayer->m_flDuckAmount" );
		NETVAR( float, m_flDuckSpeed, "DT_BasePlayer->m_flDuckSpeed" );
		NETVAR( vec3_t, m_vecViewOffset, "DT_BasePlayer->m_vecViewOffset[0]" );
		NETVAR( int32_t, m_nTickBase, "DT_BasePlayer->m_nTickBase" );
		NETVAR( vec3_t, m_vecVelocity, "DT_BasePlayer->m_vecVelocity[0]" );
		NETVAR( vec3_t, m_viewPunchAngle, "DT_BasePlayer->m_viewPunchAngle" );
		NETVAR( vec3_t, m_aimPunchAngle, "DT_BasePlayer->m_aimPunchAngle" );
	};

	/* local player */
	class c_local_player
	{
		friend bool operator==( const c_local_player& lhs, void* rhs );
	public:
		c_local_player( ) : m_local( nullptr ) {}

		operator bool( ) const { return *m_local != nullptr; }
		operator c_base_player* ( ) const { return *m_local; }

		c_base_player* operator->( ) { return *m_local; }

	private:
		c_base_player** m_local;
	};

	inline c_local_player g_local;

}
