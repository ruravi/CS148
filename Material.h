//
//  Material.h
//  Assignment8
//
//  Created by Rukmani RaviSundaram on 12/2/11.
//  Copyright 2011 stanford. All rights reserved.
//

#ifndef Assignment8_Material_h
#define Assignment8_Material_h
#include "STColor3f.h"

class Material {
public:
    Material(STColor3f amb, STColor3f diff, STColor3f spec, STColor3f mirr, float shine);
    
    STColor3f ambient;
    STColor3f diffuse;
    STColor3f specular;
    STColor3f mirror;
    float shininess;
};


#endif
