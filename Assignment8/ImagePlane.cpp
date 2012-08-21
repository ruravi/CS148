//
//  ImagePlane.cpp
//  Assignment8
//
//  Created by Rukmani RaviSundaram on 12/1/11.
//  Copyright 2011 stanford. All rights reserved.
//

#include <iostream>
#include "ImagePlane.h"
#include "STImage.h"
#include "STPoint3.h"
#define PI 3.14159265

ImagePlane::ImagePlane(int imgWidth, int imgHeight, const std::string& outputFilename, int fovy, int aspect, Camera *mCamera) {
    
    output = new STImage(imgWidth, imgHeight, STImage::Pixel(0,0,0,0));
    this->outputFilename = outputFilename;
    calculateViewPlane(fovy,aspect,mCamera);
    this->imgWidth = imgWidth;
    this->imgHeight = imgHeight;
}

void ImagePlane::calculateViewPlane(int fovy, int aspect, Camera *mCamera )
{
    STPoint3 C = mCamera->eye + mCamera->w;
    float fovyinrad = fovy *  PI/180.;
    float Y = tan(fovyinrad/2.);
    float X = tan(aspect * fovyinrad/2.);
        
    LL = C + X * mCamera->u - Y * mCamera->v;
    UL = C + X * mCamera->u + Y * mCamera->v;
    LR = C - X * mCamera->u - Y * mCamera->v;
    UR = C - X * mCamera->u + Y * mCamera->v;
}

void ImagePlane::writePixel(int x , int y, STColor4ub value)
{
    if ( x > 0 && x < imgWidth && y > 0 && y < imgHeight) {
        output->SetPixel(x, y, value);
    }
}

void ImagePlane::DrawImage()
{
    output->Draw();
    output->Save(outputFilename);
}