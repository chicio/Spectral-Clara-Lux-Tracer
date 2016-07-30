#include "pch.h"
#include "CppUnitTest.h"
#include "Spectrum.hpp"
#include "Constants.hpp"
#include "Illuminant.hpp"
#include "MacbethColorChecker.hpp"
#include "Spectrum.hpp"
#include "ColorRenderingIndex.hpp"
#include "ColorMatchingFunction.hpp"
#include "CIEXYZ.hpp"
#include "sRGB.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
    TEST_CLASS(UnitTest1)
    {
    public:
        TEST_METHOD(CRITestSamplesMethod)
        {
			Spectrum<constant::spectrumSamples> spectrumfl4(Illuminant::fl4);
			ColorRenderingIndex cri;
			float criTestSample = cri.testSampleMethod(spectrumfl4);

			Assert::IsTrue(criTestSample >= 50.8f);
			Assert::IsTrue(criTestSample <= 51.2f);
		}

		TEST_METHOD(CRIR96aMethod)
		{
			Spectrum<constant::spectrumSamples> spectrumfl4(Illuminant::fl4);
			ColorRenderingIndex cri;
			float crir96a = cri.r96aMethod(spectrumfl4);

			Assert::IsTrue(crir96a > 50.0f);
			Assert::IsTrue(crir96a < 60.0f);
		}

		TEST_METHOD(TristimulusValuesConversion)
		{
			const int colorToBeTested = 5;
			ColorMatchingFunction* colorMatchingFunction = new Standard2ObserverColorMatchingFunction();

			//Test main color from macbeth color checker (most used in scenes).
			Spectrum<constant::spectrumSamples> macbethSPD[colorToBeTested] = {
				Spectrum<constant::spectrumSamples>(MacbethColorChecker::red),
				Spectrum<constant::spectrumSamples>(MacbethColorChecker::yellow),
				Spectrum<constant::spectrumSamples>(MacbethColorChecker::green),
				Spectrum<constant::spectrumSamples>(MacbethColorChecker::blue),
				Spectrum<constant::spectrumSamples>(MacbethColorChecker::orange)
			};

			Vector3D macbethSRGB[colorToBeTested] = {
				Vector3D(176.0f,  48.0f,  56.0f),
				Vector3D(238.0f, 200.0f,  22.0f),
				Vector3D(71.0f, 149.0f,  72.0f),
				Vector3D(43.0f,  62.0f, 147.0f),
				Vector3D(220.0f, 123.0f,  45.0f)
			};

			//Consider a margin error during the conversion process.
			const float error = 5.0f;

			for (int i = 0; i < colorToBeTested; i++) {

				Spectrum<constant::spectrumSamples> d65(Illuminant::d65);
				Spectrum<constant::spectrumSamples> colorIlluminantProduct = macbethSPD[i] * d65;

				Vector3D tristimulus = CIE1931XYZ::tristimulusValues(colorIlluminantProduct, d65, colorMatchingFunction);
				Vector3D rgb = CIE1931XYZ::tristimulusTosRGB(tristimulus);

				//Apply sRGB gamma correction.
				sRGB::sRGBGammaCorrection(rgb, sRGBCompading);

				//Convert to standard 0 - 255 RGB value.
				sRGB::sRGBStandardRange(rgb);

				//R component.
				Assert::IsTrue(rgb.x < macbethSRGB[i].x + error);
				Assert::IsTrue(rgb.x > macbethSRGB[i].x - error);

				//G component.
				Assert::IsTrue(rgb.y < macbethSRGB[i].y + error);
				Assert::IsTrue(rgb.y > macbethSRGB[i].y - error);

				//B component.
				Assert::IsTrue(rgb.z < macbethSRGB[i].z + error);
				Assert::IsTrue(rgb.z > macbethSRGB[i].z - error);
			}
		}
    };
}
