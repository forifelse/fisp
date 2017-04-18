#pragma once

#include <string>
#include <fstream>
#include "define.h"

namespace fisp
{
	namespace share
	{
		struct Blob
		{
			byte*	ptr;
			ulong	size;

			Blob():ptr(nullptr),size(0) {}
			~Blob() { ptr = nullptr; size = 0; }
			void destroy() { delptr(ptr); size = 0; }
		};
	}
}