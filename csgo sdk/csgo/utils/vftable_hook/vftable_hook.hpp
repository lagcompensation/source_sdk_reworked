#pragma once
#include <map>
#include <winnt.h>
#include <memoryapi.h>

class vftable_hook {
	vftable_hook( const vftable_hook& ) = delete;
public:

	template<class type>
	static type hook_manual( uintptr_t* instance, int offset, type hook )
	{
		DWORD Dummy;
		type fnOld = ( type )instance[ offset ];
		VirtualProtect( static_cast< void* >( instance + offset * 0x4 ), 0x4, PAGE_EXECUTE_READWRITE, &Dummy );
		instance[ offset ] = ( uintptr_t ) hook;
		VirtualProtect( static_cast< void* > ( instance + offset * 0x4 ), 0x4, Dummy, &Dummy );
		return fnOld;
	}

private:

	static int unprotect( void* region )
	{
		MEMORY_BASIC_INFORMATION mbi;
		VirtualQuery( ( LPCVOID ) region, &mbi, sizeof( mbi ) );
		VirtualProtect( mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &mbi.Protect );
		return mbi.Protect;
	}

	static void protect( void* region, int protection )
	{
		MEMORY_BASIC_INFORMATION mbi;
		VirtualQuery( ( LPCVOID ) region, &mbi, sizeof( mbi ) );
		VirtualProtect( mbi.BaseAddress, mbi.RegionSize, protection, &mbi.Protect );
	}
};




