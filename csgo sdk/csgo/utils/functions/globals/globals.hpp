#pragma once

/* pre-define */
class vec3_t;
namespace csgo {
	class c_base_player;
	class c_usercmd;
}

namespace g {
	extern csgo::c_usercmd* cmd;
	extern bool sendpacket;
	extern vec3_t real_angle;
	extern vec3_t fake_angle;
}
