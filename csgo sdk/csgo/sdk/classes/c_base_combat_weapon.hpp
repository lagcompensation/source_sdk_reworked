#pragma once
#include "..\..\utils\vfunc.hpp"
#include "..\netvar\netvar.hpp"
#include "c_base_attributable_item.hpp"

namespace csgo {
	// DT_BaseCombatWeapon
	class c_base_combat_weapon : public c_base_attributable_item {
	public:

		/* other */

		float get_inaccuracy( ) {
			return get_vfunc<float( __thiscall* )( void* )>( this, 483 )( this );
		}

		float get_spread( ) {
			return get_vfunc<float( __thiscall* )( void* )>( this, 453 )( this );
		}

		void update_accuracy_penalty( ) {
			get_vfunc<void( __thiscall* )( void* )>( this, 484 )( this );
		}

		NETVAR( float_t, m_fAccuracyPenalty, "DT_WeaponCSBase->m_fAccuracyPenalty" );
		NETVAR( float_t, m_fLastShotTime, "DT_WeaponCSBase->m_fLastShotTime" );
		NETVAR( float_t, m_flPostponeFireReadyTime, "DT_BaseCombatWeapon->m_flPostponeFireReadyTime" );

		/* DT_WeaponCSBaseGun */
		NETVAR( int32_t, m_zoomLevel, "DT_WeaponCSBaseGun->m_zoomLevel" );
		NETVAR( int32_t, m_iBurstShotsRemaining, "DT_WeaponCSBaseGun->m_iBurstShotsRemaining" );

		/* csgo netvars */
		NETVAR( int32_t, m_iClip1, "DT_BaseCombatWeapon->m_iClip1" );
		NETVAR( int32_t, m_flNextPrimaryAttack, "DT_BaseCombatWeapon->m_flNextPrimaryAttack" );
		NETVAR( int32_t, m_flNextSecondaryAttack, "DT_BaseCombatWeapon->m_flNextSecondaryAttack" );
   
	};
}
