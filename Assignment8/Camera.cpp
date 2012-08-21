//
//  Camera.cpp
//  Assignment8
//
//  Created by Rukmani RaviSundaram on 12/1/11.
//  Copyright 2011 stanford. All rights reserved.
//

#include <iostream>
#include "Camera.h"
#include "STVector3.h"

Camera::Camera(const STPoint3& eye, const STVector3& up, const STPoint3& lookAt, float fovy, float aspect) {
    this->eye = eye;
    this->fovy = fovy;
    this->aspect = aspect;
    this->lookAt = lookAt;
    STVector3 a = lookAt - eye;
    STVector3 b = up;
    w = Normalize(a);
    u = Normalize(STVector3::Cross(b, w));
    v = STVector3::Cross(w, u);
}