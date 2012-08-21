//
//  AmbientLight.cpp
//  Assignment8
//
//  Created by Rukmani RaviSundaram on 12/2/11.
//  Copyright 2011 stanford. All rights reserved.
//

#include <iostream>
#include "AmbientLight.h"
#include "STPoint3.h"
#include "STVector3.h"
#include "STColor3f.h"


AmbientLight::AmbientLight(STColor3f color, STTransform4 matrix) :Light(color, matrix)
{
    
}

STColor3f AmbientLight::calculateIntensity(STPoint3 P , STVector3 N) 
{
    return LightSourceIntensity;
}