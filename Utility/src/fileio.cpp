#include "../include/fileio.h"

namespace fisp
{
	namespace utility
	{
		Blob FileStream::loadFile(const std::string& strFile)
		{
			Blob blob;
			if (strFile.length() <= 0)
				return blob;
			std::fstream fs;
			fs.open(strFile.c_str(), std::ios::basic_ios::binary | std::ios::basic_ios::in);
			if (!fs.is_open())
				return blob;
			//fs.seekg(0);
			//unsigned long idx = fs.tellg();
			fs.seekg(0, std::ios::end);
			blob.size = (unsigned long)fs.tellg();
			blob.ptr = new byte[blob.size + 1];
			fs.seekg(0);
			fs.read((char*)blob.ptr, blob.size);
			blob.ptr[blob.size] = '\0';

			return blob;
		}

	}
}