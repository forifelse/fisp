﻿#pragma once

#include <wrl.h>
#include <wrl/client.h>
#include <dxgi1_4.h>
#include <d3d12.h>
//#include "Common\d3dx12.h"
#include <pix.h>
#include <DirectXColors.h>
#include <DirectXMath.h>
#include <memory>
#include <vector>
//#include <agile.h>
#include <concrt.h>

#if defined(_DEBUG)
#include <dxgidebug.h>
#endif

#include "../../Utility/include/useUtility.h"
#include "DeviceResources.h"
//#include "ShaderStructures.h"
//#include "../Render/include/useRender.h"
//#include "ShaderStructures.h"

namespace FispApp
{
	// Function that reads from a binary file asynchronously.
	//inline Concurrency::task<std::vector<byte>> ReadDataAsync(const std::wstring& filename)
	//{
	//	using namespace Windows::Storage;
	//	using namespace Concurrency;

	//	auto folder = Windows::ApplicationModel::Package::Current->InstalledLocation;

	//	return create_task(folder->GetFileAsync(Platform::StringReference(filename.c_str()))).then([](StorageFile^ file)
	//	{
	//		return FileIO::ReadBufferAsync(file);
	//	}).then([](Streams::IBuffer^ fileBuffer) -> std::vector<byte>
	//	{
	//		std::vector<byte> returnBuffer;
	//		returnBuffer.resize(fileBuffer->Length);
	//		Streams::DataReader::FromBuffer(fileBuffer)->ReadBytes(Platform::ArrayReference<byte>(returnBuffer.data(), fileBuffer->Length));
	//		return returnBuffer;
	//	});
	//}

	// Constant buffer used to send MVP matrices to the vertex shader.
	struct ModelViewProjectionConstantBuffer
	{
		DirectX::XMFLOAT4X4 model;
		DirectX::XMFLOAT4X4 view;
		DirectX::XMFLOAT4X4 projection;
	};

	// Used to send per-vertex data to the vertex shader.
	struct VertexPositionColor
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 color;
	};

	// This sample renderer instantiates a basic rendering pipeline.
	class MeshD12 : public IMeshRender
	{
	public:
		MeshD12(IDevice* pDevice);
		~MeshD12();

	public:
		void device(IDevice* pDevice) override;
		void build(IEntity*	pEntity) override;
		void update(float delta) override;
		void render(float delta) override;

	private:
		IDevice*	mpDeviceRef;

	public:
		void onSize();
		bool isLoaded() const { return m_loadingComplete; }
		void rotate(float radians);

	private:
		// Constant buffers must be 256-byte aligned.
		static const UINT c_alignedConstantBufferSize = (sizeof(ModelViewProjectionConstantBuffer) + 255) & ~255;

		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceD12> m_deviceResources;

		// Direct3D resources for cube geometry.
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>	m_commandList;
		Microsoft::WRL::ComPtr<ID3D12RootSignature>			m_rootSignature;
		Microsoft::WRL::ComPtr<ID3D12PipelineState>			m_pipelineState;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>		m_cbvHeap;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_vertexBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_indexBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_constantBuffer;
		ModelViewProjectionConstantBuffer					m_constantBufferData;
		UINT8*												m_mappedConstantBuffer;
		UINT												m_cbvDescriptorSize;
		D3D12_RECT											m_scissorRect;
		D3D12_VERTEX_BUFFER_VIEW							m_vertexBufferView;
		D3D12_INDEX_BUFFER_VIEW								m_indexBufferView;

		// Variables used with the rendering loop.
		bool	m_loadingComplete;
		float	m_radiansPerSecond;
		//float	m_angle;
		//bool	m_tracking;
	};
}

