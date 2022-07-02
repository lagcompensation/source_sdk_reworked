#include "../hooks.hpp"
#include "../../features/features.hpp"
#include "../../includes.hpp"
#include "../../sdk/includes.hpp"

void __stdcall hooks::create_move( int sequence_number, float input_sample_frametime, bool active, bool& send_packet ) {
	/* call origin */
	static auto o_createmove = c_hooks.clientdll_hook.get_original< hooks::create_move_fn >( c_hooks.vtable_indexes.create_move );
	o_createmove( csgo::i::clientdll, 0, sequence_number, input_sample_frametime, active );

	auto cmd = csgo::i::input->get_user_cmd( 0, sequence_number );
	auto verified = &csgo::i::input->verified_commands[ sequence_number % 150 ];

	if ( !cmd || !cmd->command_number || !csgo::i::engine->is_in_game( ) || !csgo::g_local ) {
		return;
	}

	/* globals */
	g::cmd = cmd;
	g::sendpacket = send_packet;

	/* fix the shot when menu open : imgui issue */
	if ( menu.opened ) {
		cmd->buttons &= ~csgo::in_attack;
	}

	/* prediction related */ {
		csgo::features::prediction.start( );

		csgo::features::prediction.end( );
	}

	/* get angles */ {
		if ( g::sendpacket ) {
			g::fake_angle = cmd->viewangles;
		}
		else {
			g::real_angle = cmd->viewangles;
		}
	}

	/* anti-untrusted */ {
		cmd->viewangles.clamp( );
	}

	/* end of create_move */
	send_packet = g::sendpacket;
	verified->m_cmd = *cmd;
	verified->m_crc = cmd->get_checksum( );

}

__declspec( naked ) void __fastcall hooks::create_move_hook( void* _this, int, int sequence_number, float input_sample_frametime, bool active ) {
	__asm {
		push ebp
		mov  ebp, esp
		push ebx
		push esp
		push dword ptr[ active ]
		push dword ptr[ input_sample_frametime ]
		push dword ptr[ sequence_number ]
		call hooks::create_move
		pop  ebx
		pop  ebp
		retn 0Ch
	}
}
