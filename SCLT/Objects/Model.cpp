//
//  Model.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 03/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "Model.hpp"

Model::~Model() {

    //Clean material.
    delete material;
};
