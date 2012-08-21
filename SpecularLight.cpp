//
//  SpecularLight.cpp
//  Assignment8
//
//  Created by Rukmani RaviSundaram on 12/2/11.
//  Copyright 2011 stanford. All rights reserved.
//

#include <iostream>
#include "SpecularLight.h"
#include "STColor3f.h"

SpecularLight::SpecularLight(STPoint3 locn, STColor3f col) : Light(col)
{
    lightPos = locn;
}

STColor3f SpecularLight::calculateIntensity(STPoint3 P, STVector3 N, STPoint3 eye, float shininess)
{
    STVector3 l = Normalize(ToLight(P));
    STVector3 e = Normalize(eye - P);
    STVector3 Rm = Normalize(2. * STVector3::Dot(l, Normalize(N)) * Normalize(N) - l);
    float base = STVector3::Dot(Rm, e) > 0. ? STVector3::Dot(Rm, e) : 0;
    return LightSourceIntensity * pow(base,shininess);    
}