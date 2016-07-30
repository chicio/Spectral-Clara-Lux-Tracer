//
//  Rasterizer.cpp
//  RayTracing
//
//  Created by Fabrizio Duroni on 28/12/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "Rasterizer.h"

WriteableBitmap^ SpectralClaraLuxTracer::Rasterizer::rasterize(const std::vector<Vector3D> pixels, int imageWidth, int imageHeight) {

	WriteableBitmap^ bm = ref new WriteableBitmap(imageWidth, imageHeight);

	unsigned int length;
	byte* sourcePixels = getPointerToPixelData(bm->PixelBuffer, &length);
	const unsigned int width = bm->PixelWidth;
	const unsigned int height = bm->PixelHeight;

	int rowPosition = 0;

	for (unsigned int k = 0; k < height; k++) {

		for (unsigned int i = 0; i < (width * 4); i += 4) {

			Vector3D pixelColor = pixels[(height - k - 1) * width + rowPosition];

			int pos = k * (width * 4) + (i);
			sourcePixels[pos] = (byte)pixelColor.z; //Blue
			sourcePixels[pos + 1] = (byte)pixelColor.y; //Green
			sourcePixels[pos + 2] = (byte)pixelColor.x; //Red
			sourcePixels[pos + 3] = 255;

			rowPosition++;
		}

		//Reset row position.
		rowPosition = 0;
	}

	return bm;
}

byte* SpectralClaraLuxTracer::Rasterizer::getPointerToPixelData(IBuffer^ pixelBuffer, unsigned int *length) {

	if (length != nullptr) {

		*length = pixelBuffer->Length;
	}

	//Query the IBufferByteAccess interface.
	ComPtr<IBufferByteAccess> bufferByteAccess;
	reinterpret_cast<IInspectable*>(pixelBuffer)->QueryInterface(IID_PPV_ARGS(&bufferByteAccess));

	//Retrieve the buffer data.
	byte* pixels = nullptr;
	bufferByteAccess->Buffer(&pixels);

	return pixels;
}
