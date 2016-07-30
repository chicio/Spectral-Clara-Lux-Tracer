//
//  MainPage.xaml.cpp
//  Spectral Clara Lux Tracer
//
//  Created by Fabrizio Duroni on 30/12/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "Rasterizer.h"
#include "Support.h"
#include "ColorRenderingIndex.hpp"

using namespace SpectralClaraLuxTracer;
using namespace Platform;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Popups;
using namespace Windows::UI::ViewManagement;

MainPage::MainPage() {

	InitializeComponent();

	this->endTrace = false;

	//Fade out UI elements.
	fadeOutProgressBarAnimation->Begin();
	fadeOutRenderingTimeAnimation->Begin();
}

void SpectralClaraLuxTracer::MainPage::startRayTracingAction(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {

	//Setup UI:
	//- reset rasterImage
	//- disable start ray tracing button
	//- show progress bar
	//- hide rendering time box
	rasterImage->Source = nullptr;
	startRayTracingButton->IsEnabled = false;
	fadeOutRenderingTimeAnimation->Begin();
	fadeInProgressBarAnimation->Begin();

	//Init view plane.
	viewPlane = ViewPlane(600, 600);

	//Get scene name and number of sample for anti-aliasing.
	//Convert String^ to std::string.
	std::wstring sceneNameWideString(sceneNameTextBox->Text->Data());
	std::string sceneNameString(sceneNameWideString.begin(), sceneNameWideString.end());

	if (sceneNameString == "") {

		MessageDialog^ msg = ref new MessageDialog(
			"Scene name not valid.",
			"Scene not valid"
			);
		msg->ShowAsync();
	}

	std::wstring antialiasingNumSampleWideString(antialiasingNumSampleTextBox->Text->Data());
	std::string antialiasingNumSampleString(antialiasingNumSampleWideString.begin(), antialiasingNumSampleWideString.end());
	int antialiasingNumOfSample = atoi(antialiasingNumSampleString.c_str());

	auto task = executeRayTracerAsync(sceneNameString, antialiasingNumOfSample);

	task.then([this](std::vector<Vector3D> pixels) {
		Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal,
			ref new Windows::UI::Core::DispatchedHandler([this, pixels]() {

				//Print image only if we receive pixels.
				if (pixels.size() > 0) {

					//Rasterize: create a bitmap from the array of pixels generated.
					WriteableBitmap^ rasterizedBitmapImage = Rasterizer().rasterize(pixels, viewPlane.width, viewPlane.height);
					
					//Show image on screen.
					rasterImage->Source = rasterizedBitmapImage;

					this->endTrace = true;
				}

				//Reset UI State.
				this->rayTracerEndTime = time(NULL);
				startRayTracingButton->IsEnabled = true;
				fadeOutProgressBarAnimation->Begin();
			}
		));
	});
}

concurrency::task<std::vector<Vector3D>> SpectralClaraLuxTracer::MainPage::executeRayTracerAsync(std::string sceneNameString, int antialiasingNumOfSample) {

	this->rayTracerStartTime = time(NULL);

	return create_task([this, sceneNameString, antialiasingNumOfSample]() -> std::vector<Vector3D> {

		std::vector<Vector3D> pixels;

		//Init ray tracer.
		SCLT scltRayTracer(viewPlane, sceneNameString, antialiasingNumOfSample);

		std::string sceneErrorsDescription;

		//Scene is not valid
		if (!scltRayTracer.validScene(sceneErrorsDescription)) {

			Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal,
				ref new Windows::UI::Core::DispatchedHandler([this, sceneErrorsDescription]() {

					std::wstring sceneErrorsDescriptionWideString(sceneErrorsDescription.begin(), sceneErrorsDescription.end());

					//Set rendering time message on UI and start fade in animation.
					String^ sceneErrorsDescriptionPlatformString = ref new String(sceneErrorsDescriptionWideString.c_str());

					MessageDialog^ msg = ref new MessageDialog(
						sceneErrorsDescriptionPlatformString,
						"Scene not valid"
					);
					msg->ShowAsync();
				}
			));

			return pixels;
		}

		//Set the delegate.
		scltRayTracer.setDelegate(this);

		//Run ray tracer.
		pixels = scltRayTracer.runSCLTRayTracer();

		return pixels;
	});
}

void SpectralClaraLuxTracer::MainPage::calibrateCRIAction(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {

	//Calibrate CRI with f4 illuminant.
	Spectrum<constant::spectrumSamples> spectrumF4(Illuminant::fl4);

	//Show CRI.
	this->cri(spectrumF4);
}

void SpectralClaraLuxTracer::MainPage::calculateCRIAction(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {

	//Init scene.
	std::wstring sceneNameWideString(sceneNameTextBox->Text->Data());
	std::string sceneNameString(sceneNameWideString.begin(), sceneNameWideString.end());
	Scene sceneSelected(sceneNameString);

	//Check if we can calculate the CRI for the selected scene.
	if (sceneSelected.tracerModelType == TracerRGBModel) {

		MessageDialog^ msg = ref new MessageDialog(
			"CRI not available for a RGB scene.",
			"Color Rendering Index"
			);
		msg->ShowAsync();

		return;
	}

	//Calculate CRI for the scene light.
	this->cri(sceneSelected.light->spectrum);
}

void SpectralClaraLuxTracer::MainPage::cri(Spectrum<constant::spectrumSamples> light) {

	ColorRenderingIndex cri;
	float criTestSample = cri.testSampleMethod(light);
	float criR96a = cri.r96aMethod(light);

	//Setup message.
	String^ resultMessage = "Test sample method: " + criTestSample.ToString() + "\nR96a: " + criR96a.ToString();

	// Create and show the message dialog.
	MessageDialog^ msg = ref new MessageDialog(resultMessage, "Color Rendering Index");
	msg->ShowAsync();
}

void SpectralClaraLuxTracer::MainPage::update(float progress) {

	Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal,
		ref new Windows::UI::Core::DispatchedHandler([this, progress]() {

			rayTracerProgressBar->Value = progress;
		}
	));
}

void SpectralClaraLuxTracer::MainPage::fadeInThemeAnimationCompletedOnProgressBar(Platform::Object^ sender, Platform::Object^ e) {

	if (this->endTrace == false) {

		//Called on start (not tracing operation).
		//No need to animate.
		return;
	}

	//Calculate time and prepare rendering time message.
	double secondsRendering = difftime(this->rayTracerEndTime, this->rayTracerStartTime);

	int hour = lround(floor(secondsRendering / 3600)) % 100;
	int minute = lround(floor(secondsRendering / 60)) % 60;
	int seconds = lround(floor(secondsRendering)) % 60;

	std::string renderingTimeString = Support::stringFormat("Rendering time %02d:%02d:%02d", hour, minute, seconds);
	std::wstring renderingTimeWideString(renderingTimeString.begin(), renderingTimeString.end());

	//Set rendering time message on UI and start fade in animation.
	renderingTimeTextBlock->Text = ref new String(renderingTimeWideString.c_str());
	fadeInRenderingTimeAnimation->Begin();

	//Reset trace operation state flag.
	this->endTrace = false;
}
