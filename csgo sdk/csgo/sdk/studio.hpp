#pragma once
#include "vec3.hpp"
#include "matrix3x4.hpp"

namespace csgo
{
	struct model_t
	{
		void*   handle;       //0x0000 
		char    name[ 260 ];  //0x0004 
		__int32 load_flags;   //0x0108 
		__int32 server_count; //0x010C 
		__int32 type;         //0x0110 
		__int32 flags;        //0x0114 
		vec3_t  mins;         //0x0118 
		vec3_t  maxs;         //0x0124 
		float   radius;       //0x0130 
		char    pad[ 0x1C ];  //0x0134
	}; // size = 0x0150

	enum bones_mask : int32_t {
		bone_used_mask = 0x0007FF00,
		bone_used_by_anything = 0x0007FF00,
		bone_used_by_hitbox = 0x00000100,    // bone (or child) is used by a hit box
		bone_used_by_attachment = 0x00000200,    // bone (or child) is used by an attachment point
		bone_used_by_vertex_mask = 0x0003FC00,
		bone_used_by_vertex_lod0 = 0x00000400,    // bone (or child) is used by the toplevel model via skinned vertex
		bone_used_by_vertex_lod1 = 0x00000800,
		bone_used_by_vertex_lod2 = 0x00001000,
		bone_used_by_vertex_lod3 = 0x00002000,
		bone_used_by_vertex_lod4 = 0x00004000,
		bone_used_by_vertex_lod5 = 0x00008000,
		bone_used_by_vertex_lod6 = 0x00010000,
		bone_used_by_vertex_lod7 = 0x00020000,
		bone_used_by_bone_merge = 0x00040000,    // bone is available for bone merge to occur against it

		bone_used_by_server = bone_used_by_hitbox | bone_used_by_vertex_lod0 | bone_used_by_vertex_lod1 | bone_used_by_vertex_lod2
		| bone_used_by_vertex_lod3 | bone_used_by_vertex_lod4 | bone_used_by_vertex_lod5 | bone_used_by_vertex_lod6 | bone_used_by_vertex_lod7

	};

	struct mstudiobone_t {
		int name_index;

		char* const get_name( ) const {
			return reinterpret_cast< char* >( const_cast< mstudiobone_t* >( this ) ) + name_index;
		}

		int parent;
		int bonecontroller[ 6 ];

		vec3_t pos;
		float quat[ 4 ];
		vec3_t rotation;
		vec3_t pos_scale;
		vec3_t rot_scale;

		matrix3x4_t	pose_to_bone;
		float quaternion_alignment[ 4 ];
		int flags;
		int proc_type;
		int proc_index;
		mutable int physics_bone;

		void* get_procedure( ) const {
			if ( !this->proc_index )
				return nullptr;
			else
				return ( void* ) ( ( ( std::uint8_t* ) this ) + this->proc_index );
		};

		int surface_prop_index;

		char* const get_surface_prop( void ) const {
			return ( ( char* ) this ) + surface_prop_index;
		}

		int contents;
		uint8_t pad_0x1[ 32 ];
	};

	struct mstudiobbox_t {
		int bone;
		int group;
		vec3_t bbmin;
		vec3_t bbmax;
		int hitbox_name_index;
		uint8_t pad_1[ 12 ];
		float radius;
		uint8_t pad_2[ 16 ];

		const char* get_name( ) {
			if ( !this->hitbox_name_index )
				return nullptr;

			return reinterpret_cast< const char* >( reinterpret_cast< std::uint8_t* >( const_cast< mstudiobbox_t* >( this ) ) + this->hitbox_name_index );
		}
	};

	struct mstudiohitboxset_t {
		int name_index;
		int num_hitboxes;
		int hitbox_index;

		const char* get_name( void ) {
			if ( !this->name_index )
				return nullptr;

			return reinterpret_cast< const char* >( reinterpret_cast< std::uint8_t* >( const_cast< mstudiohitboxset_t* >( this ) ) + this->name_index );
		}

		mstudiobbox_t* hitbox( int i ) const {
			if ( i > this->num_hitboxes )
				return nullptr;

			return reinterpret_cast< mstudiobbox_t* >( reinterpret_cast< std::uint8_t* >( const_cast< mstudiohitboxset_t* >( this ) ) + this->hitbox_index ) + i;
		}
	};

	struct studiohdr_t {
		int id;
		int version;
		long checksum;
		char name[ 64 ];
		int length;
		vec3_t vec_eye_pos;
		vec3_t vec_illumination_pos;
		vec3_t vec_hull_min;
		vec3_t vec_hull_max;
		vec3_t vec_min;
		vec3_t vec_max;
		int flags;
		int numbones;
		int boneindex;
		int numbonecontrollers;
		int bonecontrollerindex;
		int numhitboxsets;
		int hitboxsetindex;
		int numlocalanim;
		int localanimindex;
		int numlocalseq;
		int localseqindex;
		int activitylistversion;
		int eventsindexed;
		int numtextures;
		int textureindex;

		inline const char* get_name( void ) const {
			return this->name;
		}

		mstudiohitboxset_t* hitbox_set( int i ) {
			if ( i > this->numhitboxsets )
				return nullptr;

			return reinterpret_cast< mstudiohitboxset_t* > ( reinterpret_cast< std::uint8_t* >( const_cast< studiohdr_t* >( this ) ) + this->hitboxsetindex ) + i;
		}

		mstudiobone_t* bone( int i ) {
			if ( i > this->numbones )
				return nullptr;

			return reinterpret_cast< mstudiobone_t* > ( reinterpret_cast< std::uint8_t* >( const_cast< studiohdr_t* >( this ) ) + this->boneindex ) + i;
		}
	};


}
