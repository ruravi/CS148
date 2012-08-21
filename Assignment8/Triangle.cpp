//
//  Triangle.cpp
//  Assignment8
//
//  Created by Rukmani RaviSundaram on 12/1/11.
//  Copyright 2011 stanford. All rights reserved.
//

#include <iostream>
#include "Triangle.h"

Triangle::Triangle(STPoint3 a, STPoint3 b, STPoint3 c, STTransform4 M) {
    this->A = a;
    this->B = b;
    this->C = c;
    this->M = M;
    IsTriangle = true;
}

Intersection* Triangle::FindIntersection(Ray *mRay) {
    
    Intersection *inter = new Intersection;
    STPoint3 eye = InverseTransformRay(mRay->start);
    STPoint3 dist = STPoint3(InverseTransformRay(mRay->direction));
    float a = A.x - B.x;
    float b = A.y - B.y;
    float c = A.z - B.z;
    float d = A.x - C.x;
    float e = A.y - C.y;
    float f = A.z - C.z;
    float g = dist.x;
    float h = dist.y;
    float i = dist.z;
    float j = A.x - eye.x;
    float k = A.y - eye.y;
    float l = A.z - eye.z;
    
    float M = a*(e*i - h*f) + b*(g*f - d*i) + c*(d*h - e*g);
    float t = -( f*(a*k - j*b) + e*(j*c - a*l) + d*(b*l - k*c)) / M;
    if (t < 0 || t < mRay->min_t || t > mRay->max_t) {
        inter->isValid = false;
        return inter;
    }
    float gamma = (i*(a*k - j*b) + h*(j*c - a*l) + g*(b*l - k*c)) / M;
    if (gamma < 0 || gamma > 1) {
        inter->isValid = false;
        return inter;
    }
    float beta = (j*(e*i - h*f) + k*(g*f - d*i) + l*(d*h - e*g)) / M;
    if (beta < 0 || beta > 1-gamma) {
        inter->isValid = false;
        return inter;
    }
    inter->isValid = true;
    inter->t = t;
    inter->P = eye + t*STVector3(dist);
    inter->normal = Normalize(STVector3::Cross(C-A, B-A));
    
    // Transformation
    inter->P = TransformPoint(inter->P);
    inter->normal = Normalize(InverseTransformNormal(inter->normal));
    
    return inter;
}