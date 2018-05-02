//
//  Galaxy.cpp
//  Photometric Model
//
//  Created by Wesley Peters on 5/1/18.
//  Copyright (c) 2018 Wesley Peters. All rights reserved.
//

#include <iostream>

#include "Galaxy.h"
#include "stdlib.h"
#include "math.h"

#define PI 3.1415926535

Galaxy::Galaxy(const CCD& ccd)
    :
    // set up random
    rng(rd()),

    // parameters for galaxy as a whole
    distance_dist(70.0f,120.0f),
    inc_dist(20.0f,65.0f),
    distance(distance_dist(rng)),
    inclination(inc_dist(rng)),

    // disk distributions and values
    surf_disk_dist(22.0f,24.0f),
    scale_dist(3.0f,7.0f),
    pa_dist(-90.0f,90.0f),

    // bar distributions and values
    surf_bar_dist(21.0f,22.0f),
    bar_ellip_dist(0.5f,0.7f),
    bar_len_dist(5.0f,6.0f),
    bar_shape_dist(1.8f,2.2f),

    // initialize objects
    disk(surf_disk_dist(rng),scale_dist(rng),pa_dist(rng),ccd),
    bar(surf_bar_dist(rng),pa_dist(rng),bar_ellip_dist(rng),bar_len_dist(rng),bar_shape_dist(rng),ccd)
{
    std::cout << "Distance (Mpc) = " << distance << std::endl;
    std::cout << "Inclination = " << inclination << std::endl;
    std::cout << std::endl;
    std::cout << "Disk cen_int = " << disk.GetCenInt() << std::endl;
    std::cout << "Disk scale (arcsec) = " << disk.GetScale() << std::endl;
    std::cout << "Disk pa = " << disk.GetPa() << std::endl;
    std::cout << std::endl;
    std::cout << "Bar cen_int = " << bar.GetCenInt() << std::endl;
    std::cout << "Bar ellip = " << bar.GetEllip() << std::endl;
    std::cout << "Bar len (kpc) = " << bar.GetLen() << std::endl;
    std::cout << "Bar pa = " << bar.GetPa() << std::endl;
}

void Galaxy::genCoordsNew(int x_in, int y_in, const CCD& ccd)
{
    const int xcen = ccd.GetX()/2;
    const int ycen = ccd.GetY()/2;
    
    const float inc_rad = doRadCon(inclination);
    const float pa_rad = doRadCon(disk.GetPa());
    
    float shape = bar.GetShape();
    float ellip = bar.GetEllip();
    
    // cartesian coordinates in galaxy frame from given pixel values
    x = (float(x_in-xcen)*cos(pa_rad) + float(y_in-ycen)*sin(pa_rad))/cos(inc_rad);
    y = float(y_in-ycen)*cos(pa_rad) - float(x_in-xcen)*sin(pa_rad);

    // bar coordinate
    bar_coord = pow(pow(abs(x),shape) + pow(abs(y/(1.0f - ellip)),shape),1.0f/shape);
}

float Galaxy::diskInten(float factor)
{
    return disk.inten(x, y, factor);
}

float Galaxy::barInten(float factor)
{
    return bar.inten(bar_coord, factor);
}

float Galaxy::getDistance()
{
    return distance;
}

float Galaxy::doRadCon(float angle)
{
    return angle*PI/180.0f;
}