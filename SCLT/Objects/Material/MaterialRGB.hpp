//
//  Material.h
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 05/07/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef MaterialRGB_hpp
#define MaterialRGB_hpp

#include "Material.hpp"
#include "Vector3D.hpp"

class MaterialRGB : public Material {
public:
    
    /// Flag used to check if material is refractive.
    bool isReflective;
    /// Flag used to check if material is transmissive.
    bool isTransmissive;
    /// Refractive index.
    float refractiveIndex;
    /// Shiness property.
    float sh;    
    /// Emissive component.
    Vector3D ke;
    /// Ambient component.
    Vector3D ka;
    /// Diffusive component.
    Vector3D kd;
    /// Specular component.
    Vector3D ks;
    
    /*!
     Convenience initializer: Jade.
     */
    static Material* jade();
    
    /*!
     Convenience initializer: Bronze.
     */
    static Material* bronze();
    
    /*!
     Convenience initializer: Generic violet.
     */
    static Material* violet();
        
    /*!
     Convenience initializer: Generic green.
     */
    static Material* green();
    
    /*!
     Convenience initializer: Generic red.
     */
    static Material* red();

    /*!
     Convenience initializer: Generic medium gray.
     */
    static Material* mediumGray();
    
    /*!
     Convenience initializer: Generic light gray.
     */
    static Material* lightGray();
        
    /*!
     Generic diffuse material
     */
    static Material* matte();
    
    /*!
     Convenience initializer: Chrome.
     */
    static Material* chrome();
    
    /*!
     Convenience initializer: Silver.
     */
    static Material* silver();
    
    /******* TRANSMISSIVE MATERIALS *******/
    
    /*!
     Convenience initializer: Glass.
     */
    static Material* glass();
    
    /*!
     Convenience initializer: Glass.
     */
    static Material* glasswater();
    
    /******* MATERIALS WITH TEXTURE ******/

    /*!
     Convenience initializer: Matte with texture.
     
     @param textureName name of the texture to be used.
     */
    static Material* matte(const char* textureName);
    
    /*!
     Convenience initializer: Ruby with surface bump mapper.
     
     @param scale of the bump map.
     */
    static Material* rubyBumpMapped(float scale);
    
    /*!
     Convenience initializer: Marble with color of flames.
     */
    static Material* flameMarble();
    
    /*!
     Convenience initializer: Blue turbulence.
     */
    static Material* blueTurbulence();
};

#endif
