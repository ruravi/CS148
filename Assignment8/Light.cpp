//
//  Light.cpp
//  Assignment8
//
//  Created by Rukmani RaviSundaram on 12/2/11.
//  Copyright 2011 stanford. All rights reserved.
//

#include <iostream>
#include "Light.h"
#include "STVector3.h"
#include "STColor4ub.h"

Light::Light(STColor3f lightsource, STTransform4 currentmatrix) {
    LightSourceIntensity = lightsource;
    this->currentmatrix = currentmatrix;
}

STVector3 Light::ToLight(STPoint3 P)
{
    return lightPos - P;
}

STVector3 Light::ToLight(STPoint3 P, STTransform4 M)
{
    return M.Inverse() * lightPos - P;
}