#include "math.hpp"

namespace csgo {
	math c_math;

	void csgo::math::sin_cos( float rad, float* sine, float* cosine )
	{
		*sine = std::sinf( rad );
		*cosine = std::cosf( rad );
	}

	float csgo::math::normalize_yaw( float yaw )
	{
		while ( yaw > 180 )
			yaw -= 360.f;

		while ( yaw < -180 )
			yaw += 360.f;

		return yaw;
	}

	void csgo::math::clamp_angles( vec3_t& ang )
	{
		if ( ang.x > 89.0f )
			ang.x = 89.0f;
		else if ( ang.x < -89.0f )
			ang.x = -89.0f;

		if ( ang.y > 180.0f )
			ang.y = 180.0f;
		else if ( ang.y < -180.0f )
			ang.y = -180.0f;

		ang.z = 0;
	}

	float csgo::math::rad2deg( float rad ) {
		float result = rad * ( 180.0f / M_PI );
		return result;
	}

	float csgo::math::deg2rad( float deg ) {
		float result = deg * ( M_PI / 180.0f );
		return result;
	}

	float csgo::math::grd_to_bog( float grd ) {
		return ( M_PI / 180 ) * grd;
	}

	void csgo::math::angle_vectors( const vec3_t& angles, vec3_t& forward )
	{
		float sp, sy, cp, cy;

		sin_cos( deg2rad( angles[ 1 ] ), &sy, &cy );
		sin_cos( deg2rad( angles[ 0 ] ), &sp, &cp );

		forward.x = cp * cy;
		forward.y = cp * sy;
		forward.z = -sp;
	}

	void csgo::math::angle_vectors( const vec3_t& angles, vec3_t& forward, vec3_t& right, vec3_t& up )
	{
		float sr, sp, sy, cr, cp, cy;

		sin_cos( deg2rad( angles[ 1 ] ), &sy, &cy );
		sin_cos( deg2rad( angles[ 0 ] ), &sp, &cp );
		sin_cos( deg2rad( angles[ 2 ] ), &sr, &cr );

		forward.x = ( cp * cy );
		forward.y = ( cp * sy );
		forward.z = ( -sp );
		right.x = ( -1 * sr * sp * cy + -1 * cr * -sy );
		right.y = ( -1 * sr * sp * sy + -1 * cr * cy );
		right.z = ( -1 * sr * cp );
		up.x = ( cr * sp * cy + -sr * -sy );
		up.y = ( cr * sp * sy + -sr * cy );
		up.z = ( cr * cp );
	}

	void csgo::math::angle_vectors( const vec3_t& angles, vec3_t* forward, vec3_t* right, vec3_t* up )
	{
		float sp, sy, sr, cp, cy, cr;

		sin_cos( grd_to_bog( angles.x ), &sp, &cp );
		sin_cos( grd_to_bog( angles.y ), &sy, &cy );
		sin_cos( grd_to_bog( angles.z ), &sr, &cr );

		if ( forward != nullptr )
		{
			forward->x = cp * cy;
			forward->y = cp * sy;
			forward->z = -sp;
		}

		if ( right != nullptr )
		{
			right->x = -1 * sr * sp * cy + -1 * cr * -sy;
			right->y = -1 * sr * sp * sy + -1 * cr * cy;
			right->z = -1 * sr * cp;
		}

		if ( up != nullptr )
		{
			up->x = cr * sp * cy + -sr * -sy;
			up->y = cr * sp * sy + -sr * cy;
			up->z = cr * cp;
		}
	}

}

