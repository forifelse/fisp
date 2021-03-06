﻿#pragma once
#include "pch.h"

namespace DX
{
	
	enum EDisplayOrientation
	{
		DisplayOrientation_None = 0,
		DisplayOrientation_Landscape = 1,
		DisplayOrientation_Portrait = 2,
		DisplayOrientation_LandscapeFlipped = 3,
		DisplayOrientation_PortraitFlipped = 4
	};

	static const UINT c_frameCount = 3;		// Use triple buffering.

	// Controls all the DirectX device resources.
	class DeviceD12 : public IDevice
	{
	public:
		struct DeviceParam
		{
			IUnknown* pWnd;
			float width;
			float height;
			EDisplayOrientation eNative;
			EDisplayOrientation eCurrent;
			float dpi;
		};

	public:
		virtual void fullscreen(bool bFullscreen) override;
		virtual void clearRT() override;
		virtual void present(uint uSyncInterval = 0, uint uFlags = 0) override;
		virtual void* deviceHW() override;
		virtual uint backbufferCount() const override;

	public:
		DeviceD12(DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D32_FLOAT);
		void SetWindow(const DeviceD12::DeviceParam& param);
		void SetLogicalSize(float cx, float cy);
		void SetCurrentOrientation(const EDisplayOrientation& eCurrentRotation);
		void SetDpi(float dpi, float cx, float cy);
		void ValidateDevice();
		void WaitForGpu();

		// The size of the render target, in pixels.
		void OutSize(float &cx, float &cy)								{ cx = m_OutWidth; cy = m_OutHeight; }

		// The size of the render target, in dips.
		void LgcSize(float &cx, float &cy)								{ cx = m_LgcWidth; cy = m_LgcHeight; }

		float						GetDpi() const						{ return m_effectiveDpi; }
		bool						IsDeviceRemoved() const				{ return m_deviceRemoved; }

		// D3D Accessors.
		ID3D12Device*				GetD3DDevice() const				{ return m_d3dDevice.Get(); }
		IDXGISwapChain3*			GetSwapChain() const				{ return m_swapChain.Get(); }
		ID3D12Resource*				GetRenderTarget() const				{ return m_renderTargets[m_currentFrame].Get(); }
		ID3D12Resource*				GetDepthStencil() const				{ return m_depthStencil.Get(); }
		ID3D12CommandQueue*			GetCommandQueue() const				{ return m_commandQueue.Get(); }
		ID3D12CommandAllocator*		GetCommandAllocator() const			{ return m_commandAllocators[m_currentFrame].Get(); }
		DXGI_FORMAT					GetBackBufferFormat() const			{ return m_backBufferFormat; }
		DXGI_FORMAT					GetDepthBufferFormat() const		{ return m_depthBufferFormat; }
		D3D12_VIEWPORT				GetScreenViewport() const			{ return m_screenViewport; }
		DirectX::XMFLOAT4X4			GetOrientationTransform3D() const	{ return m_orientationTransform3D; }
		UINT						GetCurrentFrameIndex() const		{ return m_currentFrame; }

		CD3DX12_CPU_DESCRIPTOR_HANDLE GetRenderTargetView() const
		{
			return CD3DX12_CPU_DESCRIPTOR_HANDLE(m_rtvHeap->GetCPUDescriptorHandleForHeapStart(), m_currentFrame, m_rtvDescriptorSize);
		}
		CD3DX12_CPU_DESCRIPTOR_HANDLE GetDepthStencilView() const
		{
			return CD3DX12_CPU_DESCRIPTOR_HANDLE(m_dsvHeap->GetCPUDescriptorHandleForHeapStart());
		}

	private:
		void CreateDeviceIndependentResources();
		void CreateDeviceResources();
		void CreateWindowSizeDependentResources();
		void UpdateRenderTargetSize();
		void MoveToNextFrame();
		DXGI_MODE_ROTATION ComputeDisplayRotation();
		void GetHardwareAdapter(IDXGIAdapter1** ppAdapter);

		UINT											m_currentFrame;

		// Direct3D objects.
		Microsoft::WRL::ComPtr<ID3D12Device>			m_d3dDevice;
		Microsoft::WRL::ComPtr<IDXGIFactory4>			m_dxgiFactory;
		Microsoft::WRL::ComPtr<IDXGISwapChain3>			m_swapChain;
		Microsoft::WRL::ComPtr<ID3D12Resource>			m_renderTargets[c_frameCount];
		Microsoft::WRL::ComPtr<ID3D12Resource>			m_depthStencil;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	m_rtvHeap;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	m_dsvHeap;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue>		m_commandQueue;
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator>	m_commandAllocators[c_frameCount];
		DXGI_FORMAT										m_backBufferFormat;
		DXGI_FORMAT										m_depthBufferFormat;
		D3D12_VIEWPORT									m_screenViewport;
		UINT											m_rtvDescriptorSize;
		bool											m_deviceRemoved;

		// CPU/GPU Synchronization.
		Microsoft::WRL::ComPtr<ID3D12Fence>				m_fence;
		UINT64											m_fenceValues[c_frameCount];
		HANDLE											m_fenceEvent;

		// Cached reference to the Window.
		IUnknown*										m_wnd;

		// Cached device properties.
		float											m_RTWidth, m_RTHeight;
		float											m_OutWidth, m_OutHeight;
		float											m_LgcWidth, m_LgcHeight;
		EDisplayOrientation								m_eCurrentRotation;
		EDisplayOrientation								m_eNativeRotation;
		float											m_dpi;

		// This is the DPI that will be reported back to the app. It takes into account whether the app supports high resolution screens or not.
		float											m_effectiveDpi;

		// Transforms used for display orientation.
		DirectX::XMFLOAT4X4								m_orientationTransform3D;

	};
}
