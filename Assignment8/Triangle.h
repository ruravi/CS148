//
//  Triangle.h
//  Assignment8
//
//  Created by Rukmani RaviSundaram on 12/1/11.
//  Copyright 2011 stanford. All rights reserved.
//

#ifndef Assignment8_Triangle_h
#define Assignment8_Triangle_h
#include "STPoint3.h"
#include "Shape.h"

class Triangle : public Shape {
public:
    Triangle(STPoint3, STPoint3, STPoint3, STTransform4);
    virtual Intersection* FindIntersection(Ray *);
    
private:
    STPoint3 A;
    STPoint3 B;
    STPoint3 C;
};

#endif
