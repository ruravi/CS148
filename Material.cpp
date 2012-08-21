//
//  Material.cpp
//  Assignment8
//
//  Created by Rukmani RaviSundaram on 12/2/11.
//  Copyright 2011 stanford. All rights reserved.
//

#include <iostream>
#include "Material.h"
#include "STColor3f.h"

Material::Material ( STColor3f amb, STColor3f diff, STColor3f spec, STColor3f mirr, float shine )
: ambient(amb), diffuse(diff), specular(spec), mirror(mirr), shininess(shine)
{
    
}