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
    Galaxy(const CCD& ccd);
    void genCoordsNew(int x_in, int y_in, const CCD& ccd);
    float diskInten(float factor);
    float barInten(float factor);
    float getDistance();
private:
    // random initializations
    std::random_device rd;
    std::mt19937 rng;
    
    // distributions for parameters
    std::uniform_real_distribution<float> distance_dist;
    std::uniform_real_distribution<float> inc_dist;
    
    // distributions for the disk parameters
    std::uniform_real_distribution<float> surf_disk_dist;
    std::uniform_real_distribution<float> scale_dist;
    std::uniform_real_distribution<float> pa_dist;
    // distributions for the bar parameters
    std::uniform_real_distribution<float> surf_bar_dist;
    std::uniform_real_distribution<float> bar_ellip_dist;
    std::uniform_real_distribution<float> bar_len_dist;
    std::uniform_real_distribution<float> bar_shape_dist;
    
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
    float scale_try;
    float len_try;
    float inc_try;
    float ellip_try;
    
    // functions
    float doRadCon(float angle);
};

#endif /* defined(__Photometric_Model__Galaxy__) */
