#include "pch.h"
#include "App.h"

#include <ppltasks.h>

using namespace FispApp;

//using namespace concurrency;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
//using namespace Windows::UI::Core;
//using namespace Windows::UI::Input;
//using namespace Windows::System;
//using namespace Windows::Foundation;
//using namespace Windows::Graphics::Display;
//
//using Microsoft::WRL::ComPtr;

[Platform::MTAThread]
int main(Platform::Array<Platform::String^>^)
{
	FispAppMain app;
	UWPWnd wnd;
	Fisp::root()->init(&app, &wnd);
	//
	auto viewSource = ref new ViewSource();
	CoreApplication::Run(viewSource);
	return 0;
}

