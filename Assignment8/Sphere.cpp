//
//  Sphere.cpp
//  Assignment8
//
//  Created by Rukmani RaviSundaram on 12/1/11.
//  Copyright 2011 stanford. All rights reserved.
//

#include <iostream>
#include "Sphere.h"

Sphere::Sphere(float radius, STPoint3 center, STTransform4 M)
{
    this->radius = radius;
    this->Center = center;
    this->M = M;
    IsTriangle = false;
}

Intersection *Sphere::FindIntersection(Ray *mRay) 
{
    Intersection *intersectionPt = new Intersection;
    STPoint3 e = InverseTransformRay(mRay->start);
    STVector3 d = InverseTransformRay(mRay->direction);
    STPoint3 c = Center;
    float Rsquared = radius * radius;
    
    float discriminant = pow(STVector3::Dot(d, e - c),2) - STVector3::Dot(d, d) * (STVector3::Dot(e-c, e-c) - Rsquared);
    
    if (discriminant < 0) {
        intersectionPt->isValid = false;
        return intersectionPt;
    }
    
    float t1 = (-STVector3::Dot(d, e -c) + sqrt(discriminant)) / STVector3::Dot(d, d);
    float t2 = (-STVector3::Dot(d, e -c) - sqrt(discriminant)) / STVector3::Dot(d, d);
    t1 = (t1 < 0 ?  ((t2 > 0) ? t2 : t1) : t1);
    t2 = (t2 < 0 ? (( t1 > 0) ? t1 : t2) : t2);
    float t = (t1 < t2) ? t1 : t2;
    
    if ( t < mRay->min_t || t > mRay->max_t) {
        intersectionPt->isValid = false;
        return intersectionPt;
    }
    
    intersectionPt->isValid = true;
    intersectionPt->t = t;
    intersectionPt->P = e + t * d;
    intersectionPt->normal = Normalize((intersectionPt->P - c));
    
    intersectionPt->P = TransformPoint(intersectionPt->P);
    intersectionPt->normal = Normalize(InverseTransformNormal(intersectionPt->normal));
    return intersectionPt;
}

