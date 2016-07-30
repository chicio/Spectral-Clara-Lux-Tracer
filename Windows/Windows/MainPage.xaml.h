//
//  MainPage.xaml.h
//  Spectral Clara Lux Tracer
//
//  Created by Fabrizio Duroni on 30/12/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#pragma once

#include "MainPage.g.h"

#include <wrl.h>
#include <robuffer.h>
#include "SCLT.hpp"
#include <atomic>
#include <collection.h>
#include <ppltasks.h>
#include <concurrent_vector.h>

using namespace Windows::Storage::Streams;
using namespace Microsoft::WRL;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace concurrency;

typedef uint8 byte;

namespace SpectralClaraLuxTracer {

	/*!
	 Class that represent the main application interface
	 of the ray tracer.
	 */
	public ref class MainPage sealed{
	public:

		/*!
		 Default constructor.
		 */
		MainPage();

		/*!
		 Method call on delegation from the ray tracer
		 to update the progress bar (on UI thread).

		 @param progress percentage of render completed.
		*/
		void update(float progress);

	private:

		/// Start time of ray tracing operation.
		time_t rayTracerStartTime;

		/// Start time of ray tracing operation.
		time_t rayTracerEndTime;

		/// View plane.
		ViewPlane viewPlane;

		/// Flag used to check if the ray tracer has ended the calculation.
		bool endTrace;

		/// Bitmao used to show the result of the ray tracer,
		WriteableBitmap^ rasterizedBitmapImage;

		/*!
		  Start the ray tracer operation with the selected parameter.

		  @param sender the sender of the action.
		  @param e arguments from the sender.
		 */
		void startRayTracingAction(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		
		/*!
		 Calculate CRI action.

		 @param sender the sender of the action.
		 @param e arguments from the sender.
		 */
		void calculateCRIAction(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

		/*!
		 Calibrate CRI action.

		 @param sender the sender of the action.
		 @param e arguments from the sender.
		 */
		void calibrateCRIAction(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

		/*
		 Execute cri methods.

		 @param light light on which we calculate CRI.
		 */
		void cri(Spectrum<constant::spectrumSamples> light);

		/*!
		 Method used to launch the ray tracer render in a backgroudn
		 thread. In this way, using task, I avoid UI blocking and
		 I can show progress updates.

		 @param sceneNameString name of scene as std::string
		 @antialiasingNumOfSample number of sample to be used for AA.

		 @returns concurrency::task.
		*/
		concurrency::task<std::vector<Vector3D>> executeRayTracerAsync(std::string sceneNameString,
																	   int antialiasingNumOfSample);

		/*!
		 Event launched on completion on fade out animation of the progress bar.

		 @param sender the sender of the action.
		 @param e arguments from the sender.
		*/
		void fadeInThemeAnimationCompletedOnProgressBar(Platform::Object^ sender, Platform::Object^ e);
	};
}
