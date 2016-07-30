//
//  Spectrum.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 12/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef Spectrum_hpp
#define Spectrum_hpp

#include "MathUtils.hpp"

template <int numberOfSamples> class Spectrum {
protected:
    
    /// Spectrum sample
    float samples[numberOfSamples];
    
public:
    
    /*!
     Constructor.
     */
    Spectrum() {
        
        for (int i = 0; i < numberOfSamples; i++) {
            
            samples[i] = 0.0f;
        }
    }

    /*!
     Constructor.
     
     @param value value used to init all spectrum wavelenght.
     */
    Spectrum(float value) {
        
        for (int i = 0; i < numberOfSamples; i++) {
            
            samples[i] = value;
        }
    }
    
    /*!
     Constructor.
     
     @param sample[numberOfSamples] samples to be used to init the spectrum.
     */
    Spectrum(float newSamples[numberOfSamples]) {
        
        for (int i = 0; i < numberOfSamples; i++) {
            
            samples[i] = newSamples[i];
        }
    }
    
    /*!
     Constructor.
     
     @param sample[numberOfSamples] the number of samples to be used to init the spectrum.
     */
    Spectrum(const float newSamples[numberOfSamples]) {
        
        for (int i = 0; i < numberOfSamples; i++) {
            
            samples[i] = newSamples[i];
        }
    }
    
    /*!
     Product of two spectrums.
     
     @param otherSpectrum the other spectrum to be multiplied.
     
     @returns a new spectrum as a result of the product between the 2 spectrum.
     */
    Spectrum operator*(const Spectrum<numberOfSamples>& otherSpectrum) const {
        
        Spectrum<numberOfSamples> newSpectrum;
        
        for (int i = 0; i < numberOfSamples; i++) {
            
            newSpectrum.samples[i] = samples[i] * otherSpectrum.samples[i];
        }
        
        return newSpectrum;
    }
    
    /*!
     Product of a spectrum with a scalar.
     
     @param number the number multiplied with the spectrum.
     
     @returns a new spectrum as a result of the product.
     */
    Spectrum operator*(const float number) {
        
        Spectrum<numberOfSamples> newSpectrum;
        
        for (int i = 0; i < numberOfSamples; i++) {
            
            newSpectrum.samples[i] = samples[i] * number;
        }
        
        return newSpectrum;
    }
    
    /*!
     Product of a spectrum with a scalar.
     
     @param number the number multiplied with the spectrum.
     
     @returns a new spectrum as a result of the product.
     */
    Spectrum operator*(const float number) const {
        
        Spectrum<numberOfSamples> newSpectrum;
        
        for (int i = 0; i < numberOfSamples; i++) {
            
            newSpectrum.samples[i] = samples[i] * number;
        }
        
        return newSpectrum;
    }
    
    /*!
     Division of a spectrum with a scalar.
     
     @param number the number multiplied with the spectrum.
     
     @returns a new spectrum as a result of the product.
     */
    Spectrum operator/(const float number) const {
        
        Spectrum<numberOfSamples> newSpectrum;
        
        for (int i = 0; i < numberOfSamples; i++) {
            
            newSpectrum.samples[i] = samples[i] / number;
        }
        
        return newSpectrum;
    }
    
    /*!
     Sum of two spectrum
     
     @param otherSpectrum the other spectrum used during the operation.
     
     @returns a spectrum as a result of the sum.
     */
    Spectrum operator+(const Spectrum& otherSpectrum) {
        
        Spectrum<numberOfSamples> newSpectrum;
        
        for (int i = 0; i < numberOfSamples; i++) {
            
            newSpectrum.samples[i] = samples[i] + otherSpectrum.samples[i];
        }
        
        return newSpectrum;
    }
    
    /*!
     Difference of two spectrum
     
     @param otherSpectrum the other spectrum used during the operation.
     
     @returns a spectrum as a result of the sum.
     */
    Spectrum operator-(const Spectrum& otherSpectrum) {
        
        Spectrum<numberOfSamples> newSpectrum;
        
        for (int i = 0; i < numberOfSamples; i++) {
            
            newSpectrum.samples[i] = samples[i] - otherSpectrum.samples[i];
        }
        
        return newSpectrum;
    }
    
    /*!
     Difference of two spectrum
     
     @param otherSpectrum the other spectrum used during the operation.
     
     @returns a spectrum as a result of the sum.
     */
    bool operator==(float value) {
        
        for (int i = 0; i < numberOfSamples; i++) {
            
            if(samples[i] != value) {
                
                return false;
            }
        }
        
        return true;
    }
    
    /*!
     Overload subscript operator to manipulate samples array after init.
     */
    float& operator[](const int position) {
        
        return samples[position];
    }
    
    /*!
     Clamp spectrum inside a range.
     
     @param low low clamp value.
     @param high high clamp value.
     
     @returns a spectrum with clamp values.
     */
    Spectrum clamp(float low = 0.0f, float high = INFINITY) {
        
        Spectrum<numberOfSamples> newSpectrum;
        
        for (int i = 0; i < numberOfSamples; i++) {
            
            newSpectrum.samples[i] = MathUtils::clamp(samples[i], low, high);
        }
        
        return newSpectrum;
    }
    
    /*!
     Check if some value is not valid
     
     @returns a bool indicating not a number in spectrum.
     */
    bool nanspectrum() {
        
        Spectrum<numberOfSamples> newSpectrum;
        
        for (int i = 0; i < numberOfSamples; i++) {
            
            if(std::isnan(samples[i])) {
                
                return true;
            }
        }
        
        return false;
    }
};

#endif /* Spectrum_hpp */
