//
//  Ray.h
//  Assignment8
//
//  Created by Rukmani RaviSundaram on 12/1/11.
//  Copyright 2011 stanford. All rights reserved.
//

#ifndef Assignment8_Ray_h
#define Assignment8_Ray_h
#include "Camera.h"

class Ray {
public:
    
    Ray(Camera *mCamera, STPoint3 sample);
    Ray(STPoint3, STPoint3, float, float, bool);
    Ray(STPoint3, STPoint3, float, float, bool, bool);
    
    STPoint3 start;
    STVector3 direction;
    float min_t;
    float max_t;
};


#endif
