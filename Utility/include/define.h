#pragma once

#include <string>
#include <fstream>

namespace fisp
{
	namespace utility
	{
		typedef unsigned char		byte;
		typedef unsigned int		uint;
		//typedef unsigned int		uint8;
		//typedef unsigned int		uint16;
		typedef unsigned int		uint32;
		typedef unsigned long long	uint64;
		typedef unsigned long		ulong;

		//
#define delptr(ptr) {if(ptr) delete ptr,ptr=nullptr;}
	}
}