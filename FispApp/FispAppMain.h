﻿#pragma once

#include "../Utility/include/useUtility.h"
#include "../Render/include/useRender.h"
#include "../Engine/include/useEngine.h"

// Renders Direct3D content on the screen.
namespace FispApp
{
	class FispAppMain : public IFrame
	{
	public:
		FispAppMain();
		~FispAppMain();

		virtual void setup() override;
		virtual void startup() override;
		virtual void cleanup() override;
		virtual void update(float delta) override;
		virtual void render(float delta) override;
		// init param for render and window
		Render::InitParam* initParamRnd() override;
		// init param for render and window
		const Render::InitParam& initParamRnd() const override;
		IScene* scene() override;
		const IScene* scene() const override;
		void scene(IScene* pScene);


		void CreateRenderers(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		void Update();
		bool Render();

		void OnWindowSizeChanged();
		void OnSuspending();
		void OnResuming();
		void OnDeviceRemoved();

		std::shared_ptr<DX::DeviceResources> GetDeviceResources(const DX::DeviceResources::DeviceParam& param);

	protected:
		void SaveState();
		void LoadState();

	private:
		// TODO: Replace with your own content renderers.
		std::unique_ptr<Sample3DSceneRenderer> m_sceneRenderer;
		std::shared_ptr<DX::DeviceResources> m_deviceResources;
		// Rendering loop timer.
		ITimer*		mpTimer;
		Render::InitParam	mRndParam;
		IScene*				mpSceneRef;

		//
		float	m_angle;
		bool	m_tracking;
	};

	class MainWnd : public IWnd
	{
	public:
		MainWnd();
		~MainWnd();

		virtual void mainSM(IMainSM* pMainSM) override;
		virtual void run() override;
		virtual void show(bool bShow) override;
		virtual String exePath() override;
		virtual bool isUWP() const override;

		void CreateRenderers(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		void Update();
		bool Render();

		void OnWindowSizeChanged();
		void OnSuspending();
		void OnResuming();
		void OnDeviceRemoved();

		std::shared_ptr<DX::DeviceResources> GetDeviceResources(const DX::DeviceResources::DeviceParam& param);

	protected:
		void SaveState();
		void LoadState();

	private:
		// TODO: Replace with your own content renderers.
		std::unique_ptr<Sample3DSceneRenderer> m_sceneRenderer;
		std::shared_ptr<DX::DeviceResources> m_deviceResources;
		// Rendering loop timer.
		ITimer*		mpTimer;

		//
		float	m_angle;
		bool	m_tracking;
	};

}