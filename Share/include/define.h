#pragma once

#include <string>
#include <fstream>

namespace fisp
{
	namespace share
	{
		typedef unsigned char byte;
		typedef unsigned long ulong;

#define delptr(ptr) {if(ptr) delete ptr,ptr=nullptr;}
	}
}