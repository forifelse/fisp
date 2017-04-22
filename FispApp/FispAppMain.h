#pragma once

#include "../Render/include/useRender.h"
//#include "Content\Sample3DSceneRenderer.h"

// Renders Direct3D content on the screen.
namespace FispApp
{
	class FispAppMain
	{
	public:
		FispAppMain();
		void CreateRenderers(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		void Update();
		bool Render();

		void OnWindowSizeChanged();
		void OnSuspending();
		void OnResuming();
		void OnDeviceRemoved();

	protected:
		void SaveState();
		void LoadState();

	private:
		// TODO: Replace with your own content renderers.
		std::unique_ptr<Sample3DSceneRenderer> m_sceneRenderer;

		// Rendering loop timer.
		StepTimer m_timer;

		//
		float	m_angle;
		bool	m_tracking;
	};
}