//
//  SpecularLight.h
//  Assignment8
//
//  Created by Rukmani RaviSundaram on 12/2/11.
//  Copyright 2011 stanford. All rights reserved.
//

#ifndef Assignment8_SpecularLight_h
#define Assignment8_SpecularLight_h
#include "Light.h"

class SpecularLight : public Light {
public:
    SpecularLight(STPoint3 locn, STColor3f col);
    STColor3f calculateIntensity(STPoint3, STVector3, STPoint3, float);
    
private:
    
};

#endif
