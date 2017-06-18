/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#pragma once
#include "inShare.h"

namespace fisp
{
	namespace share
	{
		/*-----------------------------------------------------------
		class IDevice
		------------------------------------------------------------*/
		class IDevice : public IRoot
		{
		public:
			struct InitParam : public IRoot::InitParam
			{
				void*	hWnd = nullptr;
				uint	width = 0;
				uint	height = 0;
				bool	fullscreen = true;
				bool	isUWP = false;	// UWP or win32 EXE
										//
				IDBPath*	pDBPath = nullptr;
			};

		public:
			virtual void fullscreen(bool bFullscreen) = 0;
			// clear render target
			virtual void clearRT() = 0;
			virtual void present(uint uSyncInterval = 0, uint uFlags = 0) = 0;
			virtual void* deviceHW() = 0;
			virtual uint backbufferCount() const = 0;
			//
			//virtual IBufferHeap* bufferHeap() = 0;
			//virtual IPipelineState* PSO() = 0;
			//virtual IDrawWorker* drawWorker() = 0;
			////
			//virtual IMeshRender* createMesh() = 0;
			////virtual IGpuShader* createGpuShader() = 0;
			//virtual ITexture* createTexture(const String& strTag) = 0;
			//virtual ITexture* findTexture(const String& strTag) = 0;
		};



	}
}