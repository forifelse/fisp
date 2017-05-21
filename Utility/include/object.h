/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#pragma once
#include "base.h"
//#include "basecomp.h"

namespace fisp
{
	namespace utility
	{
		/*-----------------------------------------------------------
		enum EnumResourceType
		Should update the function [ bool Guid::sGetResourceName(String& strName,const EnumResourceType& resType) ]
		if add or remove enum element.
		------------------------------------------------------------*/
		enum EnumResourceType
		{
			Resource_Root,
			//
			Resource_Thread,
			//
			Resource_State,
			//
			Resource_RawGeometry,
			Resource_RawMaterial,
			Resource_RawTexture,
			Resource_RawLight,
			Resource_RawGpuShader,
			Resource_Geometry,
			Resource_Material,
			Resource_Texture,
			Resource_Light,
			Resource_GpuShader,
			//
			Resource_Primitive,
			Resource_Mesh,
			Resource_Widget,
			//
			Resource_Entity,
			Resource_MeshBone,
			Resource_MeshSkin,
			Resource_Grid,
			//
			Resource_RawString,
			Resource_String,
			Resource_Image,
			//
			Resource_File,
			//
			Resource_Effect,
			//
			Resource_IO,
			//
			Resource_Sound,
			//
			Resource_Unknow,
			//
			Resource_Max
		};

		/*-----------------------------------------------------------
		class FGUID
		------------------------------------------------------------*/
		class Guid : public IRoot
		{
		private:
			Tag				mtagGuid;
			EnumResourceType	meResType;
			// Key is tag ( = getTag()), Val is guid ( = guid.getGuid())
			//static TMaps<Tag,Tag>*	gpMapGuid;
			static TMaps<Tag, Tag>		gpMapGuid[Resource_Max];

		protected:

		public:
			Guid();
			virtual ~Guid();
			Guid(const Guid& other);
			// Use this interface to create guid is recommended.
			Guid(const Tag& tag, const EnumResourceType& resType);
			Guid& operator = (const Guid& other);
			bool operator == (const Guid& other) const;
			bool operator != (const Guid& other) const;
			bool operator < (const Guid& other) const;

			static void sDestroy();

			bool doCreate(void* pInitData = nullptr) override;
			void doDestroy() override;

			bool addToLib();
			//void getFromLib();
			void setGuid(const Tag& tagGuid);
			const Tag& getGuid() const;
			void setResourceType(const EnumResourceType& eResType);
			const EnumResourceType& getResourceType() const;
			void setTagResourceType(const Tag& tmTag, const EnumResourceType& resType);
			void getTagResourceType(Tag& tag, EnumResourceType& resType);
			bool isEmpty() const;
			void updateGuid();

			static bool sAddGuidToLib(const Tag& tag, const EnumResourceType& resType);
			static bool sAddGuidToLib(const Guid& guid, const EnumResourceType& resType);
			static bool sGetGuidFromLib(Guid& guid, const Tag& tmTag, const EnumResourceType& resType);
			static bool sIsValideToAdd(const Tag& tag, const EnumResourceType& resType);
			static bool sIsHas(const Tag& tag, const EnumResourceType& resType);
			static uint sGetResourceNumber(const EnumResourceType& resType);

			static bool sRemoveFromLib(const Tag& tag, const EnumResourceType& resType);

		private:
			static bool sGetResourceName(String& strName, const EnumResourceType& resType);
			static Tag sGetGuidTag(const Tag& tag, const EnumResourceType& resType);

			void copyOther(const Guid& other);
		};

		/*-----------------------------------------------------------
		class Object
		composite
		------------------------------------------------------------*/
		class Object : virtual public IRoot
		{
		public:
			Object();
			Object(const Object& object);
			virtual ~Object();

			static void sDestroy();

		public:
			// add component
			bool addComponent(Object* pComp);

			// Add component with guid,this interface is recommended.
			bool addComponent(Object* pComp, const Guid& guid);

			// add resource to static library.
			static bool sAddResource(Object* pLib);

			static bool sAddResource(Object* pLib, const Guid& guid);

		private:
			bool addComponent(Object* pComp, const Guid& guid, bool bAutoGuid /*= false*/);
			bool insertComponent(Object* pComp, ulong index);
			bool insertComponent(Object* pComp, const Guid& guid, ulong index);
			bool insertComponent(Object* pComp, const Guid& guid, ulong index, bool bAutoGuid /*= false*/);

			/*-----------------------------------------------------------
			prepare insert object.
			!true:		tag and eResType returned is valid.
			!false:		tag and eResType returned is invalid.
			@tag:		return value.
			@eResType:	return value.
			@pLinker:
			@pRoot:		for get the resource-type,may null if insert a static resource,or set the root.
			@pParent:	parent of the component that will be inserted.
			------------------------------------------------------------*/
			static bool sPreInsert(Tag& tag, EnumResourceType& eResType, const TMap<Guid, Object*>* const pLinker, const Object* pRoot, const Object* pParent, Object* pComp, const Guid& guid, ulong &index, bool bAutoGuid = false, bool bLinkerIsArray = false);

			static bool sInsertResource(Object* pComp, const Guid& guid, ulong &index, bool bAutoGuid /*= false*/);

			// Create GUID
			// tag is in the object (DPComposite::get/setTag()) and 
			// guid-tag is in the guid-object (Guid::get/setTag()).
			const Guid* createGuid(const EnumResourceType& resType, const Tag& tagNew = Tag(), bool bAutoTag = false);

			// Set tag and resource type,automatic call createGuid(resType,tag).
			bool setTagResourceType(const Tag& tag, const EnumResourceType& resType);

			// Create GUID
			// tag is in the object (DPComposite::get/setTag()) and 
			// guid-tag is in the guid-object (Guid::get/setTag()).
			const Guid* createGuid(const Tag& tag);

		public:
			void removeComponent();
			bool removeComponent(const Guid& guid, bool recursion = true);
			bool removeComponent(Object* pComp, bool recursion = true);
			Object* findComponent(const Guid& guid, bool recursion = true);
			Object* getComponent(Object* &pComp, const Guid& guid, bool recursion = true);
			bool replaceComponent(const Guid& guid, Object* pNewComponent);
			Object* operator () (ulong index);
			Object* subChildComponent(ulong index);
			const Object* subChildComponent(ulong index) const;

			static Object* sFindResource(const Guid& guid, bool recursion = true);
			static Object* sGetResource(Object* &pComp, const Guid& guid, bool recursion = true);
			static bool replaceResource(const Guid& guid, Object* pNewComponent);
			static ulong sGetResourceSum(const EnumResourceType& eType);
			//Object* subChildResource(ulong index,const EnumResourceType& eResType);
			//ulong getResourceSum(const EnumResourceType& eResType);

			bool isRoot() const;
			bool isComposite() const;
			bool hasChildComponent(bool bRecursion = true) const;
			bool isUseSelfValue() const;
			bool isHasComponentTag(const Tag& tag) const;
			static bool sHasResourceTag(const Tag& tag);

			void setParent(Object* parent);
			Object* getParent() const;
			Object* getRoot();
			const Object* getRoot() const;

			void setPrevSibling(Object* pPrevSibling);
			Object* getPrevSibling();
			const Object* getPrevSibling() const;
			void setNextSibling(Object* pNextSibling);
			Object* getNextSibling();
			const Object* getNextSibling() const;

			void setGuid(const Guid& guid);
			Guid* getGuid();
			const Guid* getGuid() const;
			const Guid* createGuid(bool bAutoTag = false);
			void clearGuid(bool bDeleteFromLib = false);

			void setResourceType(const EnumResourceType& eResType);
			const EnumResourceType& getResourceType() const;
			bool isResourceComposite() const;

			void setComponentTag(const Tag& tmTag);
			const Tag& getComponentTag() const;
			void setSubComponentLinker(TMap<Guid, Object*>* pMapSub);
			TMap<Guid, Object*>* getSubComponentLinker();
			const TMap<Guid, Object*>* getSubComponentLinker() const;

			// Get direct sub-component of this,no include itself.
			ulong getSubChildComponentSum() const;

			// Get direct sub-component of this,include itself.
			ulong getSubComponentSum() const;

			// Get all sub-component under this,include itself.
			ulong getComponentSum() const;


			void setLayerTag(const Tag& layer);
			Tag* getLayerTag();
			const Tag* getLayerTag() const;
			//Tag& getLayerTag();
			//const Tag& getLayerTag() const;
			ulong getLayer() const;

			// Operation
			virtual bool operator <(const Object& other) const;
			virtual Object& operator = (const Object& other);

			// create pointer
			template<class T>
			static T* sCreatePointer();
			// destroy pointer
			template<class T>
			static void sDestoryPointer(T* pt);

			template<class T>
			void setPrevSibling(T* pPrevSibling);
			template<class T>
			T* getPrevSibling();
			template<class T>
			const T* getPrevSibling() const;
			template<class T>
			void setNextSibling(T* pNextSibling);
			template<class T>
			T* getNextSibling();
			template<class T>
			const T* getNextSibling() const;
			// add sibling at last.
			template<class T>
			void addSibling(T* pSibling);
			template<class T>
			T* getFirstSibling();
			template<class T>
			const T* getFirstSibling() const;
			template<class T>
			T* getLastSibling();
			template<class T>
			const T* getLastSibling() const;

			// add sub/child component
			template<class T>
			bool addSubComponent(T* pSub);
			// get sub/child component
			template<class T>
			T* getSubComponent(ulong uIndex);
			template<class T>
			const T* getSubComponent(ulong uIndex) const;
			// get sub/child component
			template<class T>
			T* getSubComponent(const Tag& tag, bool recursion = true);
			// get component
			template<class T>
			T* getComponent(const Tag& tag, bool recursion = true);
			// component linearization
			template<class T>
			ulong linearizeData(TArray<T*>* linearComponent, TMap<String, T*>* mapComponent) const;

			// add lib resource
			template<class T>
			static bool sAddLibResource(T* pLib);
			// add lib resource
			template<class T>
			static bool sAddLibResource(T* pLib, const Tag& tag);
			// get lib resource
			template<class T>
			static T* sGetLibResource(T* &pLib, const Tag& tag);
			// get shared resource
			template<class TSharedHWRI, class TRawData>
			static TSharedHWRI* sGetSharedResource(TSharedHWRI* &pShared, const Tag& tag, TRawData* pRawData = NULL);
			// get lib resource count
			template<class T>
			static ulong sGetLibResourceSize();

		private:
			// create this object.It is often used for creation at first to create some object.
			bool doCreate(void* pInitData = nullptr) override;
			// release this object.It is often used for release at end to free some object.
			void doDestroy() override;
			// copy
			void copyOther(const Object& other);
			// component linearization recusion
			template<class T>
			ulong linearData(TArray<T*>* linearComponent, TMap<String, T*>* mapComponent) const;

		private:
			// Owner values
			// Owner values may exist in sub-class.

			// Parent
			Object*						mpParent;

			// GUID
			// tag is in the object (DPComposite::get/setTag()) and also in the guid-object (Guid::get/setTag()),
			// they must equal.
			// guid-tag is in the guid-object (Guid::get/setGuid()).
			Guid*							mpGuid;

			// Resource type
			EnumResourceType				meResourceType;

			// Layer tag
			Tag*							mpLayerTag;

			// Next sibling
			Object*						mpNextSibling;
			// Previous sibling
			Object*						mpPrevSibling;

			// Sub component
			TMap<Guid, Object*>*			mpMapSub;

			// Global Object
			static TMap<Guid, Object*>*	gpMapLib;

			// Recycle bin
			static TMap<Guid, Object*>*	gpMapBin;

			// All object pointer,reserved for memory manager.
			static TMap<Guid, Object*>*	gpMapAll;

			// class name
			static String					gstrClassName;

			// critical section
			//CRITICAL_SECTION*				mpCriticalSection;
			// Mutex
			// Semaphore
			// Event




















		public:
			static void setClassName(const String& strClassName);
			static const String& getClassName();

			// Check if this object is exist, and return it if it is exist.
			static Object*& HasInstance(const Tag& tag, Object*& object);
			// Get an object instance.
			static Object*& Instance(const Tag& tag = Tag(String("")));
			// Notify there has been created or deleted an object so that add it to map to manager.
			static Tag NotifyObjectManager(const Tag& tag, Object* const object, bool created = true);
			// Create memory if bin is empty,or get a object from bin.
			static void CreateMemory(const Tag& tag);
			// Get a new object from sub-class.
			static Object* GetNewObject();
			//static void SetClassTag(const Tag& tag);
			//static const Tag& ClassTag();
			//		private:
			// clear a map.
			void ClearMap(TMap<Tag, Object*> map);
			// Recycle garbage object for reuse.
			void Recycle(Object* garbage);
			// clear an object to bin for recycle.
			void ClearToBin();
			// Get an object from bin.
			static bool GetObjectFromBin(Object*&);
		};


		/*-----------------------------------------------------------
		class Object
		------------------------------------------------------------*/
		// create pointer
		template<class T>
		T* Object::sCreatePointer()
		{
			T* pt = new T;
			FASSERT(NULL != pt);
			return pt;
		}

		// destroy pointer
		template<class T>
		void Object::sDestoryPointer(T* pt)
		{
			FASSERT(NULL != pt);
			delete pt;
			pt = NULL;
		}

		template<class T>
		void Object::setPrevSibling(T* pPrevSibling)
		{
			mpPrevSibling = pPrevSibling;
		}

		template<class T>
		T* Object::getPrevSibling()
		{
			return (T*)mpPrevSibling;
		}

		template<class T>
		const T* Object::getPrevSibling() const
		{
			return (T*)mpPrevSibling;
		}

		// get next sibling
		template<class T>
		void Object::setNextSibling(T* pNextSibling)
		{
			mpNextSibling = pNextSibling;
		}

		// get next sibling
		template<class T>
		T* Object::getNextSibling()
		{
			return (T*)mpNextSibling;
		}
		// get next sibling
		template<class T>
		const T* Object::getNextSibling() const
		{
			return (T*)mpNextSibling;
		}

		template<class T>
		void Object::addSibling(T* pSibling)
		{
			FASSERT(NULL != pSibling);
			T* pLast = getLastSibling<T>();
			pLast->setNextSibling<T>(pSibling);
			pSibling->setPrevSibling<T>(pLast);
			//pSibling->setNextSibling<T>(NULL);
		}

		template<class T>
		T* Object::getFirstSibling()
		{
			T* pFirst = (T*)this;
			while (NULL != pFirst->getPrevSibling<T>())
			{
				pFirst = pFirst->getPrevSibling<T>();
			}
			return pFirst;
		}

		template<class T>
		const T* Object::getFirstSibling() const
		{
			T* pFirst = (T*)this;
			while (NULL != pFirst->getPrevSibling<T>())
			{
				pFirst = pFirst->getPrevSibling<T>();
			}
			return pFirst;
		}

		template<class T>
		T* Object::getLastSibling()
		{
			T* pLast = (T*)this;
			while (NULL != pLast->getNextSibling<T>())
			{
				pLast = pLast->getNextSibling<T>();
			}
			return pLast;
		}

		template<class T>
		const T* Object::getLastSibling() const
		{
			T* pLast = (T*)this;
			while (NULL != pLast->getNextSibling<T>())
			{
				pLast = pLast->getNextSibling<T>();
			}
			return pLast;
		}

		// add sub/child component
		template<class T>
		bool Object::addSubComponent(T* pSub)
		{
			return addComponent(pSub);
		}

		// get sub/child component
		template<class T>
		T* Object::getSubComponent(ulong uIndex)
		{
			return (T*)subChildComponent(uIndex);
		}

		template<class T>
		const T* Object::getSubComponent(ulong uIndex) const
		{
			return (T*)subChildComponent(uIndex);
		}

		// get sub/child component
		template<class T>
		T* Object::getSubComponent(const Tag& tag, bool recursion /* = true */)
		{
			Guid guid(tag, T::sGetResourceType());
			Object* p = findComponent(guid, recursion);
			if (p == this)
				return NULL;
			return (T*)p;
		}

		// get component
		template<class T>
		T* Object::getComponent(const Tag& tag, bool recursion /* = true */)
		{
			return (T*)findComponent(Guid(tag, T::sGetResourceType()), recursion);
		}

		// component linearization
		template<class T>
		ulong Object::linearizeData(TArray<T*>* linearComponent, TMap<String, T*>* mapComponent) const
		{
			if (NULL != linearComponent)
			{
				linearComponent->clear();
			}
			if (NULL != mapComponent)
			{
				mapComponent->clear();
			}
			return linearData(linearComponent, mapComponent);
		}

		// component linearization recusion
		template<class T>
		ulong Object::linearData(TArray<T*>* linearComponent, TMap<String, T*>* mapComponent) const
		{
			if (NULL != linearComponent)
			{
				linearComponent->add((T*)this);
			}
			if (NULL != mapComponent)
			{
				mapComponent->add(getTag().getName(), (T*)this);
			}
			//
			ulong uSize = 0;
			T* pSub = NULL;
			const ulong uCnt = getSubChildComponentSum();
			for (ulong i = 0; i < uCnt; i++)
			{
				pSub = (T*)getSubComponent<T>(i);
				uSize += pSub->linearData(linearComponent, mapComponent);
			}
			return uSize + 1;
		}

		template<class T>
		static bool Object::sAddLibResource(T* pLib)
		{
			FASSERT(pLib != NULL);
			return sAddResource(pLib);
		}

		template<class T>
		static bool Object::sAddLibResource(T* pLib, const Tag& tag)
		{
			FASSERT(pLib != NULL);
			return sAddResource(pLib, Guid(tag, T::sGetResourceType()));
		}

		template<class T>
		static T* Object::sGetLibResource(T* &pLib, const Tag& tag)
		{
			FASSERT(!tag.getName().isEmpty());
			sGetResource((Object*&)pLib, Guid(tag, T::sGetResourceType()));
			return (T*)pLib;
		}

		template<class TSharedHWRI, class TRawData>
		static TSharedHWRI* Object::sGetSharedResource(TSharedHWRI* &pShared, const Tag& tag, TRawData* pRawData /* = NULL */)
		{
			FASSERT(!tag.getName().isEmpty());
			sGetLibResource<TSharedHWRI>(pShared, tag);
			if (NULL == pShared)
			{
				TRawData* pRawLib = NULL;
				sGetLibResource<TRawData>(pRawLib, tag);
				if (NULL == pRawLib)
				{
					//priority use raw data in lib.
					pRawLib = pRawData;
				}
				if (NULL == pRawLib)
				{
					return pShared;
				}
				FASSERT(NULL != pRawLib);
				TSharedHWRI* pFlyweight = NULL;
				MAKE_PTR(pFlyweight, TSharedHWRI);
				pFlyweight->setTag(tag);
				pRawLib->makeResourceHWRI(pFlyweight);
				sAddLibResource<TSharedHWRI>(pFlyweight);
				//FASSERT(sGetLibResource<TSharedHWRI>(pShared,tag) == pFlyweight);
				//return pFlyweight;//sGetLibResource<TSharedHWRI>(pShared,tag);
				pShared = pFlyweight;
			}
			return pShared;
		}

		template<class T>
		ulong Object::sGetLibResourceSize()
		{
			return sGetResourceSum(T::sGetResourceType());
		}







	}
}