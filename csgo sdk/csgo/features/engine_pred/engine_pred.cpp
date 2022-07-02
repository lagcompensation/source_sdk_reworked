#include "engine_pred.hpp"

namespace csgo {
	namespace features {
		engine_pred prediction;

		void engine_pred::start( ) {
			static int m_tickbase;
			static c_usercmd* m_lastcmd;

			/* fixed tickbase */
			if ( !m_lastcmd || m_lastcmd->hasbeenpredicted )
				m_tickbase = csgo::g_local->m_nTickBase( );
			else
				m_tickbase++;

			m_lastcmd = g::cmd;


			/* restore curtime */
			old_curtime = csgo::i::globalvars->curtime;
			old_frametime = csgo::i::globalvars->frame_time;

			/* simulate globalvars */
			csgo::i::globalvars->curtime = m_tickbase * csgo::i::globalvars->interval_per_tick;
			csgo::i::globalvars->frame_time = csgo::i::globalvars->interval_per_tick;

			/* predict errors */
			csgo::i::movement->start_track_prediction_errors( csgo::g_local );

			/* get move data */
			c_movedata data;
			memset( &data, 0, sizeof( c_movedata ) );

			/* fix movement/etc. */
			csgo::i::move_helper->set_host( csgo::g_local );
			csgo::i::prediction->setup_move( csgo::g_local, g::cmd, csgo::i::move_helper, &data );
			csgo::i::movement->process_movement( csgo::g_local, &data );
			csgo::i::prediction->finish_move( csgo::g_local, g::cmd, &data );

			/* update accuracy ( helpful for ragebot ) */
			if ( csgo::g_local->get_active_weapon( ) )
				csgo::g_local->get_active_weapon( )->update_accuracy_penalty( );

		}


		void engine_pred::end( ) {

			/* stop predicting */
			csgo::i::movement->finish_track_prediction_errors( csgo::g_local );
			csgo::i::move_helper->set_host( nullptr );

			/* restore globalvars */
			csgo::i::globalvars->curtime = old_curtime;
			csgo::i::globalvars->frame_time = old_frametime;

		}
	}
}

