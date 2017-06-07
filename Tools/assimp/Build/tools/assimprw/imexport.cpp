#include "imexport.h"
#include <fstream>
#include "../../../../share/include/scenedata.h"
#include "../../../../utility/include/useutility.h"

bool ImExport::load(const std::string& strInFile, const std::string& strFormat, const std::string& strContent, const std::string& strOutFile)
{
	Assimp::Importer importer;
	unsigned flags =
		aiProcess_ConvertToLeftHanded |
		aiProcess_JoinIdenticalVertices |
		aiProcess_Triangulate |
		aiProcess_GenSmoothNormals |
		aiProcess_LimitBoneWeights |
		aiProcess_ImproveCacheLocality |
		aiProcess_RemoveRedundantMaterials |
		aiProcess_FixInfacingNormals |
		aiProcess_FindInvalidData |
		aiProcess_GenUVCoords |
		aiProcess_FindInstances |
		aiProcess_OptimizeMeshes;
	//flags |= aiProcess_GenNormals;
	//flags |= aiProcess_CalcTangentSpace;
	const aiScene* pInScene = importer.ReadFile(strInFile, flags);			  
	if (nullptr == pInScene)
	{
		return false;
	}
	SDScene outScene;
	getScene(&outScene, pInScene);
	//for (unsigned int i = 0; i < 100; i++)
	//{
	//	char sz[16];
	//	sprintf(sz, "%d", 2*i);
	//	outScene.strTest+=std::string(sz);
	//}
	//outScene.strName = "aaaaaAAAA中文";
	String str = "aaaaaAAAA中文";
	str.encryption();
	outScene.strName = str.getString();
	SceneRW::writeScene(&outScene, strOutFile);
	// test
	SDScene inScene;
	SceneRW::readScene(&inScene, strOutFile);
	 str=String(inScene.strName);
	str.decryption();
	inScene.strName = str.getString();
	if (inScene.strName == "aaaaaAAAA中文")
		inScene.strName = "test ok";
	return true;
}

bool ImExport::getScene(void* pOutScene, const aiScene* pInScene)
{
	if (nullptr == pOutScene || nullptr == pInScene)
		return false;
	SDScene* pScene = (SDScene*)pOutScene;
	if (pInScene->mNumMeshes <= 0 || nullptr == pInScene->mMeshes)
		return false;
	pScene->pBlob = new SDBlob;
	pScene->pRoot = new SDRoot;
	//
	pScene->uNumGeom = pInScene->mNumMeshes;
	pScene->pBlob->pGeom = new SDGeometry[pScene->uNumGeom];
	for (unsigned int i = 0; i < pScene->uNumGeom; i++)
	{
		pScene->pBlob->pGeom[i].pGemoBlob = new SDGeomBlob;
		getGeom(&pScene->pBlob->pGeom[i], pInScene->mMeshes[i]);
	}
	if (pInScene->mNumMaterials > 0)
	{
		pScene->uNumMate = pInScene->mNumMaterials;
		pScene->pBlob->pMate = new SDMaterial[pScene->uNumMate];
		for (unsigned int i = 0; i < pScene->uNumMate; i++)
		{
			getMaterial(&pScene->pBlob->pMate[i], pInScene->mMaterials[i]);
		}
	}
	//
	getRoot(pScene->pRoot, pInScene);
	return true;
}

bool ImExport::getGeom(void* pDest, const aiMesh* pSrc)
{
	if (pSrc->mNumVertices <= 0 || pSrc->mNumFaces <= 0 || nullptr == pSrc->mFaces)
		return false;
	SDGeometry* dest = (SDGeometry*)pDest;
	dest->uNumVertex = pSrc->mNumVertices;
	dest->pGemoBlob->pVertices = new float[3 * dest->uNumVertex];
	if (pSrc->mNormals)
	{
		dest->pGemoBlob->pNormal = new float[3 * dest->uNumVertex];
	}
	if (pSrc->mTangents)
	{
		dest->pGemoBlob->pTangent = new float[3 * dest->uNumVertex];
	}
	if (pSrc->mTextureCoords)
	{
		dest->pGemoBlob->pUV = new float[2 * dest->uNumVertex];
	}
	for (unsigned int i = 0; i < pSrc->mNumVertices; i++)
	{
		dest->pGemoBlob->pVertices[3 * i] = pSrc->mVertices[i].x;
		dest->pGemoBlob->pVertices[3 * i + 1] = pSrc->mVertices[i].y;
		dest->pGemoBlob->pVertices[3 * i + 2] = pSrc->mVertices[i].z;
		if (pSrc->mNormals)
		{
			dest->pGemoBlob->pNormal[3 * i] = pSrc->mNormals[i].x;
			dest->pGemoBlob->pNormal[3 * i + 1] = pSrc->mNormals[i].y;
			dest->pGemoBlob->pNormal[3 * i + 2] = pSrc->mNormals[i].z;
		}
		if (pSrc->mTangents)
		{
			dest->pGemoBlob->pTangent[3 * i] = pSrc->mTangents[i].x;
			dest->pGemoBlob->pTangent[3 * i + 1] = pSrc->mTangents[i].y;
			dest->pGemoBlob->pTangent[3 * i + 2] = pSrc->mTangents[i].z;
		}
		if (pSrc->mTextureCoords)
		{
			dest->pGemoBlob->pUV[2 * i] = pSrc->mTextureCoords[0][i].x;
			dest->pGemoBlob->pUV[2 * i + 1] = pSrc->mTextureCoords[0][i].y;
		}
	}
	dest->uNumIndex = pSrc->mFaces->mNumIndices;
	dest->pGemoBlob->pIndex = new unsigned int[dest->uNumIndex];
	memcpy(dest->pGemoBlob->pIndex, pSrc->mFaces->mIndices, dest->uNumIndex * sizeof(unsigned int));
	
	return true;
}

bool ImExport::getMaterial(void* pDest, const aiMaterial* pSrc)
{
	aiString aiStrVal;
	aiColor3D aiClrVal;
	float aiNumVal;
	int aiIntVal;
	SDMaterial* dest = (SDMaterial*)pDest;
	//
	pSrc->Get(AI_MATKEY_NAME, aiStrVal);
	dest->strName = std::string(aiStrVal.C_Str());
	if (pSrc->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), aiStrVal) == AI_SUCCESS)
		dest->strColorTexture = std::string(aiStrVal.C_Str());
	if (pSrc->Get(AI_MATKEY_TEXTURE(aiTextureType_NORMALS, 0), aiStrVal) == AI_SUCCESS)
		dest->strNormalMap = std::string(aiStrVal.C_Str());
	if (pSrc->Get(AI_MATKEY_TEXTURE(aiTextureType_SPECULAR, 0), aiStrVal) == AI_SUCCESS)
		dest->strSpecularMap = std::string(aiStrVal.C_Str());
	if (pSrc->Get(AI_MATKEY_TEXTURE(aiTextureType_LIGHTMAP, 0), aiStrVal) == AI_SUCCESS)
		dest->strLightMap = std::string(aiStrVal.C_Str());
	if (pSrc->Get(AI_MATKEY_TEXTURE(aiTextureType_EMISSIVE, 0), aiStrVal) == AI_SUCCESS)
		dest->strEmissiveMap = std::string(aiStrVal.C_Str());
	if (pSrc->Get(AI_MATKEY_COLOR_AMBIENT, aiClrVal) == AI_SUCCESS)
		dest->ambientR = aiClrVal.r, dest->ambientG = aiClrVal.g, dest->ambientB = aiClrVal.b;
	if (pSrc->Get(AI_MATKEY_COLOR_DIFFUSE, aiClrVal) == AI_SUCCESS)
		dest->diffuseR = aiClrVal.r, dest->diffuseG = aiClrVal.g, dest->diffuseB = aiClrVal.b;
	if (pSrc->Get(AI_MATKEY_COLOR_SPECULAR, aiClrVal) == AI_SUCCESS)
		dest->specularR = aiClrVal.r, dest->specularG = aiClrVal.g, dest->specularB = aiClrVal.b;
	if (pSrc->Get(AI_MATKEY_COLOR_EMISSIVE, aiClrVal) == AI_SUCCESS)
		dest->emissiveR = aiClrVal.r, dest->emissiveG = aiClrVal.g, dest->emissiveB = aiClrVal.b;
	if (pSrc->Get(AI_MATKEY_OPACITY, aiNumVal) == AI_SUCCESS)
	{
		if (aiNumVal < 0.0000001f)
			aiNumVal = 1.0f;
		if (aiNumVal < 1.0f)
		{
			dest->strMaterialName = "alpha";
			dest->diffuseA = aiNumVal;
		}
	}
	else if (pSrc->Get(AI_MATKEY_COLOR_TRANSPARENT, aiClrVal) == AI_SUCCESS)
	{
		dest->strMaterialName = "blend";  // ?
	}
	if (pSrc->Get(AI_MATKEY_SHININESS, aiNumVal) == AI_SUCCESS)
		dest->shinness = aiNumVal;
	if (pSrc->Get(AI_MATKEY_TWOSIDED, aiIntVal) == AI_SUCCESS)
		dest->bTwoSided = (aiIntVal != 0);
	dest->metallic = 0.4f;
	dest->roughness = 0.4f;
	return true;
}

bool ImExport::getRoot(void* pDest, const aiScene* pInScene)
{
	const aiNode* pRoot = pInScene->mRootNode;
	if (!(nullptr != pDest && nullptr != pRoot && nullptr == pRoot->mParent))
		return false;
	SDRoot* dest = (SDRoot*)pDest;
	if(nullptr != pRoot->mMeshes && pRoot->mNumMeshes > 0)
		dest->strNodes = String::fromNumArray<uint>(pRoot->mMeshes, pRoot->mNumMeshes).getString();
	//dest->pNodes = nullptr;
	//dest->uNumNode = pRoot->mNumMeshes;
	//if (dest->uNumNode > 0)
	//{
	//	dest->pNodes = new unsigned int[dest->uNumNode];
	//	for (unsigned int i = 0; i < dest->uNumNode; i++)
	//	{
	//		dest->pNodes[i] = pRoot->mMeshes[i];
	//	}
	//}
	return true;
}

void ImExport::write(const std::string& strFile, const aiScene* pScene)
{
	std::ofstream ofs(strFile, std::ios::binary);
	//ofs << pScene->mFlags << " , " << pScene->mNumMeshes << std::endl;
	ofs.write((char*)pScene, sizeof(aiScene));
	ofs.close();
}

void ImExport::read(const std::string& strFile)
{
	std::ifstream ifs(strFile, std::ios::binary);
	//unsigned int uFlags, uNumMeshes;
	//char sz[2];
	//ifs >> uFlags >> sz >> uNumMeshes;
	aiScene scene;
	ifs.read((char*)&scene, sizeof(aiScene));
	ifs.close();
	memset(&scene, 0, sizeof(aiScene));
}
