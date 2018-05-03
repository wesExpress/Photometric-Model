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

class Galaxy
{
public:
    void setGalaxy();
    void writeParams();
    void setDisk(float zeropoint, float exptime, float pix);
    void setBar(float zeropoint, float exptime, float pix);
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
    
    float surf_disk_try;
    float surf_bar_try;
    float disk_scale_try;
    float bar_scale_try;
    float bar_len_try;
    float inc_try;
    float bar_ellip_try;
    
    // functions
    float doRadCon(float angle);
};

#endif /* defined(__Photometric_Model__Galaxy__) */
