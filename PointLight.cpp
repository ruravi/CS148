//
//  PointLight.cpp
//  Assignment8
//
//  Created by Rukmani RaviSundaram on 12/2/11.
//  Copyright 2011 stanford. All rights reserved.
//

#include <iostream>
#include "PointLight.h"
#include "STColor3f.h"
#include "STVector3.h"


PointLight::PointLight(STPoint3 locn, STColor3f col, STTransform4 matrix) : Light(col, matrix) 
{
    lightPos = locn;
}

STColor3f PointLight::calculateIntensity(STPoint3 P, STVector3 N,Shape *currentShape)
{
    STVector3 l = Light::ToLight(P);
    float costheta = STVector3::Dot(N, Normalize(l)) ;
    
    
    if (currentShape->IsTriangle) {
        costheta = costheta < 0 ? -costheta : costheta ;
    } else {
        costheta = costheta < 0 ? 0 : costheta;
    }
    return STColor3f(LightSourceIntensity.r * costheta,LightSourceIntensity.g * costheta,LightSourceIntensity.b * costheta);
}



STColor3f PointLight::calculateSpecularLightIntensity(STPoint3 P, STVector3 N, STPoint3 eye, float shininess, Shape* currentShape) 
{
        
    STVector3 l = Normalize(ToLight(P));
    STVector3 e = Normalize(eye - P);
    STVector3 Rm = Normalize(2. * STVector3::Dot(l, N) * N - l);
    
    float base = STVector3::Dot(Rm, e) > 0. ? STVector3::Dot(Rm, e) : 0;
    
    if (currentShape->IsTriangle) {
        base = STVector3::Dot(Rm, e) < 0 ? -STVector3::Dot(Rm, e) : STVector3::Dot(Rm, e);
    }
    return LightSourceIntensity * pow(base,shininess);    
}