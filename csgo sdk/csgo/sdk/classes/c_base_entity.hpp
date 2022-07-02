#pragma once
#include "..\..\utils\vfunc.hpp"
#include "..\interfaces\interfaces.hpp"
#include "..\netvar\netvar.hpp"
#include "..\datamap.hpp"
#include "..\matrix3x4.hpp"
#include "..\vec3.hpp"
#include "i_client_entity.hpp"

namespace csgo
{

	class c_base_entity : public i_client_entity
	{
	public:

		static __forceinline c_base_entity* get_entity_by_index( int index ) {
			return static_cast< c_base_entity* >( csgo::i::entitylist->get_client_entity( index ) );
		}

		/* other */
		datamap_t* get_data_desc_map( ) {
			typedef datamap_t* ( __thiscall * o_fn )( void* );
			return get_vfunc<o_fn>( this, 15 )( this );
		}

		datamap_t* get_pred_desc_map( ) {
			typedef datamap_t* ( __thiscall * o_fn )( void* );
			return get_vfunc<o_fn>( this, 17 )( this );
		}

		/* csgo netvars */
		NETVAR( float_t, m_flSimulationTime, "DT_BaseEntity->m_flSimulationTime" );
		NETVAR_OFFSET( float_t, m_flOldSimulationTime, "CBaseEntity->m_flSimulationTime", 0x4 );
		NETVAR( vec3_t, m_vecOrigin, "DT_BaseEntity->m_vecOrigin" );
		NETVAR( vec3_t, m_angRotation, "DT_BaseEntity->m_angRotation" );
		NETVAR( int32_t, m_nModelIndex, "DT_BaseEntity->m_nModelIndex" );
		NETVAR( int32_t, m_iTeamNum, "DT_BaseEntity->m_iTeamNum" );
		NETVAR( bool, m_bSpotted, "DT_BaseEntity->m_bSpotted" );
	};
}
