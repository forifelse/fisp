#pragma once
#include <fstream>

struct SDCamera
{
	float	tx,ty,tz;
	float	rx,ry,rz;

	SDCamera() { memset(this, 0, sizeof(SDCamera)); }
	SDCamera(const SDCamera& o)
	{
		tx = o.tx; ty = o.ty; tz = o.tz;
		rx = o.rx; ry = o.ry; rz = o.rz;
	}
	SDCamera& operator=(const SDCamera& o)
	{
		tx = o.tx; ty = o.ty; tz = o.tz;
		rx = o.rx; ry = o.ry; rz = o.rz;
		return *this;
	}
	bool operator<(const SDCamera& o)
	{
		return true;
	}
};

struct SDLitDire
{
	SDLitDire() { memset(this, 0, sizeof(SDLitDire)); }
};

struct SDLitPoint
{
	std::string	strName;
	float	x,y,z;
	float	r,g,b;
	float	radius;
	float	intensity;

	SDLitPoint() { memset(this, 0, sizeof(SDLitPoint)); }
	SDLitPoint(const SDLitPoint& o)
	{
		strName = o.strName;
		x = o.x; y = o.y; z = o.z;
		r = o.r; g = o.g; b = o.b;
		radius = o.radius;
		intensity = o.intensity;
	}
	SDLitPoint& operator=(const SDLitPoint& o)
	{
		strName = o.strName;
		x = o.x; y = o.y; z = o.z;
		r = o.r; g = o.g; b = o.b;
		radius = o.radius;
		intensity = o.intensity;
		return *this;
	}
	bool operator<(const SDLitPoint& o)
	{
		return true;
	}
};

struct SDLitSpot : public SDLitPoint
{
	float	toward;
	float	inner, outer;

	SDLitSpot() { memset(this, 0, sizeof(SDLitSpot)); }
	SDLitSpot(const SDLitSpot& o)
	{
		__super::operator=(o);
		toward = o.toward;
		inner = o.inner;
		outer = o.outer;
	}
	SDLitSpot& operator=(const SDLitSpot& o)
	{
		__super::operator=(o);
		toward = o.toward;
		inner = o.inner;
		outer = o.outer;
		return *this;
	}
	bool operator<(const SDLitSpot& o)
	{
		return true;
	}
};

struct SDMaterial
{
	std::string	strName;
	std::string strMaterialName;
	std::string	strColorTexture;
	std::string	strNormalMap;
	std::string	strSpecularMap;
	std::string strLightMap;
	std::string strEmissiveMap;
	float	ambientR, ambientG, ambientB;
	float	diffuseR, diffuseG, diffuseB, diffuseA;
	float	specularR, specularG, specularB;
	float	emissiveR, emissiveG, emissiveB;
	float	shinness;
	bool	bTwoSided;
	float	metallic;
	float	roughness;

	SDMaterial() { memset(this, 0, sizeof(SDMaterial)); }
	SDMaterial(const SDMaterial& o)
	{
		strName = o.strName;
		strMaterialName = o.strMaterialName;
		strColorTexture = o.strColorTexture;
		strNormalMap = o.strNormalMap;
		strSpecularMap = o.strSpecularMap;
		strLightMap = o.strLightMap;
		strEmissiveMap = o.strEmissiveMap;
		ambientR = o.ambientR; ambientG = o.ambientG; ambientB = o.ambientB;
		diffuseR = o.diffuseR; diffuseG = o.diffuseG; diffuseB = o.diffuseB; diffuseA = o.diffuseA;
		specularR = o.specularR; specularG = o.specularG; specularB = o.specularB;
		emissiveR = o.emissiveR; emissiveG = o.emissiveG; emissiveB = o.emissiveB;
		shinness = o.shinness;
		bTwoSided = o.bTwoSided;
		metallic = o.metallic;
		roughness = o.roughness;
	}
	SDMaterial& operator=(const SDMaterial& o)
	{
		strName = o.strName;
		strMaterialName = o.strMaterialName;
		strColorTexture = o.strColorTexture;
		strNormalMap = o.strNormalMap;
		strSpecularMap = o.strSpecularMap;
		strLightMap = o.strLightMap;
		strEmissiveMap = o.strEmissiveMap;
		ambientR = o.ambientR; ambientG = o.ambientG; ambientB = o.ambientB;
		diffuseR = o.diffuseR; diffuseG = o.diffuseG; diffuseB = o.diffuseB; diffuseA = o.diffuseA;
		specularR = o.specularR; specularG = o.specularG; specularB = o.specularB;
		emissiveR = o.emissiveR; emissiveG = o.emissiveG; emissiveB = o.emissiveB;
		shinness = o.shinness;
		bTwoSided = o.bTwoSided;
		metallic = o.metallic;
		roughness = o.roughness;
		return *this;
	}
	bool operator<(const SDMaterial& o)
	{
		return true;
	}
};

struct SDTexture
{

};

struct SDGeomBlob
{
	float*			pVertices;
	unsigned int*	pIndex;
	float*			pUV;
	float*			pNormal;
	float*			pTangent;
	float*			pVerClr;

	SDGeomBlob() { memset(this, 0, sizeof(SDGeomBlob)); }
	SDGeomBlob(const SDGeomBlob& o)
	{
		memcpy(this, &o, sizeof(SDGeomBlob));
	}
	SDGeomBlob& operator=(const SDGeomBlob& o)
	{
		memcpy(this, &o, sizeof(SDGeomBlob));
		return *this;
	}
	bool operator<(const SDGeomBlob& o)
	{
		return true;
	}
};

struct SDGeometry
{
	unsigned int	uNumVertex;
	unsigned int	uNumIndex;
	bool			bNormal;
	bool			bTangent;
	bool			bUV;
	bool			bVerClr;
	//unsigned int	primType;
	SDGeomBlob*		pGeomBlob;

	SDGeometry() { memset(this, 0, sizeof(SDGeometry)); }
	SDGeometry(const SDGeometry& o)
	{
		uNumVertex = o.uNumVertex;
		uNumIndex = o.uNumIndex;
		bNormal = o.bNormal;
		bTangent = o.bTangent;
		bUV = o.bUV;
		bVerClr = o.bVerClr;
		//primType = o.primType;
		pGeomBlob = o.pGeomBlob;
	}
	SDGeometry& operator=(const SDGeometry& o)
	{
		uNumVertex = o.uNumVertex;
		uNumIndex = o.uNumIndex;
		bNormal = o.bNormal;
		bTangent = o.bTangent;
		bUV = o.bUV;
		bVerClr = o.bVerClr;
		//primType = o.primType;
		pGeomBlob = o.pGeomBlob;
		return *this;
	}
	bool operator<(const SDGeometry& o)
	{
		return true;
	}
};

struct SDAnimate
{
};

struct SDSubMesh
{
	unsigned int	uGeomIdx;
	unsigned int	uMateIdx;
	unsigned int	uAnimate;
	unsigned int	uSubIdx;
	bool			bCollision;

	SDSubMesh() { memset(this, 0, sizeof(SDSubMesh)); }
	SDSubMesh(const SDSubMesh& o)
	{
		uGeomIdx = o.uGeomIdx;
		uMateIdx = o.uMateIdx;
		uAnimate = o.uAnimate;
		uSubIdx = o.uSubIdx;
		bCollision = o.bCollision;
	}
	SDSubMesh& operator=(const SDSubMesh& o)
	{
		uGeomIdx = o.uGeomIdx;
		uMateIdx = o.uMateIdx;
		uAnimate = o.uAnimate;
		uSubIdx = o.uSubIdx;
		bCollision = o.bCollision;
		return *this;
	}
	bool operator<(const SDSubMesh& o)
	{
		return true;
	}
};

struct SDEntity
{
	std::string		strName;
	SDSubMesh		subFirst;
	std::string		strSubs; // Geometry index,Material index,Collision flag;Geometry index,Material index,Collision flag ...

	SDEntity() { memset(this, 0, sizeof(SDEntity)); }
	SDEntity(const SDEntity& o)
	{
		memcpy(this, &o, sizeof(SDEntity));
	}
	SDEntity& operator=(const SDEntity& o)
	{
		memcpy(this, &o, sizeof(SDEntity));
		return *this;
	}
	bool operator<(const SDEntity& o)
	{
		return true;
	}
};

struct SDNode
{
	std::string		strName;
	SDEntity		entity;
	//
	float			trans[16];//float	tx, ty, tz, rx, ry, rz, sx, sy, sz;
	bool			bVisible;
	bool			bCastShadow;
	bool			bReceiveShadow;
	bool			bSimulate;
	bool			bDamage;
	float			mass;
	//
	unsigned int	uParent;	// 0xffffffff or -1 means parent is null
	std::string		strChildren;
	// instance ?

	SDNode() { memset(this, 0, sizeof(SDNode)); }
	SDNode(const SDNode& o)
	{
		memcpy(this, &o, sizeof(SDNode));
	}
	SDNode& operator=(const SDNode& o)
	{
		memcpy(this, &o, sizeof(SDNode));
		return *this;
	}
	bool operator<(const SDNode& o)
	{
		return true;
	}
};

struct SDRoot
{
	std::string	strName;
	std::string	strNodes;
	std::string strChildren;

	SDRoot() { memset(this, 0, sizeof(SDRoot)); }
	SDRoot(const SDRoot& o)
	{
		strName = o.strName;
		strNodes = o.strNodes;
		strChildren = o.strChildren;
	}
	SDRoot& operator=(const SDRoot& o)
	{
		strName = o.strName;
		strNodes = o.strNodes;
		strChildren = o.strChildren;
		return *this;
	}
	bool operator<(const SDRoot& o)
	{
		return true;
	}
};

struct SDBlob
{
	// Blob data
	SDNode*			pNode;
	SDGeometry*		pGeom;
	SDMaterial*		pMate;
	SDAnimate*		pAnim;
	SDLitDire*		pLitDire;
	SDLitPoint*		pLitPoint;
	SDLitSpot*		pLitSpot;

	SDBlob() { memset(this, 0, sizeof(SDBlob)); }
	SDBlob(const SDBlob& o)
	{
		memcpy(this, &o, sizeof(SDBlob));
	}
	SDBlob& operator=(const SDBlob& o)
	{
		memcpy(this, &o, sizeof(SDBlob));
		return *this;
	}
	bool operator<(const SDBlob& o)
	{
		return true;
	}
};

struct SDScene
{
	// Blob data
	SDBlob*			pBlob;
	unsigned int	uNumNode;
	unsigned int	uNumMesh;
	unsigned int	uNumGeom;
	unsigned int	uNumMate;
	unsigned int	uNumAnim;
	unsigned int	uNumLitDire;
	unsigned int	uNumLitPoint;
	unsigned int	uNumLitSpot;
	// scene data
	std::string		strName;
	SDCamera		camera;
	SDRoot*			pRoot;

	SDScene() { memset(this, 0, sizeof(SDScene)); }
	virtual ~SDScene()
	{
		if (pBlob)delete pBlob, pBlob = 0; if (pRoot)delete pRoot, pRoot = 0;
	}
	SDScene(const SDScene& o)
	{
		//memcpy(this, &o, sizeof(SDScene));
		pBlob = o.pBlob;
		uNumNode = o.uNumNode;
		uNumMesh = o.uNumMesh;
		uNumGeom = o.uNumGeom;
		uNumMate = o.uNumMate;
		uNumAnim = o.uNumAnim;
		uNumLitDire = o.uNumLitDire;
		uNumLitPoint = o.uNumLitPoint;
		uNumLitSpot = o.uNumLitSpot;

		strName = o.strName;
		camera = o.camera;
		pRoot = o.pRoot;
	}
	SDScene& operator=(const SDScene& o)
	{
		//memcpy(this, &o, sizeof(SDScene));
		pBlob = o.pBlob;
		uNumNode = o.uNumNode;
		uNumMesh = o.uNumMesh;
		uNumGeom = o.uNumGeom;
		uNumMate = o.uNumMate;
		uNumAnim = o.uNumAnim;
		uNumLitDire = o.uNumLitDire;
		uNumLitPoint = o.uNumLitPoint;
		uNumLitSpot = o.uNumLitSpot;

		strName = o.strName;
		camera = o.camera;
		pRoot = o.pRoot;
		return *this;
	}
	bool operator<(const SDScene& o)
	{
		return true;
	}
};

struct SceneRW
{
private:
	template<class T>
	static void write(const T* pData, const std::string& strFile, unsigned int uFrom = 0)
	{
		std::ofstream ofs(strFile, std::ios::binary);
		ofs.seekp(uFrom);
		ofs.write((char*)pData, sizeof(T));
		ofs.close();

		//ofs << pScene->mFlags << " , " << pScene->mNumMeshes << std::endl;
	}

	template<class T>
	static void read(T& data, const std::string& strFile, unsigned int uFrom = 0)
	{
		std::ifstream ifs(strFile, std::ios::binary);
		ifs.seekg(uFrom);
		ifs.read((char*)&data, sizeof(T));
		ifs.close();

		//unsigned int uFlags, uNumMeshes;
		//char sz[2];
		//ifs >> uFlags >> sz >> uNumMeshes;
	}

public:
	static bool writeScene(const SDScene* pScene, const std::string& strFile)
	{
		if (nullptr == pScene || nullptr == pScene->pRoot)
			return false;
		//write<SDScene>(pScene, strFile);
		std::ofstream ofs(strFile, std::ios::binary);
		if (!ofs.is_open())
			return false;
		ofs.seekp(0);
		ofs.write((char*)pScene, sizeof(SDScene));
		if (pScene->uNumNode > 0)
		{
			ofs.write((char*)pScene->pBlob->pNode, sizeof(SDNode) * pScene->uNumNode);
		}
		//if(pScene->uNumMesh  > 0)
		//	ofs.write((char*)pScene->pBlob->pMesh, sizeof(SDMesh) * pScene->uNumMesh);
		if (pScene->uNumGeom > 0)
		{
			ofs.write((char*)pScene->pBlob->pGeom, sizeof(SDGeometry) * pScene->uNumGeom);
			SDGeometry* pGeom = nullptr;
			for (unsigned int i = 0; i < pScene->uNumGeom; i++)
			{
				pGeom = &pScene->pBlob->pGeom[i];
				ofs.write((char*)pGeom->pGeomBlob->pVertices, sizeof(float) * pGeom->uNumVertex * 3);
				if(pGeom->bNormal)
					ofs.write((char*)pGeom->pGeomBlob->pNormal, sizeof(float) * pGeom->uNumVertex * 3);
				if (pGeom->bTangent)
					ofs.write((char*)pGeom->pGeomBlob->pTangent, sizeof(float) * pGeom->uNumVertex * 3);
				if (pGeom->bUV)
					ofs.write((char*)pGeom->pGeomBlob->pUV, sizeof(float) * pGeom->uNumVertex * 2);
				if (pGeom->bVerClr)
					ofs.write((char*)pGeom->pGeomBlob->pVerClr, sizeof(float) * pGeom->uNumVertex * 3);
				if (nullptr != pGeom->pGeomBlob->pIndex && pGeom->uNumIndex > 0)
					ofs.write((char*)pGeom->pGeomBlob->pIndex, sizeof(unsigned int) * pGeom->uNumIndex);
			}
		}
		if (pScene->uNumMate  > 0)
			ofs.write((char*)pScene->pBlob->pMate, sizeof(SDMaterial) * pScene->uNumMate);
		if (pScene->uNumAnim  > 0)
			ofs.write((char*)pScene->pBlob->pAnim, sizeof(SDAnimate) * pScene->uNumAnim);
		if (pScene->uNumLitDire  > 0)
			ofs.write((char*)pScene->pBlob->pLitDire, sizeof(SDLitDire) * pScene->uNumLitDire);
		if (pScene->uNumLitPoint  > 0)
			ofs.write((char*)pScene->pBlob->pLitPoint, sizeof(SDLitPoint) * pScene->uNumLitPoint);
		if (pScene->uNumLitSpot  > 0)
			ofs.write((char*)pScene->pBlob->pLitSpot, sizeof(SDLitSpot) * pScene->uNumLitSpot);
		//
		ofs.write((char*)pScene->pRoot, sizeof(SDRoot));
		//
		ofs.close();
		return true;
	}

	static bool readScene(SDScene* pScene, const std::string& strFile)
	{
		if (nullptr == pScene)
			return false;
		//read<SDScene>(scene, strFile);
		std::ifstream ifs(strFile, std::ios::binary);
		if (!ifs.is_open())
			return false;
		memset(pScene, 0, sizeof(SDScene));
		ifs.seekg(0);
		ifs.read((char*)pScene, sizeof(SDScene));
		pScene->pBlob = new SDBlob;
		pScene->pRoot = new SDRoot;

		pScene->pBlob->pNode = nullptr;
		if (pScene->uNumNode > 0)
		{
			pScene->pBlob->pNode = new SDNode[pScene->uNumNode];
			ifs.read((char*)pScene->pBlob->pNode, sizeof(SDNode) * pScene->uNumNode);
		}

		//pScene->pBlob->pMesh = nullptr;
		//if (pScene->uNumMesh > 0)
		//{
		//	pScene->pBlob->pMesh = new SDMesh[pScene->uNumMesh];
		//	ifs.read((char*)pScene->pBlob->pMesh, sizeof(SDMesh) * pScene->uNumMesh);
		//	for(unsigned int i=0; i<pScene->uNumMesh; i++)
		//		pScene->pBlob->pMesh[i].pSubOther = nullptr;
		//}

		pScene->pBlob->pGeom = nullptr;
		if (pScene->uNumGeom > 0)
		{
			pScene->pBlob->pGeom = new SDGeometry[pScene->uNumGeom];
			ifs.read((char*)pScene->pBlob->pGeom, sizeof(SDGeometry) * pScene->uNumGeom);
			SDGeometry* pGeom = nullptr;
			for (unsigned int i = 0; i < pScene->uNumGeom; i++)
			{
				pGeom = &pScene->pBlob->pGeom[i];
				pGeom->pGeomBlob = new SDGeomBlob;
				pGeom->pGeomBlob->pVertices = new float[pGeom->uNumVertex * 3];
				ifs.read((char*)pGeom->pGeomBlob->pVertices, sizeof(float) * pGeom->uNumVertex * 3);
				pGeom->pGeomBlob->pNormal = nullptr;
				if (pGeom->bNormal)
				{
					pGeom->pGeomBlob->pNormal = new float[pGeom->uNumVertex * 3];
					ifs.read((char*)pGeom->pGeomBlob->pNormal, sizeof(float) * pGeom->uNumVertex * 3);
				}
				pGeom->pGeomBlob->pTangent = nullptr;
				if (pGeom->bTangent)
				{
					pGeom->pGeomBlob->pTangent = new float[pGeom->uNumVertex * 3];
					ifs.read((char*)pGeom->pGeomBlob->pTangent, sizeof(float) * pGeom->uNumVertex * 3);
				}
				pGeom->pGeomBlob->pUV = nullptr;
				if (pGeom->bUV)
				{
					pGeom->pGeomBlob->pUV = new float[pGeom->uNumVertex * 2];
					ifs.read((char*)pGeom->pGeomBlob->pUV, sizeof(float) * pGeom->uNumVertex * 2);
				}
				pGeom->pGeomBlob->pVerClr = nullptr;
				if (pGeom->bVerClr)
				{
					pGeom->pGeomBlob->pVerClr = new float[pGeom->uNumVertex * 3];
					ifs.read((char*)pGeom->pGeomBlob->pVerClr, sizeof(float) * pGeom->uNumVertex * 3);
				}
				pGeom->pGeomBlob->pIndex = nullptr;
				if (pGeom->uNumIndex > 0)
				{
					pGeom->pGeomBlob->pIndex = new unsigned int[pGeom->uNumIndex];
					ifs.read((char*)pGeom->pGeomBlob->pIndex, sizeof(unsigned int) * pGeom->uNumIndex);
				}
			}
		}

		pScene->pBlob->pMate = nullptr;
		if (pScene->uNumMate > 0)
		{
			pScene->pBlob->pMate = new SDMaterial[pScene->uNumMate];
			ifs.read((char*)pScene->pBlob->pMate, sizeof(SDMaterial) * pScene->uNumMate);
		}

		pScene->pBlob->pAnim = nullptr;
		if (pScene->uNumAnim > 0)
		{
			pScene->pBlob->pAnim = new SDAnimate[pScene->uNumAnim];
			ifs.read((char*)pScene->pBlob->pAnim, sizeof(SDAnimate) * pScene->uNumAnim);
		}

		pScene->pBlob->pLitDire = nullptr;
		if (pScene->uNumLitDire > 0)
		{
			pScene->pBlob->pLitDire = new SDLitDire[pScene->uNumLitDire];
			ifs.read((char*)pScene->pBlob->pLitDire, sizeof(SDLitDire) * pScene->uNumLitDire);
		}

		pScene->pBlob->pLitPoint = nullptr;
		if (pScene->uNumLitPoint > 0)
		{
			pScene->pBlob->pLitPoint = new SDLitPoint[pScene->uNumLitPoint];
			ifs.read((char*)pScene->pBlob->pLitPoint, sizeof(SDLitPoint) * pScene->uNumLitPoint);
		}

		pScene->pBlob->pLitSpot = nullptr;
		if (pScene->uNumLitSpot > 0)
		{
			pScene->pBlob->pLitSpot = new SDLitSpot[pScene->uNumLitSpot];
			ifs.read((char*)pScene->pBlob->pLitSpot, sizeof(SDLitSpot) * pScene->uNumLitSpot);
		}
		//
		ifs.read((char*)pScene->pRoot, sizeof(SDRoot));
		//
		ifs.close();
		return true;
	}
};
