#pragma once
#include "i_handle_entity.hpp"
#include "i_collideable.hpp"
#include "i_client_networkable.hpp"
#include "i_client_renderable.hpp"
#include "i_client_entity.hpp"
#include "c_base_entity.hpp"
#include "i_client_thinkable.hpp"

namespace csgo
{
	/* pre-define */
	class i_handle_entity;
	class i_client_unknown;
	class i_client_networkable;
	class i_client_renderable;
	class i_client_entity;
	class c_base_entity;
	class i_client_thinkable;

	class i_client_unknown : public i_handle_entity
	{
	public:
		virtual i_collideable* get_collideable( ) = 0;
		virtual i_client_networkable* get_client_networkable( ) = 0;
		virtual i_client_renderable* get_client_renderable( ) = 0;
		virtual i_client_entity* get_client_entity( ) = 0;
		virtual c_base_entity* get_base_entity( ) = 0;
		virtual i_client_thinkable* get_client_thinkable( ) = 0;
		virtual void* get_client_alpha_property( ) = 0;
	};
}
