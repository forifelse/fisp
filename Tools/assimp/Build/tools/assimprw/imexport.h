#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class ImExport
{
public:
	bool load(const std::string& strInFile, const std::string& strFormat, const std::string& strContent, const std::string& strOutFile);
	void write(const std::string& strFile, const aiScene* pScene);
	void read(const std::string& strFile);

protected:
	bool getScene(void* pOutScene, const aiScene* pInScene);

private:
	bool getGeom(void* pDest, const aiMesh* pSrc);
	bool getMaterial(void* pDest, const aiMaterial* pSrc);
	bool getMesh(void* pDest, const aiMesh* pSrc);
	bool getRoot(void* pDest, const aiScene* pInScene);
	unsigned int nodeNum(const aiNode* pRoot);
	void traveNodes(void* pDest, unsigned int uIdx, unsigned int uParent, const aiNode* pInNode);

private:
	//aiScene*	mpScene;
	//SDScene*	mpSDScene;
};
