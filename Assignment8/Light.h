//
//  Light.h
//  Assignment8
//
//  Created by Rukmani RaviSundaram on 12/2/11.
//  Copyright 2011 stanford. All rights reserved.
//

#ifndef Assignment8_Light_h
#define Assignment8_Light_h
#include "STColor3f.h"
#include "STPoint3.h"
#include "STVector3.h"
#include "STColor4ub.h"
#include "STTransform4.h"


class Light {
public:
    Light(STColor3f, STTransform4);
    float calculateIntensity(STPoint3, STVector3);
    STPoint3  lightPos;
    STTransform4 currentmatrix;
    
protected:
    
    STColor3f LightSourceIntensity;
    STVector3 ToLight(STPoint3 P);
    STVector3 ToLight(STPoint3, STTransform4);
    
private:
    
};

#endif
