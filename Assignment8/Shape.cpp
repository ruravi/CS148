//
//  Shape.cpp
//  Assignment8
//
//  Created by Rukmani RaviSundaram on 12/1/11.
//  Copyright 2011 stanford. All rights reserved.
//

#include <iostream>
#include "Shape.h"

Intersection *Shape::FindIntersection(Ray *mRay) {
    Intersection *i;
    i->isValid = false;
    return i;
}

STPoint3 Shape::InverseTransformRay(STPoint3 point) {
    return M.Inverse() * point;
}

STVector3 Shape::InverseTransformRay(STVector3 vector) {
    return M.Inverse() * vector;
}

STPoint3 Shape::TransformPoint(STPoint3 point) 
{
    return M * point;
}
STVector3 Shape::InverseTransformNormal(STVector3 vector)
{
    return (M.Inverse()).Transpose() * vector;
}