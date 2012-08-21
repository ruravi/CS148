//
//  PointLight.h
//  Assignment8
//
//  Created by Rukmani RaviSundaram on 12/2/11.
//  Copyright 2011 stanford. All rights reserved.
//

#ifndef Assignment8_PointLight_h
#define Assignment8_PointLight_h
#include "Light.h"
#include "Shape.h"

class PointLight : public Light {
public:
    PointLight(STPoint3, STColor3f, STTransform4);
    STColor3f calculateIntensity(STPoint3, STVector3, Shape*);
    STColor3f calculateSpecularLightIntensity(STPoint3, STVector3, STPoint3, float, Shape*);
    
private:
};

#endif
