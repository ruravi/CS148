//
//  Shape.h
//  Assignment8
//
//  Created by Rukmani RaviSundaram on 12/1/11.
//  Copyright 2011 stanford. All rights reserved.
//

#ifndef Assignment8_Shape_h
#define Assignment8_Shape_h
#include "STPoint3.h"
#include "STVector3.h"
#include "Ray.h"
#include "STTransform4.h"

struct Intersection {
    float t;
    STPoint3 P;
    STVector3 normal;
    bool isValid;
    bool IsTransformed;
};

class Shape {
    
public:
    virtual Intersection* FindIntersection(Ray *);
    STPoint3 InverseTransformRay( STPoint3);
    STVector3 InverseTransformRay(STVector3);
    STPoint3 TransformPoint(STPoint3);
    STVector3 InverseTransformNormal(STVector3 vector);
    

    STTransform4 M; //Transformation Matrix for this object
    bool IsTriangle;
    
    
};


#endif
