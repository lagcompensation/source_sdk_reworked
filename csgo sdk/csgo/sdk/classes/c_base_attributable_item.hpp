#pragma once
#include "..\netvar\netvar.hpp"
#include "c_base_entity.hpp"

namespace csgo {

	// DT_BaseAttributableItem
	class c_base_attributable_item : public c_base_entity {
	public:
		/* csgo netvars */
		NETVAR( short, m_iItemDefinitionIndex, "DT_BaseAttributableItem->m_iItemDefinitionIndex" );
	};


}
