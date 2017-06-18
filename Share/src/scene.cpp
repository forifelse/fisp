/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#include "../include/scene.h"

namespace fisp
{
	namespace share
	{
		/*-----------------------------------------------------------
		class Scene
		------------------------------------------------------------*/
		Scene::Scene()
		{
		}

		Scene::~Scene()
		{
		}

		void Scene::clear()
		{

		}

		void Scene::flush()
		{

		}

		void Scene::update(float delta)
		{

		}

		void Scene::render(float delta)
		{

		}

		void Scene::onSize()
		{

		}

		bool Scene::writeScene(const SDScene* pScene, const std::string& strPathFile)
		{
			if (nullptr == pScene || nullptr == pScene->pRoot)
				return false;
			//write<SDScene>(pScene, strFile);
			std::ofstream ofs(strPathFile, std::ios::binary);
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
					if (pGeom->bNormal)
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

		bool Scene::readScene(SDScene* pScene, const std::string& strPathFile)
		{
			if (nullptr == pScene)
				return false;
			//read<SDScene>(scene, strFile);
			std::ifstream ifs(strPathFile, std::ios::binary);
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



	}
}