//
//  ImagePlane.h
//  Assignment8
//
//  Created by Rukmani RaviSundaram on 12/1/11.
//  Copyright 2011 stanford. All rights reserved.
//

#ifndef Assignment8_ImagePlane_h
#define Assignment8_ImagePlane_h
#include "STImage.h"
#include "Camera.h"

class ImagePlane {
public:
    ImagePlane(int imgWidth, int imgHeight, const std::string& outputFilename, int fovy, int aspect, Camera *mCamera);
    void calculateViewPlane(int fovy, int aspect, Camera *mCamera);
    STPoint3 Sample(float, float);
    void writePixel(int, int, STColor4ub);
    void DrawImage(void);
    
    STPoint3 LL;
    STPoint3 LR;
    STPoint3 UL;
    STPoint3 UR;

private:
    STImage *output;
    std::string outputFilename;
    
    
    int imgWidth;
    int imgHeight;
                    
};


#endif
