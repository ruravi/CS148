//
//  DirectionalLight.h
//  Assignment8
//
//  Created by Rukmani RaviSundaram on 12/2/11.
//  Copyright 2011 stanford. All rights reserved.
//

#ifndef Assignment8_DirectionalLight_h
#define Assignment8_DirectionalLight_h
#include "Light.h"
#include "Shape.h"

class DirectionalLight : public Light {
public:
    DirectionalLight(STPoint3, STColor3f, STTransform4);
    STColor3f calculateIntensity(STPoint3, STVector3, Shape*);
    STVector3 ToLight(void);
    STColor3f calculateSpecularLightIntensity(STPoint3, STVector3, STPoint3, float, Shape*);
    
private:
    
};


#endif
