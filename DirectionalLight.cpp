//
//  DirectionalLight.cpp
//  Assignment8
//
//  Created by Rukmani RaviSundaram on 12/2/11.
//  Copyright 2011 stanford. All rights reserved.
//

#include <iostream>
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(STPoint3 D, STColor3f col, STTransform4 matrix) : Light(col, matrix) {
    lightPos = STPoint3(-D.x, -D.y, -D.z);
}

STColor3f DirectionalLight::calculateIntensity(STPoint3 P, STVector3 N, Shape *curr_shape)
{
    STVector3 l =  Normalize(ToLight());
    float costheta = STVector3::Dot(Normalize(N), l);
    if (curr_shape->IsTriangle) {
        costheta = costheta < 0 ? -costheta : costheta;
    } else {
        costheta = costheta < 0 ? 0 : costheta;
    }
    return STColor3f(LightSourceIntensity.r * costheta,LightSourceIntensity.g * costheta,LightSourceIntensity.b * costheta);

}

STVector3 DirectionalLight::ToLight(void)
{
    return STVector3(lightPos);
}

STColor3f DirectionalLight::calculateSpecularLightIntensity(STPoint3 P ,STVector3 N, STPoint3 eye, float shininess, Shape *curr_shape) {
    STVector3 l =  Normalize(ToLight());
    STVector3 e = Normalize(eye - P);
    STVector3 Rm = Normalize(2. * STVector3::Dot(l, Normalize(N)) * Normalize(N) - l);
    float base = STVector3::Dot(Rm, e) > 0. ? STVector3::Dot(Rm, e) : 0;
    if (curr_shape->IsTriangle) {
        base = STVector3::Dot(Rm, e) < 0. ? -STVector3::Dot(Rm, e) : STVector3::Dot(Rm, e);
    }
    return LightSourceIntensity * pow(base,shininess);  
}