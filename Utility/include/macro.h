/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#pragma once

namespace Diff3D
{
	/*-----------------------------------------------------------
	Zero
	------------------------------------------------------------*/
	#define FZERO									Maths::PFTolerance()

	/*-----------------------------------------------------------
	Assert
	------------------------------------------------------------*/
	#define FASSERT(exp)							{	\
														assert((exp));	\
													}
	//#define FASSERT(exp)							{	\
	//													if(!(exp))	\
	//													{	\
	//														char msg[MAX_PATH];	\
	//														sprintf(msg,"File: %s, Line: %d, Func: %s\r\n",__FILE__,__LINE__,__FUNCTION__);	\
	//														MessageBoxA(NULL,msg,"Title",0);	\
	//														std::fstream fs;	\
	//														fs.open("..\\error.ini",std::ios::out | std::ios::trunc | std::ios::binary);	\
	//														fs.write(msg,strlen(msg) + 1);	\
	//														fs.close();	\
	//													}	\
	//													assert((exp));	\
	//												}

	/*-----------------------------------------------------------
	Check
	------------------------------------------------------------*/
	#define FCHECK(exp,returnValue)					{	\
														if((!(exp)))	\
														{	\
															return (returnValue);	\
														}	\
													}

	/*-----------------------------------------------------------
	New a pointer
	------------------------------------------------------------*/
	#define VTFEDeepCopy(className,pDes,pSrc)		{	\
														if(pSrc)	\
														{	\
															if((pDes) == NULL)	\
															{	\
																pDes = IRoot::sNew<className>();	\
															}	\
															*pDes = *pSrc;	\
														}	\
														else	\
														{	\
															IRoot::sDelete<className>(pDes);	\
														}	\
													}

	/*-----------------------------------------------------------
	New a pointer
	------------------------------------------------------------*/
	#define FDeepCopy(className,pDes,pSrc)			{	\
														if(pSrc)	\
														{	\
															if((pDes) == NULL)	\
															{	\
																MAKE_PTR(pDes,className);	\
															}	\
															*pDes = *pSrc;	\
														}	\
														else	\
														{	\
															FREE_PTR(pDes);	\
														}	\
													}

	/*-----------------------------------------------------------
	New a pointer
	------------------------------------------------------------*/
	#define FDeepCopyBase(className,pDes,pSrc)		{	\
														if(pSrc)	\
														{	\
															if((pDes) == NULL)	\
															{	\
																MAKE_BASEPTR(pDes,className);	\
															}	\
															*pDes = *pSrc;	\
														}	\
														else	\
														{	\
															FREE_BASEPTR(pDes);	\
														}	\
													}

	/*-----------------------------------------------------------
	New a pointer
	------------------------------------------------------------*/
	#define MAKE_PTR(ptr,fclass)					{	\
														FASSERT(NULL == ptr);	\
														(ptr) = new (fclass);	\
														\
													}

	/*-----------------------------------------------------------
	Free a pointer
	------------------------------------------------------------*/
	#define FREE_PTR(ptr)							{	\
														if((ptr) != NULL)	\
														{	\
															delete (ptr);	\
														}	\
														(ptr) = NULL;	\
													}

	/*-----------------------------------------------------------
	New a pointer
	------------------------------------------------------------*/
	#define REMAKE_PTR(ptr,fclass)					{	\
														FREE_PTR(ptr);	\
														MAKE_PTR(ptr,fclass);	\
													}

	/*-----------------------------------------------------------
	Free pointer array
	------------------------------------------------------------*/
	#define FREE_ARRAY(ptr)							{	\
														if((ptr) != NULL)	\
														{	\
															delete[] (ptr);		\
															(ptr) = NULL;	\
														}	\
													}

	/*-----------------------------------------------------------
	Free com pointer
	------------------------------------------------------------*/
	#define FREE_COMPTR(ptr)						{	\
														if((ptr) != NULL)	\
														{	\
															(ptr)->Release();	\
															(ptr) = NULL;	\
														}	\
													}
	/*-----------------------------------------------------------
	new base pointer
	------------------------------------------------------------*/
	#define MAKE_BASEPTR(ptr,fclass)				{	\
														FASSERT(NULL == ptr);	\
														(ptr) = new (fclass);	\
													}

	/*-----------------------------------------------------------
	Free base pointer
	------------------------------------------------------------*/
	#define FREE_BASEPTR(ptr)						{	\
														if((ptr) != NULL)	\
														{	\
															delete (ptr);	\
															(ptr) = NULL;	\
														}	\
													}

	/*-----------------------------------------------------------
	Re-create pointer
	------------------------------------------------------------*/
	#define REMAKE_BASEPTR(ptr,fclass)				{	\
														FREE_BASEPTR(ptr);	\
														MAKE_PTR(ptr,fclass);	\
													}

	/*-----------------------------------------------------------
	Check pointer
	------------------------------------------------------------*/
	#define CHECK_PTR(ptr,returnValue)				{	\
														if((ptr) == NULL)	\
														{	\
															return (returnValue);	\
														}	\
													}

	/*-----------------------------------------------------------
	Check express
	------------------------------------------------------------*/
	#define CHECK_EXP(exp,returnValue)				{	\
														if((!(exp)))	\
														{	\
															return (returnValue);	\
														}	\
													}

	/*-----------------------------------------------------------
	Set state
	------------------------------------------------------------*/
	#define STATE_SET(state)						setState(state);

	/*-----------------------------------------------------------
	Check state
	------------------------------------------------------------*/
	#define CHECK_STATE(state,returnValue)			{	\
														if(isState(state))	\
														{	\
															return (returnValue);	\
														}	\
													}

	/*-----------------------------------------------------------
	Check memory
	------------------------------------------------------------*/
	#define CHECK_MEMORY(ptr,returnValue)			CHECK_PTR(ptr,returnValue);

	/*-----------------------------------------------------------
	Get map value
	------------------------------------------------------------*/
	#define FMETER(meter)							FUnit::getMapValue((meter));

	/*-----------------------------------------------------------
	Throw if failed
	------------------------------------------------------------*/
	#define FThrowIfFailed(hr)						{	\
														if (FAILED(hr))	\
														{	\
															throw;	\
														}	\
													}






























	/*-----------------------------------------------------------
	Run Diff3D
	------------------------------------------------------------*/
	#define RUN_FE3D(hInstance,hPrevInstance,lpCmdLine,nCmdShow,AppLogic,strTitle)		{	\
																							FESystem* pSys = FESystem::sInstance((hInstance),(hPrevInstance),(lpCmdLine),(nCmdShow));	\
																							pSys->setAppImp((AppLogic),(strTitle));	\
																							pSys->create();	\
																							pSys->mainLoop();	\
																							pSys->release();	\
																							int re = pSys->exitApp();	\
																							return re;	\
																						}

	/*-----------------------------------------------------------
	Run web player
	------------------------------------------------------------*/
	#define RUN_FE3DWebPlayer(hWnd,AppLogic,strTitle)		{	\
																FESystem* pSys = FESystem::sInstance((hWnd));	\
																pSys->setAppImp((AppLogic),(strTitle));	\
																pSys->create();	\
																pSys->mainLoop();	\
																pSys->release();	\
																int re = pSys->exitApp();	\
																delete pSys,pSys = NULL;	\
																return re;	\
															}

	/*-----------------------------------------------------------
	Default accuracy
	------------------------------------------------------------*/
	#define FACCURACY								6










	// Defined Enum for result.
	// returned value.
	enum FRD
	{
		F_OK = 0,						// OK
		F_FAILED,
		F_IGNORE,						//= 1,	// Return abnormal, but can ignore.
		F_ERROR_UNKNOWN,				//= 2,	// Return abnormal, unknown error and can not ignore.
		F_ERROR_CREATE_WINDOWS,			//= 2,	// Return abnormal, unknown error and can not ignore.
		F_STATE_ISRAW,					//= 2,	// Return abnormal, unknown error and can not ignore.
		F_STATE_MAKED,					//= 2,	// Return abnormal, unknown error and can not ignore.
		F_STATE_FREED,					//= 2,	// Return abnormal, unknown error and can not ignore.
		F_ERROR_CREATED3D,				//= 3,	// Failed to create Direct3D9.
		F_ERROR_G3D_NULL,				//= 4,	// Direct3D is null in a function.
		F_ERROR_DEVICE_NULL,			//= 4,	// Direct3D is null in a function.
		F_ERROR_G3DDX_MAKE,				//= 5,	// Failed to make G3DDX.
		F_ERROR_G3DDX_BUILDDEVICELIST,	//= 5,	// Failed to build device list.
		F_ERROR_ADAPTER_NONE,			//= 6,	// Failed to get adapter information. No adapter.
		F_ERROR_ADAPTER_ID,				//= 7,	// Failed to get adapter ID(identifier).
		F_ERROR_DEVICE_CAPS,			//= 8,	// Failed to get device CAPS(capsibility).
		F_ERROR_DEVICE_CREATE,			//= 9,	// Failed to create device.
		F_ERROR_DEVICE_NULL_IN_MAP,		//= 10,	// Failed to create device.
		F_ERROR_DEVICE_CHECK,			//= 11,	// Failed to check device, this device setting is invalid.
		F_ERROR_GETDEFAULT_DEVICE,		//= 12,	// Failed to check device, this device setting is invalid.
		F_ERROR_PRESENT,				//= 13,	// Failed to check device, this device setting is invalid.
		F_ERROR_CREATE_ENTITY,			//= 14,	// Failed to create mesh, check vertex or index data and other setting parameters.
		F_ERROR_CREATE_VERTEXBUFFER,	//= 14,	// Failed to create mesh, check vertex or index data and other setting parameters.
		F_ERROR_CREATE_INDEXBUFFER,		//= 14,	// Failed to create mesh, check vertex or index data and other setting parameters.
		F_ERROR_CREATE_PRIMITIVE,		//= 14,	// Failed to create mesh, check vertex or index data and other setting parameters.
		F_ERROR_CREATE_MESH,			//= 14,	// Failed to create mesh, check vertex or index data and other setting parameters.
		F_ERROR_CREATE_MEMORY,			//= 14,	// Failed to create memory, check new operator for new pointer.
	};

	typedef FRD fresult;
	typedef FRD Drt ;








































#define NULL_D3DPTR(ptr)	if((ptr) == NULL){	\
								return ;}
#define NULL_D3DPTR_RE(ptr)	if((ptr) == NULL){	\
								return F_ERROR_D3D_NULL;}
#define NULL_PTR_RE(ptr)	if((ptr) == NULL){	\
								return ;}
#define NULL_PTR_RE_BOOL(ptr)	if((ptr) == NULL){	\
									return false;}	
#define NULL_PTR_RE_INT(ptr)	if((ptr) == NULL){	\
									return -1;}
#define NULL_PTR_RE_NULL(ptr)	if((ptr) == NULL){	\
									return NULL;}
#define NULL_PTR_RE_ERROR(ptr,err)	if((ptr) == NULL){	\
								return (err);}
#define MAKE_STATE	SetState(FS_MAKE);
#define FREE_STATE	SetState(FS_FREE);
#define MAKE_STATE_RE	if(GetState() == FS_MAKE)	\
							return F_IGNORE;
#define FREE_STATE_RE	if(GetState() == FS_FREE)	\
							return F_IGNORE;
} // namespace AFFE