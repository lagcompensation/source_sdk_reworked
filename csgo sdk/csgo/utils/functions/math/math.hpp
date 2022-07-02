#pragma once
#include "..\..\..\includes.hpp"

namespace csgo {
	constexpr auto M_PI = 3.14159265358979f;
	class math {
	public:
		void sin_cos( float rad, float* sine, float* cosine );
		float normalize_yaw( float yaw );
		void clamp_angles( vec3_t& ang );
		float rad2deg( float rad );
		float deg2rad( float deg );
		float grd_to_bog( float grd );
		void angle_vectors( const vec3_t& angles, vec3_t& forward );
		void angle_vectors( const vec3_t& angles, vec3_t& forward, vec3_t& right, vec3_t& up );
		void angle_vectors( const vec3_t& angles, vec3_t* forward = nullptr, vec3_t* right = nullptr, vec3_t* up = nullptr );
	};
	extern math c_math;
}
