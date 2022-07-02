#pragma once

namespace csgo {
	class c_globalvars {
	public:
		float real_time; // 0x0000
		int frame_count; // 0x0004
		float absolute_frame_time; // 0x0008
		float absolute_frame_start_time_std_dev; // 0x000C
		float curtime; // 0x0010
		float frame_time; // 0x0014
		int max_clients; // 0x0018
		int tick_count; // 0x001C
		float interval_per_tick; // 0x0020
		float interpolation_amount; // 0x0024
		int sim_ticks_this_frame; // 0x0028
		int network_protocol; // 0x002C
		void* save_data; // 0x0030
		bool m_client; // 0x0031
		bool m_remote_client; // 0x0032
	private:
		int timestamp_networking_base;
		int timestamp_randomize_window;
	};
}
