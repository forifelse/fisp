/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#pragma once
#include "useShare.h"
#include "scenedata.h"

namespace fisp
{
	class IScene;

	namespace share
	{
		/*-----------------------------------------------------------
		class ICamera
		------------------------------------------------------------*/
		class ICamera //: public ITransform
		{
		public:
			virtual void perspect(uint uWidth, uint uHeight, float fov = 1.570796327f, float ZNear = 0.01f, float ZFar = 10000.0f) = 0;
			virtual void move(float dx, float dy, float dz, bool bOffset = true) = 0;
			virtual void rotate(float dx, float dy, float dz, bool bOffset = true) = 0;
			virtual void update(float deltaTime) = 0;
			//virtual const Vector& pos() const = 0;
			//virtual const Matrix& viewMatrix() const = 0;
			//virtual const Matrix& projMatrix() const = 0;
			//virtual Matrix viewMatrixInv() const = 0;
			//virtual Matrix projMatrixInv() const = 0;

			//virtual void pawn(IPawn* pPawn) = 0;
			//virtual IPawn* pawn() = 0;
			//virtual const IPawn* pawn() const = 0;
			//virtual void radius(float fRadius, bool bOffset = true) = 0;
			//virtual void radianOff(float fRadianOff, bool bOffset = true) = 0;
			//virtual ITransform* transform() = 0;
			//// same as rotate(dx,dy,dz), mainly for avatar in a scene.
			//virtual void pitchYawRoll(float dx, float dy, float dz, float radianOffset) = 0;
			//virtual void zoom(float dist) = 0;
		};

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

		/*-----------------------------------------------------------
		class IRender
		------------------------------------------------------------*/
		class IRender : public IRoot
		{
		public:
			struct InitParam : public IRoot::InitParam
			{
				InitParam()
				{
					strTitle = "fisp";
					bBorder = false;
				}
				~InitParam()
				{
					strTitle = "";
					bBorder = false;
				}
				InitParam(const IRender::InitParam& o)
				{
					deviceParam = o.deviceParam;
					strTitle = o.strTitle;
					bBorder = o.bBorder;
				}
				IRender::InitParam& operator=(const IRender::InitParam& o)
				{
					deviceParam = o.deviceParam;
					strTitle = o.strTitle;
					bBorder = o.bBorder;
					return *this;
				}

				IDevice::InitParam deviceParam;
				String	strTitle = "fisp";
				bool	bBorder = false;

			};

		public:
			virtual void update(float delta) = 0;
			virtual void render(float delta) = 0;

		public:
			//virtual void fullscreen(bool bFullscreen) = 0;
			//virtual void dbPath(IDBPath* pDBPath) = 0;
			//virtual void eventPreRender(IDelegate* pEvent) = 0;
			//virtual void eventPostRender(IDelegate* pEvent) = 0;
			//virtual bool createPipelineState(ShaderState* pState) = 0;
			//virtual void flushScene() = 0;

			////virtual void populateCmdList() = 0;
			////virtual void waitForPreFrame() = 0;

			virtual ICamera* camera() = 0;
			virtual const ICamera* camera() const = 0;
			//virtual void scene(IScene* pScene) = 0;
			virtual IScene* scene() = 0;
			virtual const IScene* scene() const = 0;
			//virtual IAvatar* avatar() = 0;
			//virtual const IAvatar* avatar() const = 0;

		private:
		};

		/*-----------------------------------------------------------
		class IScene
		------------------------------------------------------------*/
		class IScene : public IRoot
		{
		public:
			virtual void clear() = 0;
			virtual void flush() = 0;
			virtual void update(float delta) = 0;
			virtual void render(float delta) = 0;
			virtual void onSize() = 0;
		};

		/*-----------------------------------------------------------
		class IWorld
		------------------------------------------------------------*/
		class IWorld : public IRoot
		{
		public:
		};


	}
}