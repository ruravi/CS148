//
//  Sphere.h
//  Assignment8
//
//  Created by Rukmani RaviSundaram on 12/1/11.
//  Copyright 2011 stanford. All rights reserved.
//

#ifndef Assignment8_Sphere_h
#define Assignment8_Sphere_h
#include "Shape.h"


class Sphere : public Shape {
public:
    Sphere(float, STPoint3, STTransform4);
    virtual Intersection* FindIntersection(Ray *);
    
private:
    float radius;
    STPoint3 Center;
};


#endif
