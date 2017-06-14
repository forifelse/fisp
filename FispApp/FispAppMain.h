#pragma once

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