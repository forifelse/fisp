/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#include "..\include\object.h"

namespace fisp
{
	namespace utility
	{
		/*-----------------------------------------------------------
		class Guid
		------------------------------------------------------------*/
		//TMaps<Tag,Tag>* Guid::gpMapGuid = new TMaps<Tag,Tag>[Resource_Max];
		TMaps<Tag, Tag>	Guid::gpMapGuid[Resource_Max];
		Guid::Guid()
			:mtagGuid("")
			, meResType(Resource_Max)
		{
			tag("");
			//setGuid("");
		}

		Guid::~Guid()
		{
			destroy();
		}

		Guid::Guid(const Tag& tag, const EnumResourceType& resType)
			:mtagGuid("")
			, meResType(Resource_Max)
		{
			setTagResourceType(tag, resType);
		}

		Guid::Guid(const Guid& other)
			:mtagGuid("")
			, meResType(Resource_Max)
		{
			copyOther(other);
		}

		Guid& Guid::operator = (const Guid& other)
		{
			copyOther(other);
			return *this;
		}

		bool Guid::operator == (const Guid& other) const
		{
			return ((getTag() == other.getTag()) && \
				(getGuid() == other.getGuid()) && \
				(getResourceType() == other.getResourceType()));
		}

		bool Guid::operator != (const Guid& other) const
		{
			return !(*this == other);
		}

		bool Guid::operator < (const Guid& other) const
		{
			return (getTag() < other.getTag());
			//return (getGuid() < other.getGuid());
			//return ((getTag() < other.getTag()) &&	\
						//	(getGuid() < other.getGuid())) &&	\
			//	(getResourceType() < other.getResourceType());
		}

		void Guid::copyOther(const Guid& other)
		{
			IRoot::operator = (other);
			tag(other.getTag());
			setResourceType(other.getResourceType());
			setGuid(other.getGuid());
		}

		void Guid::sDestroy()
		{
			if (gpMapGuid != NULL)
			{
				//gpMapGuid->clear();
				delete[] gpMapGuid;
				//gpMapGuid = NULL;
			}
		}

		bool Guid::doCreate(void* pInitData /* = nullptr */)
		{
			return true;
		}

		void Guid::doDestroy()
		{
			mtagGuid.clear();
			meResType = Resource_Max;
		}

		bool Guid::addToLib()
		{
			Tag tag = getTag();
			EnumResourceType resType = getResourceType();
			if (sAddGuidToLib(tag, resType))
			{
				Tag tagGuid;
				tagGuid = sGetGuidTag(tag, resType);
				setGuid(tagGuid);
				// assert
				Guid guid;
				FASSERT(sGetGuidFromLib(guid, tag, resType));
				FASSERT(getTag() == guid.getTag() &&
					getResourceType() == guid.getResourceType() &&
					getGuid() == guid.getGuid());
				return true;
			}
			return false;
		}

		void Guid::updateGuid()
		{
			Tag tagGuid;
			tagGuid = sGetGuidTag(getTag(), getResourceType());
			setGuid(tagGuid);
		}

		void Guid::setGuid(const Tag& tagGuid)
		{
			if (!tagGuid.name().isEmpty())
			{
				mtagGuid = tagGuid;
			}
		}

		const Tag& Guid::getGuid() const
		{
			//updateGuid();
			return mtagGuid;
		}

		void Guid::setResourceType(const EnumResourceType& eResType)
		{
			FCHECK(eResType >= 0 && eResType < Resource_Max, void());
			meResType = eResType;
			updateGuid();
		}

		const EnumResourceType& Guid::getResourceType() const
		{
			return meResType;
		}

		void Guid::setTagResourceType(const Tag& tmTag, const EnumResourceType& resType)
		{
			FASSERT(!tmTag.name().isEmpty() && resType >= 0 && resType < Resource_Max);
			tag(tmTag);
			setResourceType(resType);
			updateGuid();
		}

		void Guid::getTagResourceType(Tag& tag, EnumResourceType& resType)
		{
			tag = getTag();
			resType = getResourceType();
		}

		bool Guid::isEmpty() const
		{
			return meResType == Resource_Max ||
				mtagGuid.name().isEmpty() ||
				getTag().name().isEmpty();
		}

		bool Guid::sAddGuidToLib(const Tag& tag, const EnumResourceType& resType)
		{
			FASSERT(sIsValideToAdd(tag, resType));
			Tag tagGuid;
			tagGuid = sGetGuidTag(tag, resType);
			FASSERT(!tagGuid.name().isEmpty());
			gpMapGuid[resType].Add(tag, tagGuid);
			return true;
		}

		bool Guid::sAddGuidToLib(const Guid& guid, const EnumResourceType& resType)
		{
			return sAddGuidToLib(guid.getTag(), resType);
		}

		bool Guid::sGetGuidFromLib(Guid& guid, const Tag& tmTag, const EnumResourceType& resType)
		{
			Tag val("");
			gpMapGuid[resType].getValue(tmTag, val);
			bool bHas = !val.name().isEmpty();
			if (bHas)
			{
				guid.tag(tmTag);
				guid.setGuid(val);
				FASSERT(!guid.getTag().name().isEmpty());
				FASSERT(!guid.getGuid().name().isEmpty());
				guid.setResourceType(resType);
				FASSERT(guid.getResourceType() >= 0 && guid.getResourceType() < Resource_Max);
			}
			return bHas;
		}

		bool Guid::sIsValideToAdd(const Tag& tag, const EnumResourceType& resType)
		{
			if (tag.name().isEmpty() || resType < 0 || resType >= Resource_Max)
			{
				return false;
			}
			return !sIsHas(tag, resType);
		}

		bool Guid::sIsHas(const Tag& tag, const EnumResourceType& resType)
		{
			Tag tagGuid;
			return gpMapGuid[resType].Find(tag, tagGuid);
		}

		bool Guid::sRemoveFromLib(const Tag& tag, const EnumResourceType& resType)
		{
			if (sIsHas(tag, resType))
			{
				Tag val;
				return gpMapGuid[resType].Remove(tag, val);
			}
			return false;
		}

		uint Guid::sGetResourceNumber(const EnumResourceType& resType)
		{
			return gpMapGuid[resType].GetSize();
		}

		bool Guid::sGetResourceName(String& strName, const EnumResourceType& resType)
		{
			strName.clear();
			switch (resType)
			{
			case Resource_Root:
				strName = String("root");
				break;
			case Resource_Thread:
				strName = String("thread");
				break;
			case Resource_State:
				strName = String("state");
				break;
			case Resource_RawGeometry:
				strName = String("rawGeometry");
				break;
			case Resource_RawMaterial:
				strName = String("rawMaterial");
				break;
			case Resource_RawTexture:
				strName = String("rawTexture");
				break;
			case Resource_RawLight:
				strName = String("rawLight");
				break;
			case Resource_RawGpuShader:
				strName = String("rawGpuShader");
				break;
			case Resource_Geometry:
				strName = String("geometry");
				break;
			case Resource_Material:
				strName = String("material");
				break;
			case Resource_Texture:
				strName = String("texture");
				break;
			case Resource_Light:
				strName = String("light");
				break;
			case Resource_GpuShader:
				strName = String("GpuShader");
				break;
			case Resource_Entity:
				strName = String("Entity");
				break;
			case Resource_Primitive:
				strName = String("primitive");
				break;
			case Resource_Grid:
				strName = String("grid");
				break;
			case Resource_Mesh:
				strName = String("mesh");
				break;
			case Resource_MeshBone:
				strName = String("meshBone");
				break;
			case Resource_MeshSkin:
				strName = String("meshSkin");
				break;
			case Resource_Widget:
				strName = String("widget");
				break;
			case Resource_String:
				strName = String("string");
				break;
			case Resource_Image:
				strName = String("image");
				break;
			case Resource_File:
				strName = String("file");
				break;
			case Resource_Effect:
				strName = String("effect");
				break;
			case Resource_IO:
				strName = String("io");
				break;
			case Resource_Sound:
				strName = String("sound");
				break;
			case Resource_Unknow:
				strName = String("unknow");
				break;
			default:
				strName = "unknown";
			}
			return !strName.isEmpty();
		}

		Tag Guid::sGetGuidTag(const Tag& tag, const EnumResourceType& resType)
		{
			Tag tagGuid;
			String resName;
			sGetResourceName(resName, resType);
			resName += ".";
			resName += tag.name();
			tagGuid.name(resName);
			return tagGuid;
		}

		/*-----------------------------------------------------------
		class Object
		Parent in charge of deleting elements.
		Siblings delete it's previous or next sibling only when the previous or next sibling do not has parent.
		------------------------------------------------------------*/
		TMap<Guid, Object*>* Object::gpMapLib = NULL;
		TMap<Guid, Object*>* Object::gpMapBin = NULL;
		TMap<Guid, Object*>* Object::gpMapAll = NULL;
		String Object::gstrClassName = "Object";
		Object::Object()
			:mpParent(NULL)
			, mpGuid(NULL)
			, meResourceType(Resource_Unknow)
			, mpLayerTag(NULL)
			, mpNextSibling(NULL)
			, mpPrevSibling(NULL)
			, mpMapSub(NULL)
		{
			mpLayerTag = Tag::createMem<Tag>();
			mpLayerTag->name("0");
		}

		Object::~Object()
		{
			removeComponent();
			destroy();
		}

		Object::Object(const Object& other)
			:mpParent(NULL)
			, mpGuid(NULL)
			, mpLayerTag(NULL)
			, mpNextSibling(NULL)
			, mpPrevSibling(NULL)
			, mpMapSub(NULL)
		{
			copyOther(other);
		}

		Object& Object::operator = (const Object& other)
		{
			copyOther(other);
			return *this;
		}

		bool Object::operator <(const Object& object) const
		{
			return getTag() < object.getTag();
		}

		bool Object::doCreate(void* pInitData /* = nullptr */)
		{
			mpParent = NULL;
			if (NULL == mpLayerTag)
			{
				mpLayerTag = Tag::createMem<Tag>();
				mpLayerTag->name("0");
			}

			return true;
		}

		void Object::doDestroy()
		{
			removeComponent();
			if (mpParent != NULL)
			{
				mpParent->removeComponent(this);
				mpParent = NULL;
			}
			if (NULL != mpPrevSibling)
			{
				mpPrevSibling->setNextSibling(mpNextSibling);
			}
			if (NULL != mpNextSibling)
			{
				mpNextSibling->setPrevSibling(mpPrevSibling);
			}
			mpPrevSibling = mpNextSibling = NULL;
			Guid::destroyMem<Guid>(mpGuid);
			Tag::destroyMem<Tag>(mpLayerTag);
			if (mpMapSub != NULL)
			{
				delete mpMapSub;
				mpMapSub = NULL;
			}
		}

		void Object::copyOther(const Object& other)
		{
			IRoot::operator = (other);
			// parent
			if (!other.isRoot())
			{
				MAKE_PTR(mpParent, Object);
				setParent(other.getParent());
			}
			// guid
			if (other.getGuid() != NULL)
			{
				Guid::destroyMem<Guid>(mpGuid);
				mpGuid = Guid::createMem<Guid>();
				*mpGuid = *other.getGuid();
				FASSERT(getGuid() != NULL);
			}
			meResourceType = other.getResourceType();
			// player tag
			Tag::deepCopy<Tag>(mpLayerTag, other.getLayerTag());
			// sibling
			FDeepCopy(Object, mpNextSibling, other.mpNextSibling);
			FDeepCopy(Object, mpPrevSibling, other.mpPrevSibling);
			// sub map
			if (other.getSubComponentLinker() != NULL)
			{
				if (mpMapSub == NULL)
				{
					mpMapSub = new TMap < Guid, Object* > ;
				}
				*mpMapSub = *other.getSubComponentLinker();
			}
			else
			{
				FREE_PTR(mpMapSub);
			}
			// class name
			gstrClassName = other.getClassName();
		}

		void Object::CreateMemory(const Tag& tag)
		{
			// Get a object memory from bin first, if NULL then allocate a new object.
			Object* fromBin = NULL;
			bool hasObj = GetObjectFromBin(fromBin);
			if (!hasObj || fromBin == NULL)
			{
				fromBin = GetNewObject();//new DPComposite();
			}
			NotifyObjectManager(tag, fromBin);
		}

		Object* Object::GetNewObject()
		{
			return NULL;
		}

		// component operation ...
		void Object::setParent(Object* parent)
		{
			mpParent = parent;
		}

		Object* Object::getParent() const
		{
			return mpParent;
		}

		void Object::setPrevSibling(Object* pPrevSibling)
		{
			mpPrevSibling = pPrevSibling;
		}

		Object* Object::getPrevSibling()
		{
			return mpPrevSibling;
		}

		const Object* Object::getPrevSibling() const
		{
			return mpPrevSibling;
		}

		void Object::setNextSibling(Object* pNextSibling)
		{
			mpNextSibling = pNextSibling;
		}

		Object* Object::getNextSibling()
		{
			return mpNextSibling;
		}

		const Object* Object::getNextSibling() const
		{
			return mpNextSibling;
		}

		void Object::setGuid(const Guid& guid)
		{
			if (NULL == mpGuid)
			{
				mpGuid = Guid::createMem<Guid>();
				*mpGuid = guid;
			}
		}

		Guid* Object::getGuid()
		{
			return mpGuid;
		}

		const Guid* Object::getGuid() const
		{
			return mpGuid;
		}

		bool Object::setTagResourceType(const Tag& tag, const EnumResourceType& resType)
		{
			if (Guid::sIsValideToAdd(tag, resType))
			{
				const Guid* pGuid = createGuid(resType, tag);
				return (pGuid == NULL) ? false : true;
			}
			return false;
		}

		void Object::setResourceType(const EnumResourceType& eResType)
		{
			if (eResType >= 0 && eResType < Resource_Max)
			{
				meResourceType = eResType;
			}
		}

		const EnumResourceType& Object::getResourceType() const
		{
			return meResourceType;
		}

		bool Object::isResourceComposite() const
		{
			return getResourceType() != Resource_Max;
		}

		const Guid* Object::createGuid(const EnumResourceType& resType, const Tag& tagNew /* = Tag() */, bool bAutoTag /* = false */)
		{
			Tag tagTemp = (tagNew.name().isEmpty()) ? getTag() : tagNew;
			if (!Guid::sIsValideToAdd(tagTemp, resType))
			{
				if (bAutoTag)
				{
					tagTemp.name(Guid::sGetResourceNumber(resType));
				}
				else
				{
					FASSERT(NULL != mpGuid);
					return mpGuid;
				}
			}
			if (Guid::sIsValideToAdd(tagTemp, resType))
			{
				if (NULL == mpGuid)
				{
					mpGuid = Guid::createMem<Guid>();
					mpGuid->setTagResourceType(tagTemp, resType);
				}
				else
				{
					//FASSERT(getTag() == mpGuid->getTag());
					mpGuid->sRemoveFromLib(getTag(), resType);
					if (getTag() != mpGuid->getTag())
					{
						mpGuid->sRemoveFromLib(mpGuid->getTag(), resType);
					}
					*mpGuid = Guid(tagTemp, resType);
				}
				mpGuid->addToLib();
				tag(tagTemp);
				setResourceType(resType);
				FASSERT(getTag() == mpGuid->getTag());
				FASSERT(getResourceType() == mpGuid->getResourceType());
			}
			FASSERT(NULL != mpGuid);
			return mpGuid;
		}

		const Guid* Object::createGuid(bool bAutoTag /* = false */)
		{
			if (mpGuid != NULL && getTag() == mpGuid->getTag() && getResourceType() == mpGuid->getResourceType())
			{
				return NULL;
			}
			return createGuid(getResourceType(), Tag(), bAutoTag);
		}

		void Object::clearGuid(bool bDeleteFromLib /* = false */)
		{
			if (bDeleteFromLib)
			{
				;
			}
			Guid::destroyMem<Guid>(mpGuid);
		}

		const Guid* Object::createGuid(const Tag& tag)
		{
			FASSERT(!tag.name().isEmpty());
			EnumResourceType resType = getResourceType();
			FASSERT(resType >= 0 && resType < Resource_Max);
			if (Guid::sIsValideToAdd(tag, resType))
			{
				const Guid* pGuid = createGuid(resType, tag);
				return pGuid;
			}
			return NULL;
		}

		Object* Object::getRoot()
		{
			if (isRoot())
			{
				return this;
			}
			return mpParent->getRoot();
			//Object* pRoot = this;
			//while(NULL != pRoot->getParent())
			//{
			//	pRoot = pRoot->getParent();
			//}
			//while(NULL != pRoot->getPrevSibling())
			//{
			//	pRoot = pRoot->getPrevSibling();
			//}
			//FASSERT(pRoot->isRoot());
			//return pRoot;
		}

		const Object* Object::getRoot() const
		{
			if (isRoot())
			{
				return this;
			}
			return mpParent->getRoot();
			//const Object* pRoot = this;
			//while(NULL != pRoot->getParent())
			//{
			//	pRoot = pRoot->getParent();
			//}
			//while(NULL != pRoot->getPrevSibling())
			//{
			//	pRoot = pRoot->getPrevSibling();
			//}
			//FASSERT(pRoot->isRoot());
			//return pRoot;
		}

		bool Object::isRoot() const
		{
			return (NULL == mpParent && NULL == mpPrevSibling);
		}

		bool Object::isComposite() const
		{
			return hasChildComponent();
		}

		bool Object::hasChildComponent(bool bRecursion /*= true*/) const
		{
			return mpMapSub != NULL && mpMapSub->size() > 0;
		}

		bool Object::isUseSelfValue() const
		{
			return true;
		}

		bool Object::isHasComponentTag(const Tag& tag) const
		{
			if (getTag() == tag)
			{
				return true;
			}
			else
			{
				if (mpMapSub == NULL)
				{
					return false;
				}
				Object* pComp = NULL;
				for (ulong i = 0; i < mpMapSub->size(); i++)
				{
					pComp = mpMapSub->getAt(i);
					if (pComp != NULL)
					{
						if (pComp->isHasComponentTag(tag))
						{
							pComp = NULL;
							return true;
						}
						pComp = NULL;
					}
				}
			}
			return false;
		}

		bool Object::sHasResourceTag(const Tag& tag)
		{
			//if(getTag() == tag)
			//{
			//	return true;
			//}
			//else
			{
				if (gpMapLib == NULL)
				{
					return false;
				}
				Object* pComp = NULL;
				for (ulong i = 0; i < gpMapLib->size(); i++)
				{
					pComp = gpMapLib->getAt(i);
					if (pComp != NULL)
					{
						if (pComp->sHasResourceTag(tag))
						{
							pComp = NULL;
							return true;
						}
						pComp = NULL;
					}
				}
			}
			return false;
		}

		bool Object::addComponent(Object* pComp)
		{
			return addComponent(pComp, Guid(), false);
		}

		bool Object::addComponent(Object* pComp, const Guid& guid)
		{
			return addComponent(pComp, guid, false);
		}

		bool Object::addComponent(Object* pComp, const Guid& guid, bool bAutoGuid /* = false */)
		{
			if (mpMapSub == NULL)
			{
				mpMapSub = new TMap < Guid, Object* > ;
			}
			ulong index = mpMapSub->size();
			return insertComponent(pComp, guid, index, bAutoGuid);
		}

		bool Object::insertComponent(Object* pComp, ulong index)
		{
			return insertComponent(pComp, Guid(), index, false);
		}

		bool Object::insertComponent(Object* pComp, const Guid& guid, ulong index)
		{
			return insertComponent(pComp, guid, index, false);
		}

		bool Object::insertComponent(Object* pComp, const Guid& guid, ulong index, bool bAutoGuid /* = false */)
		{
			Tag tmTag;
			EnumResourceType resType;
			if (!sPreInsert(tmTag, resType, mpMapSub, getRoot(), this, pComp, guid, index, bAutoGuid))
				return false;

			// check component
			Object* pRoot = getRoot();
			FASSERT(pRoot != NULL);
			if (pRoot->isHasComponentTag(tmTag))
			{
				String strMsg("Failed to add component -- ");
				strMsg += tmTag.name();
				strMsg += ". Tag name is not available!\r\n";
				//Log::singleton()->write(strMsg);
				FASSERT(!"Tag name is not available!");
				return false;
			}
			//if(!hasSelfValue())
			//{
			//	return true;
			//}

			// check guid
			//if(!Guid::sIsValideToAdd(tmTag,resType))
			//{
			//	String msg("Failed to add component -- ");
			//	msg += tmTag.getName();
			//	msg += ". Guid name is not available!\r\n";
			//	gLog->write(msg);
			//	FASSERT(0);
			//	return false;
			//}

			// set new component
			pComp->setParent(this);
			pComp->setComponentTag(tmTag);
			//pComp->createGuid(resType,tmTag);
			pComp->setGuid(Guid(tmTag, resType));
			FASSERT(pComp->getGuid() != NULL);
			// new pointer
			if (mpMapSub == NULL)
			{
				mpMapSub = new TMap < Guid, Object* > ;
			}
			// add
			mpMapSub->add(*(pComp->getGuid()), pComp);
			return true;
		}

		bool Object::sAddResource(Object* pLib)
		{
			Guid guid;
			Guid* pGuid = pLib->getGuid();
			if (pGuid != NULL)
			{
				guid = *pGuid;
			}
			return sAddResource(pLib, guid);
		}

		bool Object::sAddResource(Object* pLib, const Guid& guid)
		{
			ulong index = 0;
			return sInsertResource(pLib, guid, index, false);
		}

		bool Object::sInsertResource(Object* pComp, const Guid& guid, ulong &index, bool bAutoGuid /* = false */)
		{
			FASSERT(pComp != NULL);
			Tag tmTag;
			EnumResourceType resType;
			// new pointer
			if (gpMapLib == NULL)
			{
				gpMapLib = new TMap<Guid, Object*>[Resource_Max];
			}
			if (!sPreInsert(tmTag, resType, gpMapLib, NULL, NULL, pComp, guid, index, bAutoGuid, true))
				return false;

			// check component
			//Object* pRoot = getRoot();
			//FASSERT(pRoot != NULL);
			if (sHasResourceTag(tmTag))
			{
				String strMsg("Failed to add component -- ");
				strMsg += tmTag.name();
				strMsg += ". Tag name is not available!\r\n";
				//gLog->write(strMsg);
				FASSERT(0);
				return false;
			}
			//if(!hasSelfValue())
			//{
			//	return true;
			//}

			// check guid
			//if(!Guid::sIsValideToAdd(tmTag,resType))
			//{
			//	String msg("Failed to add component -- ");
			//	msg += tmTag.getName();
			//	msg += ". Guid name is not available!\r\n";
			//	gLog->write(msg);
			//	FASSERT(0);
			//	return false;
			//}

			// set new component
			pComp->setParent(NULL);
			pComp->setComponentTag(tmTag);
			//pComp->createGuid(resType,tmTag);
			pComp->setGuid(Guid(tmTag, resType));
			FASSERT(pComp->getGuid() != NULL);
			//// new pointer
			//if(gpMapLib == NULL)
			//{
			//	gpMapLib = new TMap<Guid,Object*>[Resource_Max];
			//}
			// add
			gpMapLib[resType].add(*(pComp->getGuid()), pComp);
			return true;
		}

		bool Object::sPreInsert(Tag& tag, EnumResourceType& eResType, const TMap<Guid, Object*>* const pLinker, const Object* pRoot, const Object* pParent, Object* pComp, const Guid& guid, ulong &index, bool bAutoGuid /* = false */, bool bLinkerIsArray /* = false */)
		{
			CHECK_PTR(pComp, false);
			FASSERT((pComp->getGuid() != NULL && !pComp->getGuid()->isEmpty()) ||
				(!guid.getTag().name().isEmpty() && guid.getResourceType() >= 0 && guid.getResourceType() < Resource_Max) ||
				pLinker != NULL);// && index == pLinker->GetSize());

			// set resource type
			EnumResourceType resType = guid.getResourceType();
			if (!(resType >= 0 && resType < Resource_Max) && pRoot != NULL)
			{
				resType = pRoot->getResourceType();
			}
			if (!(resType >= 0 && resType < Resource_Max))
			{
				resType = pComp->getResourceType();
			}
			if (!(resType >= 0 && resType < Resource_Max))
			{
				resType = Resource_Unknow;
			}
			FASSERT(resType >= 0 && resType < Resource_Max);

			// set index
			if (bLinkerIsArray)
				index = pLinker[resType].size();
			else
				index = pLinker->size();

			// set layer
			const Tag layer(index);
			Tag comTag("");
			if (pParent != NULL)
			{
				comTag = *pParent->getLayerTag();
				comTag += Tag(".");
				comTag += layer;
			}
			else
			{
				comTag = "0";
			}
			pComp->setLayerTag(comTag);
			// set tag
			Tag tmTag;
			if (bAutoGuid)
			{
				tmTag = *pComp->getLayerTag();
			}
			else
			{
				tmTag = (pComp->getGuid() != NULL) ? pComp->getGuid()->getTag() : pComp->getTag();
				tmTag = (guid.getTag().name().isEmpty()) ? (tmTag) : guid.getTag();
			}
			if (tmTag.name().isEmpty())
			{
				tmTag = *pComp->getLayerTag();
				String strName = tmTag.name();
				strName.remove(0, 1);
				strName = getClassName() + strName;
				tmTag.name(strName);
			}
			FASSERT(!tmTag.name().isEmpty());

			// save
			tag = tmTag;
			eResType = resType;
			return true;
		}

		//void Object::removeComponent()
		//{
		//	CHECK_PTR(mpMapSub,void());
		//	Guid tmGuid;
		//	Object* pComp = NULL;
		//	for(mpMapSub->First(); !mpMapSub->IsEnd(); mpMapSub->Next())
		//	{
		//		mpMapSub->Value(tmGuid,pComp);
		//		if(pComp != NULL)
		//		{
		//			if(pComp->hasChildComponent())
		//			{
		//				pComp->removeComponent();
		//			}
		//			else
		//			{
		//				Object* ptmComp = NULL;
		//				mpMapSub->Remove(*pComp->getGuid(),ptmComp);
		//				FREE_PTR(ptmComp);
		//			}
		//		}
		//	}
		//}

		void Object::removeComponent()
		{
			CHECK_PTR(mpMapSub, void());
			Guid tmGuid;
			Object* pComp = NULL;
			for(ulong i=0; i<mpMapSub->size(); i=mpMapSub->size())// i++)
			{
				pComp = mpMapSub->getAt(i);
				if (pComp != NULL)
				{
					if (pComp->hasChildComponent())
					{
						pComp->removeComponent();
					}
					else
					{
						Object* ptmComp = NULL;
						mpMapSub->remove(*pComp->getGuid(), &ptmComp);
						FREE_PTR(ptmComp);
					}
				}
			}
		}

		bool Object::removeComponent(const Guid& guid, bool recursion /*= true*/)
		{
			if (guid.isEmpty() || mpMapSub == NULL)
			{
				return false;
			}
			Object* pComp = NULL;
			bool bResult = mpMapSub->remove(guid, &pComp);
			if (bResult)
			{
				FREE_PTR(pComp);
				Guid::sRemoveFromLib(guid.getTag(), guid.getResourceType());
				return true;
			}
			if (!bResult && recursion)
			{
				for (ulong i = 0; i < mpMapSub->size(); i++)
				{
					pComp = mpMapSub->getAt(i);
					if (pComp != NULL)
					{
						if (pComp->removeComponent(*pComp->getGuid(), recursion))
						{
							return true;
						}
					}
				}
			}
			return bResult;
		}

		bool Object::removeComponent(Object* pComp, bool recursion /*= true*/)
		{
			if (pComp == NULL)
			{
				return false;
			}
			return removeComponent(*pComp->getGuid(), recursion);
		}

		Object* Object::findComponent(const Guid& guid, bool recursion /*= true*/)
		{
			const Guid* pGuid = getGuid();
			if (pGuid != NULL && guid == *pGuid)
			{
				return this;
			}
			if (mpMapSub == NULL)
				return NULL;
			Object* pResult = NULL;
			if (mpMapSub->findElement(guid, pResult))
			{
				if (pResult != NULL)
				{
					return pResult;
				}
			}

			if (!recursion)
				return NULL;

			Object* val = NULL;
			for (ulong i = 0; i < mpMapSub->size(); i++)
			{
				val = mpMapSub->getAt(i);
				if (val != NULL)
				{
					pResult = val->findComponent(guid, recursion);
					if (pResult != NULL)
					{
						return pResult;
					}
				}
			}

			return NULL;
		}

		bool Object::replaceComponent(const Guid& guid, Object* pNewComponent)
		{
			return true;
		}

		Object* Object::getComponent(Object* &pComp, const Guid& guid, bool recursion /*= true*/)
		{
			pComp = findComponent(guid, recursion);
			return pComp;
		}

		Object* Object::sFindResource(const Guid& guid, bool recursion /*= true*/)
		{
			//Guid* pGuid = getGuid();
			//if(pGuid != NULL && guid == *pGuid)
			//{
			//	return this;
			//}
			if (gpMapLib == NULL)
				return NULL;
			const EnumResourceType resType = guid.getResourceType();
			FASSERT(resType >= 0 && resType < Resource_Max);
			Object* pResult = NULL;
			if (gpMapLib[resType].findElement(guid, pResult))
			{
				if (pResult != NULL)
				{
					return pResult;
				}
			}

			//if(!recursion)
			//	return NULL;

			//Guid tmGuid;
			//Object* val = NULL;
			//for(gpMapLib[resType].First(); !gpMapLib[resType].IsEnd(); gpMapLib[resType].Next())
			//{
			//	gpMapLib[resType].Value(tmGuid,val);
			//	if(val != NULL)
			//	{
			//		pResult = val->sFindResource(guid,recursion);
			//		if(pResult != NULL)
			//		{
			//			return pResult;
			//		}
			//	}
			//}

			return NULL;
		}

		bool Object::replaceResource(const Guid& guid, Object* pNewComponent)
		{
			return true;
		}

		Object* Object::sGetResource(Object* &pComp, const Guid& guid, bool recursion /*= true*/)
		{
			pComp = sFindResource(guid, recursion);
			return pComp;
		}

		ulong Object::sGetResourceSum(const EnumResourceType& eType)
		{
			if (gpMapLib == NULL || eType < 0 || eType >= Resource_Max)
			{
				return 0;
			}
			return gpMapLib[eType].size();
		}

		//Object* Object::subChildResource(ulong index,const EnumResourceType& eResType)
		//{
		//	CHECK_EXP(eResType >= 0 && eResType < Resource_Max);
		//	CHECK_EXP(index >= 0 && index < gpMapLib[eResType].GetSize(),NULL);
		//	////Guid guid;
		//	////Object* pVal = NULL;
		//	////return mpMapSub->element(guid,pVal,index);
		//	//return (*mpMapSub)[index];
		//	Guid guid;
		//	Object* pObj = NULL;
		//	gpMapLib[eResType].getValueByIndex(guid,pObj,index);
		//	return pObj;
		//}

		Object* Object::operator () (ulong index)
		{
			CHECK_EXP(index >= 0 && index < getSubChildComponentSum(), NULL);
			//if(isUseSelfValue())
			//{
			//	if(index == 0)
			//		return this;
			//	index --;
			//}
			return mpMapSub->getAt(index);
		}

		Object* Object::subChildComponent(ulong index)
		{
			CHECK_EXP(index >= 0 && index < getSubChildComponentSum(), NULL);
			////Guid guid;
			////Object* pVal = NULL;
			////return mpMapSub->element(guid,pVal,index);
			//return (*mpMapSub)[index];
			Object* pObj = NULL;
			pObj = mpMapSub->getAt(index);
			return pObj;
		}

		const Object* Object::subChildComponent(ulong index) const
		{
			CHECK_EXP(index >= 0 && index < getSubChildComponentSum(), NULL);
			////Guid guid;
			////Object* pVal = NULL;
			////return mpMapSub->element(guid,pVal,index);
			//return (*mpMapSub)[index];
			Object* pObj = NULL;
			pObj = mpMapSub->getAt(index);
			return pObj;
		}

		ulong Object::getSubChildComponentSum() const
		{
			return (mpMapSub == NULL) ? 0 : mpMapSub->size();
		}

		ulong Object::getSubComponentSum() const
		{
			if (isUseSelfValue())
			{
				return getSubChildComponentSum() + 1;
			}
			return getSubChildComponentSum();
		}

		ulong Object::getComponentSum() const
		{
			ulong cnt = 0;
			if (isUseSelfValue())
			{
				cnt = 1;
			}
			if (mpMapSub == NULL)
			{
				return cnt;
			}
			Object* pComp = NULL;
			for (ulong i = 0; i < mpMapSub->size(); i++)
			{
				pComp = mpMapSub->getAt(i);
				if (pComp != NULL)
				{
					cnt += pComp->getComponentSum();
				}
			}
			return cnt;
		}

		void Object::setComponentTag(const Tag& tmTag)
		{
			if (!isHasComponentTag(tmTag))
				tag(tmTag);
		}

		const Tag& Object::getComponentTag() const
		{
			return getTag();
		}

		void Object::setSubComponentLinker(TMap<Guid, Object*>* pMapSub)
		{
			mpMapSub = pMapSub;
		}

		TMap<Guid, Object*>* Object::getSubComponentLinker()
		{
			return mpMapSub;
		}

		const TMap<Guid, Object*>* Object::getSubComponentLinker() const
		{
			return mpMapSub;
		}

		void Object::setLayerTag(const Tag& layer)
		{
			*mpLayerTag = layer;
			if (mpMapSub == NULL)
			{
				return;
			}

			Object* val = NULL;
			for (ulong i = 0; i < mpMapSub->size(); i++)
			{
				val = NULL;
				val = mpMapSub->getAt(i);
				if (val != NULL)
				{
					Tag comTag = getLayerTag();
					comTag += Tag(".");
					Tag index(i);
					comTag += index;
					val->setLayerTag(comTag);
				}
			}
		}

		Tag* Object::getLayerTag()
		{
			return mpLayerTag;
		}

		const Tag* Object::getLayerTag() const
		{
			return mpLayerTag;
		}

		//Tag& Object::getLayerTag()
		//{
		//	return *mpLayerTag;
		//}
		//const Tag& Object::getLayerTag() const
		//{
		//	return *mpLayerTag;
		//}

		ulong Object::getLayer() const
		{
			if (mpLayerTag == NULL)
				return 0;
			return mpLayerTag->name().getSubStringCount(".");
		}

		void Object::setClassName(const String& strClassName)
		{
			FASSERT(!strClassName.isEmpty());
			if (gstrClassName != strClassName)
			{
				gstrClassName = strClassName;
			}
		}

		const String& Object::getClassName()
		{
			return gstrClassName;
		}

		void Object::sDestroy()
		{
			if (NULL != gpMapLib)
			{
				for (uint i = 0; i < Resource_Max; i++)
				{
					Object* pObj = NULL;
					for (ulong j = 0; j < gpMapLib[i].size(); j++)
					{
						pObj = gpMapLib[i].getAt(j);
						FREE_PTR(pObj);
					}
					gpMapLib[i].clear();
				}
				FREE_ARRAY(gpMapLib);
			}
		}

		// component operation.

		// Component interface.
		//bool DPComposite::Add(const Tag& tag)
		//{
		//	Tag temp(tag);
		//	if(temp.getName().isEmpty())
		//		return false;
		//	if(Find(tag,true) != NULL)
		//		return false;
		//	CreateMemory(temp);
		//	if(temp == tag)
		//		return true;
		//	Object* garbage = NULL;
		//	HasInstance(temp,garbage);
		//	Recycle(garbage);
		//	//Remove(temp);
		//	return false;
		//}

		//bool DPComposite::Remove(const Tag& tag,bool recursion)
		//{
		//	// Object can be removed only by it's parent.
		//	if(!HasChild())
		//		return false;
		//	// Find top most object in inner first for speedup although it has a repeated finding operation when find by recursion.
		//	DPComposite* object = NULL;
		//	if(m_mapInner.Remove(tag,object))
		//	{
		//		Recycle(object);
		//		return true;
		//	}
		//	else if(recursion)
		//	{
		//		for(m_mapInner.First(); !m_mapInner.IsEnd(); m_mapInner.Next())
		//		{
		//			Tag curTag;
		//			DPComposite* curObj = NULL;
		//			m_mapInner.Value(curTag,curObj);
		//			if(curObj != NULL)
		//				return curObj->Remove(curTag,recursion);
		//		}
		//	}

		//	return false;
		//}

		//bool DPComposite::HasChild() const
		//{
		//	return (m_mapInner.GetSize() > 0)? true : false;
		//}

		//bool DPComposite::HasChild(const Tag& tag,bool recursion)
		//{
		//	if(!HasChild())
		//		return false;
		//	return (Find(tag,true) != NULL && getTag() != tag)? true : false;
		//}

		//DPComposite* DPComposite::Find(const Tag& tag,bool recursion)
		//{
		//	if(getTag() == tag)
		//		return this;
		//	if(!HasChild())
		//		return NULL;
		//	DPComposite* value = NULL;
		//	// Search object within this object firstly.
		//	if(m_mapInner.Find(tag,value))
		//		return value;
		//	// Search object with this tag by recursion.
		//	if(recursion)
		//	{
		//		for(m_mapInner.First(); !m_mapInner.IsEnd(); m_mapInner.Next())
		//		{
		//			Tag tag;
		//			value = (DPComposite*)m_mapInner.Value(tag,value);
		//			return Find(tag,recursion);
		//		}
		//	}
		//	return NULL;
		//}

		Tag Object::NotifyObjectManager(const Tag& tag, Object* const object, bool created /* = true */)
		{
			FASSERT(object != NULL);
			//CHECK_PTR(object,void());
			Tag temp(tag);
			//if(created)
			//{
			//	if(temp.getName().isEmpty())
			//		temp = Tag(m_mapAll.GetSize());
			//	m_mapAll.Add(temp,object);
			//}
			//else
			//{
			//	temp = Tag(object->ClassTag());
			//	m_mapBin.Add(tag,object);
			//}
			return temp;
		}

		Object*& Object::HasInstance(const Tag& tag, Object*& object)
		{
			bool result = false;//m_mapAll.Find(tag,object);
			if (!result)
				object = NULL;
			return object;
		}

		Object*& Object::Instance(const Tag& tag /* = Tag(String("") */)
		{
			/*DPComposite* pResult = HasInstance(tag);
			if(pResult != NULL)
			return pResult;
			DPComposite *pAdd = CreateMemory();
			if(tag.getName().isEmpty())
			{
			String name("Device - ");
			fchar cnt[MAX_PATH];
			sprintf(cnt,"%d",m_mapInner.GetSize());
			name.append(cnt);
			tag.setName(name);
			}
			m_mapInner.Add(tag,pAdd);
			pAdd = NULL;*/

			Object* pResult = NULL;
			HasInstance(tag, pResult);
			if (pResult != NULL)
				return pResult;
			CreateMemory(tag);
			return Instance(tag);
		}

		void Object::Recycle(Object* garbage)
		{
			if (garbage == NULL)
				return;
			//garbage->SetOuter(NULL);
			// clear garbage's all children to it's owner bin first.
			garbage->ClearToBin();
			Tag tag;
			NotifyObjectManager(tag, garbage, false);

			//OBJ_MAP bin;
			//garbage->GetBin(bin);
			//OBJ_MAP::iterator it = bin.begin();
			//// Remove object from garbage's bin to this object's bin.
			//for(it = bin.begin(); it != bin.end(); it++)
			//{
			//	DPComposite* object = (DPComposite*)it->second;
			//	object->SetOuter(NULL);
			//	m_mapBin[object->getTag()] = object;
			//}
			//// clear garbage's bin.
			//bin.clear();
		}

		//void DPComposite::SetOuter(DPComposite* const outer)
		//{
		//	m_pOuter = outer;
		//}

		//DPComposite* DPComposite::GetOuter() const
		//{
		//	return m_pOuter;
		//}

		//const Tag& DPComposite::ClassTag()
		//{
		//	s_classTag = Tag(String("Diff3D::Share::DPComposite"));
		//	return s_classTag;
		//}

		//void DPComposite::SetClassTag(const Tag& tag)
		//{
		//	s_classTag = tag;
		//}

		//bool DPComposite::IsA(const Tag& classTag)
		//{
		//	return (s_classTag == classTag);
		//}

		//void DPComposite::SetContext(const DPComposite& context)
		//{
		//	*m_pContext = context;
		//}

		// Get and set
		//OBJ_MAP& DPComposite::GetBin()
		//{
		//	return m_mapBin;
		//}

		//void DPComposite::GetBin(OBJ_MAP& bin)
		//{
		//	//bin = m_mBin;
		//}

		void Object::ClearMap(TMap<Tag, Object*> map)
		{
			if (map.size() <= 0)
				return;
			for (ulong i = 0; i < map.size(); i++)
			{
				Object* object = NULL;
				object = (Object*)map.getAt(i);
				//if(map.Remove(tag,object))
				//	m_mapBin.Add(tag,object);
			}
			map.clear();
		}

		void Object::ClearToBin()
		{
			//if(!HasChild())
			return;
			//for(m_mapInner.First(); !m_mapInner.IsEnd(); m_mapInner.Next())
			//{
			//	Tag tag;
			//	DPComposite* object = NULL;
			//	m_mapInner.Value(tag,object);
			//	if(object != NULL)
			//	{
			//		//if(object->HasChild())
			//		//{
			//		//return object->ClearToBin();
			//		//}
			//		//else
			//		//{
			//		//m_mapInner.Remove();
			//		//m_mapBin.Add(tag,object);
			//		//}
			//	}
			//}
			//OBJ_MAP::iterator it = m_mapBin.begin();
			//for(it = m_mapInner.begin(); it != m_mapInner.end(); it++)
			//{
			//	DPComposite* object = (DPComposite*)it->second;
			//	// clear children object's children to its bin first.
			//	object->ClearToBin();
			//	m_mapBin[object->getTag()] = object;
			//}
			//m_mapInner.clear();
		}

		bool Object::GetObjectFromBin(Object*& object)
		{
			//if(m_mapBin.GetSize() <= 0)
			//	return false;
			//bool result = m_mapBin.Find(object->ClassTag(),object);
			//if(result && object != NULL)
			//{
			//	DPComposite* temp = NULL;
			//	m_mapBin.Remove(object->ClassTag(),temp);
			//	return true;
			//}
			return false;
		}



	}
}