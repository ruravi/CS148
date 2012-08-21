//
//  Ray.cpp
//  Assignment8
//
//  Created by Rukmani RaviSundaram on 12/1/11.
//  Copyright 2011 stanford. All rights reserved.
//

#include <iostream>
#include "Camera.h"
#include "Ray.h"

Ray::Ray(Camera *mCamera, STPoint3 sample)
{
    start = mCamera->eye;
    direction = STVector3((sample.x - start.x),(sample.y - start.y),(sample.z - start.z));
    direction = Normalize(direction);
    min_t = 1;
    max_t = 100;
}

Ray::Ray(STPoint3 P, STPoint3 L, float min, float max, bool isDirectional, bool normalize)
{
    start = P;
    if (isDirectional) {
        direction = STVector3(L);
    } else {
        direction = L - P;
    }
    if ( normalize ) {
        direction = Normalize(direction);
    }
    min_t = min;
    max_t = max;
}

Ray::Ray(STPoint3 P, STPoint3 L, float min, float max, bool isDirectional)
{
    start = P;
    if (isDirectional) {
        direction = STVector3(L);
    } else {
        direction = L - P;
    }
  
    direction = Normalize(direction);
    
    min_t = min;
    max_t = max;
}