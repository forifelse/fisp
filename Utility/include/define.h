#pragma once

#include <string>
#include <fstream>

namespace fisp
{
	namespace utility
	{
		typedef unsigned char		byte;
		typedef unsigned int		uint;
		//
		typedef signed char         int8;
		typedef signed short        int16;
		typedef signed int          int32;
		typedef signed long long	int64;	//typedef signed __int64      int64;
		//
		typedef unsigned char       uint8;
		typedef unsigned short      uint16;
		typedef unsigned int        uint32;
		typedef unsigned long long	uint64;	//typedef unsigned __int64    uint64;
		//
		typedef unsigned long		ulong;

		//
#define delptr(ptr) {if(ptr) delete ptr,ptr=nullptr;}
	}
}