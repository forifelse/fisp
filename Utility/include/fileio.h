#pragma once

#include <string>
#include <fstream>
#include "define.h"

namespace fisp
{
	namespace utility
	{
		struct Blob
		{
			byte*	ptr = nullptr;
			ulong	size = 0;

			Blob():ptr(nullptr),size(0) {}
			~Blob() { ptr = nullptr; size = 0; }
			void destroy() { delptr(ptr); size = 0; }
		};

		class FileStream
		{
		public:
			static Blob loadFile(const std::string& strFile);
		};
	}
}