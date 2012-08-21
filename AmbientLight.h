//
//  AmbientLight.h
//  Assignment8
//
//  Created by Rukmani RaviSundaram on 12/2/11.
//  Copyright 2011 stanford. All rights reserved.
//

#ifndef Assignment8_AmbientLight_h
#define Assignment8_AmbientLight_h
#include "Light.h"
#include "STColor4ub.h"

class AmbientLight : public Light {
public:
    AmbientLight(STColor3f, STTransform4);
    STColor3f calculateIntensity(STPoint3, STVector3);
    
private:
    

};


#endif
