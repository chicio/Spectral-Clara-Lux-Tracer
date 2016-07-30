//
// Rasterizer.h
// Declaration of the Rasterizer class.
//
// Created by Fabrizio Duroni on 28/12/15.
// Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#pragma once

#include <wrl.h>
#include <robuffer.h>
#include <vector>
#include "Vector3D.hpp"

using namespace Windows::Storage::Streams;
using namespace Microsoft::WRL;
using namespace Windows::UI::Xaml::Media::Imaging;

typedef uint8 byte;

namespace SpectralClaraLuxTracer {

	class Rasterizer {
	private:

		/*!
		 Method used to get a reference to the byte buffer used 
		 by WritableBitmap to store the color of each pixel.

		 @param pixelBuffer referenced array of bytes used by byte stream (in this case WritableBitmap).
		 @param lenght lenght of the buffer.

		 @returns pointer to array of byte.
		 */
		byte* getPointerToPixelData(IBuffer^ pixelBuffer, unsigned int *length);

	public:

		Rasterizer() {};

		/*!
		 Convert an array of pixel to Image object to be displayed.

		 @param pixels array of pixels.
		 @param width of the image.
		 @param height of the image.

		 @returns WriteableBitmap^ ref.
		 */
		WriteableBitmap^ rasterize(const std::vector<Vector3D> pixels, int width, int height);
	};
}