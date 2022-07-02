#pragma once
#include "..\..\sdk\includes.hpp"

namespace csgo {
	namespace features {
		class engine_pred {
		public: 
			void start( );
			void end( );
		private:
			float old_curtime, old_frametime;
		};
		extern engine_pred prediction;
	}
}
