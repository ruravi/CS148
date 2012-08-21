//
//  Camera.h
//  Assignment8
//
//  Created by Rukmani RaviSundaram on 12/1/11.
//  Copyright 2011 stanford. All rights reserved.
//

#ifndef Assignment8_Camera_h
#define Assignment8_Camera_h
#include "STPoint3.h"
#include "STVector3.h"

class Camera{
    
public:
    Camera(const STPoint3& eye, const STVector3& up, const STPoint3& lookAt, float fovy, float aspect);
    STPoint3 eye;
    STPoint3 lookAt;
    float fovy;
    float aspect;
    STVector3 u;
    STVector3 v;
    STVector3 w;
};

#endif
