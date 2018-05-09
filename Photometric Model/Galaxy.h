//
//  Galaxy.h
//  Photometric Model
//
//  Created by Wesley Peters on 5/1/18.
//  Copyright (c) 2018 Wesley Peters. All rights reserved.
//

#ifndef __Photometric_Model__Galaxy__
#define __Photometric_Model__Galaxy__

#include <stdio.h>

#include "RandomGen.h"
#include "Disk.h"
#include "Bar.h"
#include "UserInput.h"

class Galaxy
{
public:
    void setGalaxy(UserInput& io, std::string filename);
    void writeParamsTerminal();
    void writeParamsFile(std::string output_in, float factor);
    void setDisk(float zeropoint, float exptime, float pix, UserInput& io);
    void setBar(float zeropoint, float exptime, float pix, UserInput& io);
    void genCoordsNew(int x_in, int y_in, int xcen, int ycen);
    float diskInten(float factor);
    float barInten(float factor);
    float getDistance() const;
    float getInclination() const;
private:
    RandomGen randGen;
    
    // parameters of the galaxy
    float x;
    float y;
    float bar_coord;
    float distance;
    float inclination;
    
    // components of the galaxy
    Disk disk;
    Bar bar;
    
    float surfDiskTry;
    float surfBarTry;
    float diskScaleTry;
    float barScaleTry;
    float barLenTry;
    float incTry;
    float barEllipTry;
    
    std::string barInputString = "bar_profile";
    float barNo = 0.0f;
    float barFerrer = 1.0f;
    float barFlat = 2.0f;
    float barFreeman = 3.0f;
    float barInput;
    float badInput = -10.0f;
    
    // functions
    float doRadCon(float angle);
};

#endif /* defined(__Photometric_Model__Galaxy__) */
