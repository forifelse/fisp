#include "pch.h"
#include "FispAppMain.h"
using Microsoft::WRL::ComPtr;

using namespace FispApp;
using namespace Windows::Foundation;
using namespace Windows::System::Threading;
using namespace Concurrency;
using namespace Windows::Storage;

// The DirectX 12 Application template is documented at https://go.microsoft.com/fwlink/?LinkID=613670&clcid=0x409
// Indices into the application state map.
Platform::String^ AngleKey = "Angle";
Platform::String^ TrackingKey = "Tracking";

// Loads and initializes application assets when the application is loaded.
FispAppMain::FispAppMain()
{
	// TODO: Change the timer settings if you want something other than the default variable timestep mode.
	// e.g. for 60 FPS fixed timestep update logic, call:
	/*
	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60);
	*/
	mpTimer = Timer::createMem<Timer>();
}

FispAppMain::~FispAppMain()
{
	Timer::destroyMem<ITimer>(mpTimer);
}

void FispAppMain::setup()
{

}

void FispAppMain::startup()
{

}

void FispAppMain::cleanup()
{

}

void FispAppMain::update(float delta)
{

}

void FispAppMain::render(float delta)
{

}

Render::InitParam* FispAppMain::initParamRnd()
{
	return &mRndParam;
}

const Render::InitParam& FispAppMain::initParamRnd() const
{
	return mRndParam;
}

IScene* FispAppMain::scene()
{
	return mpSceneRef;
}

const IScene* FispAppMain::scene() const
{
	return mpSceneRef;
}

void FispAppMain::scene(IScene* pScene)
{
	mpSceneRef = pScene;
}

// Creates and initializes the renderers.
void FispAppMain::CreateRenderers(const std::shared_ptr<DX::DeviceD12>& deviceResources)
{
	m_deviceResources = deviceResources;
	// TODO: Replace this with your app's content initialization.
	//m_pMeshD12 = std::unique_ptr<MeshD12>(new MeshD12(deviceResources));
	m_pMeshD12 = std::unique_ptr<MeshD12>(new MeshD12(deviceResources.get()));
	LoadState();
	OnWindowSizeChanged();
}

// Updates the application state once per frame.
void FispAppMain::Update()
{
	// Update scene objects.
	float delta = mpTimer->tick();
	//
	if (m_pMeshD12->isLoaded())
	{
		if (!m_tracking)
		{
			// Rotate the cube a small amount.
			m_angle += static_cast<float>(mpTimer->delta());
			m_pMeshD12->rotate(m_angle);
		}
	}
	// TODO: Replace this with your app's content update functions.
	m_pMeshD12->update(delta);
}

// Renders the current frame according to the current application state.
// Returns true if the frame was rendered and is ready to be displayed.
bool FispAppMain::Render()
{
	// Don't try to render anything before the first Update.
	const float delta = mpTimer->elapse();
	if (delta <= 0)
		return false;

	// Render the scene objects.
	// TODO: Replace this with your app's content rendering functions.
	m_pMeshD12->render(delta);
	return true;
}

// Updates application state when the window's size changes (e.g. device orientation change)
void FispAppMain::OnWindowSizeChanged()
{
	// TODO: Replace this with the size-dependent initialization of your app's content.
	m_pMeshD12->onSize();// > CreateWindowSizeDependentResources();
}

// Notifies the app that it is being suspended.
void FispAppMain::OnSuspending()
{
	// TODO: Replace this with your app's suspending logic.

	// Process lifetime management may terminate suspended apps at any time, so it is
	// good practice to save any state that will allow the app to restart where it left off.

	//m_sceneRenderer->SaveState();
	SaveState();

	// If your application uses video memory allocations that are easy to re-create,
	// consider releasing that memory to make it available to other applications.
}

// Notifes the app that it is no longer suspended.
void FispAppMain::OnResuming()
{
	// TODO: Replace this with your app's resuming logic.
}

// Notifies renderers that device resources need to be released.
void FispAppMain::OnDeviceRemoved()
{
	// TODO: Save any necessary application or renderer state and release the renderer
	// and its resources which are no longer valid.
	//m_sceneRenderer->SaveState();
	SaveState();
	m_pMeshD12 = nullptr;
}

// Saves the current state of the renderer.
void FispAppMain::SaveState()
{
	auto state = ApplicationData::Current->LocalSettings->Values;

	if (state->HasKey(AngleKey))
	{
		state->Remove(AngleKey);
	}
	if (state->HasKey(TrackingKey))
	{
		state->Remove(TrackingKey);
	}

	state->Insert(AngleKey, PropertyValue::CreateSingle(m_angle));
	state->Insert(TrackingKey, PropertyValue::CreateBoolean(m_tracking));
}

// Restores the previous state of the renderer.
void FispAppMain::LoadState()
{
	auto state = ApplicationData::Current->LocalSettings->Values;
	if (state->HasKey(AngleKey))
	{
		m_angle = safe_cast<IPropertyValue^>(state->Lookup(AngleKey))->GetSingle();
		state->Remove(AngleKey);
	}
	if (state->HasKey(TrackingKey))
	{
		m_tracking = safe_cast<IPropertyValue^>(state->Lookup(TrackingKey))->GetBoolean();
		state->Remove(TrackingKey);
	}
}

std::shared_ptr<DX::DeviceD12> FispAppMain::GetDeviceResources(const DX::DeviceD12::DeviceParam& param)
{
	if (m_deviceResources != nullptr && m_deviceResources->IsDeviceRemoved())
	{
		// All references to the existing D3D device must be released before a new device can be created.
		m_deviceResources = nullptr;
		OnDeviceRemoved();

#if defined(_DEBUG)
		ComPtr<IDXGIDebug1> dxgiDebug;
		if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&dxgiDebug))))
		{
			dxgiDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_FLAGS(DXGI_DEBUG_RLO_SUMMARY | DXGI_DEBUG_RLO_IGNORE_INTERNAL));
		}
#endif
	}

	if (m_deviceResources == nullptr)
	{
		m_deviceResources = std::make_shared<DX::DeviceD12>();
		//m_deviceResources->SetWindow(reinterpret_cast<IUnknown*>(wnd), w, h, eNat, eCur, LogicalDpi);
		m_deviceResources->SetWindow(param);
		CreateRenderers(m_deviceResources);
	}
	return m_deviceResources;
}





// Loads and initializes application assets when the application is loaded.
UWPWnd::UWPWnd()
{
	// TODO: Change the timer settings if you want something other than the default variable timestep mode.
	// e.g. for 60 FPS fixed timestep update logic, call:
	/*
	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60);
	*/
	mpTimer = Timer::createMem<Timer>();
}

UWPWnd::~UWPWnd()
{
	Timer::destroyMem<ITimer>(mpTimer);
}

void UWPWnd::run()
{
	mpMainSM->render();
}

void UWPWnd::show(bool bShow)
{

}

String UWPWnd::exePath()
{
	return "";
}

bool UWPWnd::isUWP() const
{
	return true;
}

IMainSM* UWPWnd::mainSM()
{
	return 0;
}

const IMainSM* UWPWnd::mainSM() const
{
	return 0;
}

void UWPWnd::mainSM(IMainSM* pMainSM)
{
	mpMainSM = pMainSM;
}

//// Creates and initializes the renderers.
//void MainWnd::CreateRenderers(const std::shared_ptr<DX::DeviceResources>& deviceResources)
//{
//	m_deviceResources = deviceResources;
//	// TODO: Replace this with your app's content initialization.
//	m_sceneRenderer = std::unique_ptr<Sample3DSceneRenderer>(new Sample3DSceneRenderer(deviceResources));
//	LoadState();
//	OnWindowSizeChanged();
//}
//
//// Updates the application state once per frame.
//void MainWnd::Update()
//{
//	// Update scene objects.
//	mpTimer->tick();
//	//
//	if (m_sceneRenderer->loadingComplete())
//	{
//		if (!m_tracking)
//		{
//			// Rotate the cube a small amount.
//			m_angle += static_cast<float>(mpTimer->delta());
//			m_sceneRenderer->Rotate(m_angle);
//		}
//	}
//	// TODO: Replace this with your app's content update functions.
//	m_sceneRenderer->Update();
//}
//
//// Renders the current frame according to the current application state.
//// Returns true if the frame was rendered and is ready to be displayed.
//bool MainWnd::Render()
//{
//	// Don't try to render anything before the first Update.
//	if (mpTimer->elapse() <= 0)
//	{
//		return false;
//	}
//
//	// Render the scene objects.
//	// TODO: Replace this with your app's content rendering functions.
//	return m_sceneRenderer->Render();
//}

// Updates application state when the window's size changes (e.g. device orientation change)
void UWPWnd::OnWindowSizeChanged()
{
	// TODO: Replace this with the size-dependent initialization of your app's content.
	mpMainSM->appFrame()->scene()->onSize();
	//m_sceneRenderer->CreateWindowSizeDependentResources();

}

// Notifies the app that it is being suspended.
void UWPWnd::OnSuspending()
{
	// TODO: Replace this with your app's suspending logic.

	// Process lifetime management may terminate suspended apps at any time, so it is
	// good practice to save any state that will allow the app to restart where it left off.

	//m_sceneRenderer->SaveState();
	SaveState();

	// If your application uses video memory allocations that are easy to re-create,
	// consider releasing that memory to make it available to other applications.
}

// Notifes the app that it is no longer suspended.
void UWPWnd::OnResuming()
{
	// TODO: Replace this with your app's resuming logic.
}

// Notifies renderers that device resources need to be released.
void UWPWnd::OnDeviceRemoved()
{
	// TODO: Save any necessary application or renderer state and release the renderer
	// and its resources which are no longer valid.
	//m_sceneRenderer->SaveState();
	SaveState();
	//m_sceneRenderer = nullptr;
}

// Saves the current state of the renderer.
void UWPWnd::SaveState()
{
	auto state = ApplicationData::Current->LocalSettings->Values;

	if (state->HasKey(AngleKey))
	{
		state->Remove(AngleKey);
	}
	if (state->HasKey(TrackingKey))
	{
		state->Remove(TrackingKey);
	}

	state->Insert(AngleKey, PropertyValue::CreateSingle(m_angle));
	state->Insert(TrackingKey, PropertyValue::CreateBoolean(m_tracking));
}

// Restores the previous state of the renderer.
void UWPWnd::LoadState()
{
	auto state = ApplicationData::Current->LocalSettings->Values;
	if (state->HasKey(AngleKey))
	{
		m_angle = safe_cast<IPropertyValue^>(state->Lookup(AngleKey))->GetSingle();
		state->Remove(AngleKey);
	}
	if (state->HasKey(TrackingKey))
	{
		m_tracking = safe_cast<IPropertyValue^>(state->Lookup(TrackingKey))->GetBoolean();
		state->Remove(TrackingKey);
	}
}

//std::shared_ptr<DX::DeviceResources> MainWnd::GetDeviceResources(const DX::DeviceResources::DeviceParam& param)
//{
//	if (m_deviceResources != nullptr && m_deviceResources->IsDeviceRemoved())
//	{
//		// All references to the existing D3D device must be released before a new device can be created.
//		m_deviceResources = nullptr;
//		OnDeviceRemoved();
//
//#if defined(_DEBUG)
//		ComPtr<IDXGIDebug1> dxgiDebug;
//		if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&dxgiDebug))))
//		{
//			dxgiDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_FLAGS(DXGI_DEBUG_RLO_SUMMARY | DXGI_DEBUG_RLO_IGNORE_INTERNAL));
//		}
//#endif
//	}
//
//	if (m_deviceResources == nullptr)
//	{
//		m_deviceResources = std::make_shared<DX::DeviceResources>();
//		//m_deviceResources->SetWindow(reinterpret_cast<IUnknown*>(wnd), w, h, eNat, eCur, LogicalDpi);
//		m_deviceResources->SetWindow(param);
//		CreateRenderers(m_deviceResources);
//	}
//	return m_deviceResources;
//}


