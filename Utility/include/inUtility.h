/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

//#ifndef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
//#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
//#endif
//
#pragma warning(disable:4996)

#ifdef USE_UTILITYDLL
#define UTILITYAPI _declspec(dllimport)
#else
#define UTILITYAPI _declspec(dllexport)
#endif

//#include "../precmp.h"
//#include <comdef.h>  // link error: not support in UWP
//
#include <assert.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
//
#define _CRTDBG_MAP_ALLOC 
#include<crtdbg.h>
//
#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <mutex>
using namespace std;
//
//#include <locale>
//#include <codecvt>
//#include "bstinc.h" // include in heard: precmp.h
#include "macro.h"
#include "define.h"

namespace fisp
{
	//typedef unsigned int	uint;	// == uint32
	//typedef unsigned long	ulong;
	//typedef unsigned char	byte;
	//typedef unsigned short	word;	//WORD
	//typedef unsigned long	dword;	//DWORD
	//typedef wchar_t			wchar;	//TCHAR WCHAR

	//typedef unsigned long long	ullong;
	//typedef unsigned __int64    uint64;

	namespace utility
	{
		inline void ThrowIfFailed(HRESULT hr)
		{
			if (hr < 0)
			{
				//throw Platform::Exception::CreateException(hr);
				assert(0);
				//assert(__FILE__ ## __LINE__);
			}
		}
		/*-----------------------------------------------------------
		class IBase
		------------------------------------------------------------*/
		class IBase
		{
		};

	}

//#define freeptr(ptr)	if(ptr){delete (ptr),(ptr)=0;}
//#define freecom(ptr)	if(ptr){(ptr)->Release(); (ptr)=0;}
//#define freearray(ptr)	if(ptr){delete[] (ptr); (ptr) = 0;}

#define ThrowIfFailed(hr) if((hr)<0){assert(0);}

}
