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

struct SDLitDire
{
	SDLitDire() { memset(this, 0, sizeof(SDLitDire)); }
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

struct SDGeometry
{
	unsigned int	uNumVertex;
	float*			pVertices;
	//unsigned int	uNumFace;
	unsigned int	uNumIndex;
	unsigned int*	pIndex;
	float*			pUV;
	float*			pNormal;
	float*			pTangent;
	float*			pVerClr;

	SDGeometry() { memset(this, 0, sizeof(SDGeometry)); }
	SDGeometry(const SDGeometry& o)
	{
		uNumVertex = o.uNumVertex;
		//uNumFace = o.uNumFace;
		uNumIndex = o.uNumIndex;
		// ?
		pVertices = o.pVertices;
		pIndex = o.pIndex;
		pUV = o.pUV;
		pNormal = o.pNormal;
		pTangent = o.pTangent;
		pVerClr = o.pVerClr;

	}
	SDGeometry& operator=(const SDGeometry& o)
	{
		uNumVertex = o.uNumVertex;
		//uNumFace = o.uNumFace;
		uNumIndex = o.uNumIndex;
		// ?
		pVertices = o.pVertices;
		pIndex = o.pIndex;
		pUV = o.pUV;
		pNormal = o.pNormal;
		pTangent = o.pTangent;
		pVerClr = o.pVerClr;
		return *this;
	}
	bool operator<(const SDGeometry& o)
	{
		return true;
	}
};

struct SDSubMesh
{
	unsigned int	uGeomIdx;
	unsigned int	uMateIdx;
	unsigned int	uSubIdx;
	bool			bCollision;

	SDSubMesh() { memset(this, 0, sizeof(SDSubMesh)); }
	SDSubMesh(const SDSubMesh& o)
	{
		uGeomIdx = o.uGeomIdx;
		uMateIdx = o.uMateIdx;
		uSubIdx = o.uSubIdx;
		bCollision = o.bCollision;
	}
	SDSubMesh& operator=(const SDSubMesh& o)
	{
		uGeomIdx = o.uGeomIdx;
		uMateIdx = o.uMateIdx;
		uSubIdx = o.uSubIdx;
		bCollision = o.bCollision;
		return *this;
	}
	bool operator<(const SDSubMesh& o)
	{
		return true;
	}
};

struct SDMesh
{
	std::string		strName;
	bool			bVisible;
	SDSubMesh		subFirst;
	unsigned int	uNumSubOther;
	SDSubMesh*		pSubOther;
	//
	float			trans[16];
	//float			tx, ty, tz, rx, ry, rz, sx, sy, sz;
	bool			bCastShadow;
	bool			bReceiveShadow;
	bool			bSimulate;
	float			mass;
	bool			bDamage;
	//
	unsigned int	uParent;	// 0xffff or -1 means parent is null
	unsigned int	uNumChild;
	unsigned int*	pChildren;
	// instance ?

	SDMesh() { memset(this, 0, sizeof(SDMesh)); }
	SDMesh(const SDMesh& o)
	{
		memcpy(this, &o, sizeof(SDMesh));
	}
	SDMesh& operator=(const SDMesh& o)
	{
		memcpy(this, &o, sizeof(SDMesh));
		return *this;
	}
	bool operator<(const SDMesh& o)
	{
		return true;
	}
};

struct SDRoot
{
	unsigned int	uNumChild;
	unsigned int*	pChildren;

	SDRoot() { memset(this, 0, sizeof(SDRoot)); }
	SDRoot(const SDRoot& o)
	{
		uNumChild = o.uNumChild;
		pChildren = o.pChildren;
	}
	SDRoot& operator=(const SDRoot& o)
	{
		uNumChild = o.uNumChild;
		pChildren = o.pChildren;
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
	SDMesh*			pMesh;
	SDGeometry*		pGeom;
	SDMaterial*		pMate;
	SDLitPoint*		pLitPoint;
	SDLitSpot*		pLitSpot;
	SDLitDire*		pLitDire;

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
	unsigned int	uNumMesh;
	unsigned int	uNumGeom;
	unsigned int	uNumMate;
	unsigned int	uNumLitPoint;
	unsigned int	uNumLitSpot;
	unsigned int	uNumLitDire;
	// scene data
	std::string		strName;
	SDCamera		camera;
	SDRoot*			pRoot;

	SDScene() { memset(this, 0, sizeof(SDScene)); }
	SDScene(const SDScene& o)
	{
		memcpy(this, &o, sizeof(SDScene));
	}
	SDScene& operator=(const SDScene& o)
	{
		memcpy(this, &o, sizeof(SDScene));
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
	static void sceneWrite(const SDScene* pScene, const std::string& strFile)
	{
		write<SDScene>(pScene, strFile);
	}

	static void sceneRead(SDScene& scene, const std::string& strFile)
	{
		read<SDScene>(scene, strFile);
	}
};
