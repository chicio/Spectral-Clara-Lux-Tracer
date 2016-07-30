//
//  MeasuredBRDF.hpp
//  Framework
//
//  Created by Fabrizio Duroni on 19/01/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#ifndef MeasuredBRDF_hpp
#define MeasuredBRDF_hpp

#include <vector>

#include "MathUtils.hpp"
#include "Spectrum.hpp"
#include "BRDF.hpp"

struct MeasuredBRDFSample {
    
    /// Coordinate of the sample remapped using maschner BRDF Mapping.
    Point3D coordinate;
    /// spectrum of the brdf sample.
    Spectrum<constant::spectrumSamples> spectrum;
};

class Measured : public BRDF {
private:

    /// Sample of brdf read from astm file.
    std::vector<MeasuredBRDFSample> sampleBRDF;
    /// If true, brdf samples spectrum will be interpolated (useful on Whitted model).
    bool samplesInterpolated;
    
    /*!
     Generate a complete spectrum starting from sample of measure BRDF taken from cornell university reflectance data.
     If needed, interpolate data for wavelenght not contained in sample spectrum.
     
     @param startSampleWavelenght 
     @param endSampleWavelenght
     @param distanceBetweenSample
     @param samples
     @param numberOfSamples
     
     @returns sample spectrum, interpolated if needed for wavelenght not containes in measure reflectance data.
     */
    Spectrum<constant::spectrumSamples> generateSpectrumFromSample(float startSampleWavelenght,
                                                                   float endSampleWavelenght,
                                                                   float distanceBetweenSample,
                                                                   float* samples,
                                                                   int numberOfSamples);
    
    /*!
     Map BRDF measured data from cornell university using the method described in Marschner Ph.D. thesis (1998).
     
     @param wo outgoing direction.
     @param wi incident direction.
     
     @returns remapped BRDF data point.
     */
    Point3D marschnerBRDFMapping(const Vector3D &wo, const Vector3D &wi) const;
    
public:
    
    /*!
     Constructor.
     
     @param reflectanceSpectrum the reflectance spectrum.
     @param interpolated if true, samples spectrum will be linearly interpolated.
     */
    Measured(const char* filename, bool interpolated);
    
    /*!
     Compute BRDF for the given direction using measured BRDF model.
     
     @param wi incident direction.
     @param wo outgoing direction.
     
     @returns BRDF.
     */
    Spectrum<constant::spectrumSamples> f(const Vector3D& wi,
                                          const Vector3D& wo,
                                          const Intersection& intersection) const;
    
    /*!
     Computed BRDF and sample wi direction for measured BRDF model.
     Useful on Monte carlo models (e.g. Path tracing).
     
     @param wi incident direction.
     @param wo outgoing direction.
     @param intersection intersection data.
     
     @returns BRDF and wi.
     */
    Spectrum<constant::spectrumSamples> samplef(Vector3D* wi,
                                                const Vector3D& wo,
                                                const Intersection& intersection) const;
    
    /*!
     Probability density function for measured BRDF model.
     
     @param wi incident direction.
     @param wo outgoing direction.
     @param intersection intersection data.
     
     @returns pdf.
     */
    float pdf(const Vector3D& wi, const Vector3D& wo, const Intersection& intersection) const;
};

#endif /* MeasuredBRDF_hpp */
