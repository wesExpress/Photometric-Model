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
#include <random>

#include "Disk.h"
#include "Bar.h"
#include "CCD.h"

class Galaxy
{
public:
    Galaxy();
    void genCoords(int i, int j, int coord_len, const CCD& ccd);
    float rotCoordX_disk(float x, float y, int xcen);
    float rotCoordY_disk(float x, float y, int ycen);
    float rotCoordX_bar(float x, float y, int xcen);
    float rotCoordY_bar(float x, float y, int ycen);
    float inten(float x_in, float y_in, float r_in);
    float GetX() const;
    float GetY() const;
    float GetR() const;
    float GetDistance() const;
    float GetInclination() const;
private:
    // random values for initializations
    std::random_device rd;
    std::mt19937 rng;
    
    // parameters of the galaxy
    float x;
    float y;
    float r;
    float distance;
    float inclination;
    // distributions for parameters
    std::uniform_real_distribution<float> distance_dist;
    std::uniform_real_distribution<float> inc_dist;
    
    // components of the galaxy
    Disk disk;
    Bar bar;
    
    // distributions for the disk parameters
    std::uniform_real_distribution<float> cen_int_disk_dist;
    std::uniform_real_distribution<float> scale_dist;
    std::uniform_real_distribution<float> pa_dist;
    std::uniform_real_distribution<float> rmax_dist;
    // distributions for the bar parameters
    std::uniform_real_distribution<float> cen_int_bar_dist;
    std::uniform_real_distribution<float> bar_ellip_dist;
    std::uniform_real_distribution<float> bar_len_dist;
    std::uniform_real_distribution<float> bar_shape_dist;
};

#endif /* defined(__Photometric_Model__Galaxy__) */
