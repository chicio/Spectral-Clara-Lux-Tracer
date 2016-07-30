//
//  TracerModelFactory.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 29/12/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef TracerModelFactory_hpp
#define TracerModelFactory_hpp

class TracerModelFactory {
public:
    
    /*!
     Create the tracer model based on the scene parameter.
     
     @param tracerModelType the type of tracer to be created.
     
     @returns a tracer model.
     */
    Tracer* createTracer(TracerModelType tracerModelType, Scene* scene);
};

#endif /* TracerModelFactory_hpp */
