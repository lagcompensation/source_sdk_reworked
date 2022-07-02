#pragma once
#include "interfaces/interfaces.hpp"

namespace csgo {
	constexpr int time2ticks( float t ) {
		return static_cast< int >( t / i::globalvars->interval_per_tick + 0.5f );
	}

	constexpr float ticks2time( int t ) {
		return static_cast< float >( t ) * i::globalvars->interval_per_tick;
	}
}
