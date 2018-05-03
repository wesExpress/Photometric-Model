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
    distance_dist(70.0f,120.0f),        // in Mpc
    inc_dist(20.0f,65.0f),              // in degrees
    distance(distance_dist(rng)),

    // disk distributions and values
    surf_disk_dist(22.5f,24.0f),        // in mag/arcsec^2
    scale_dist(3.0f,7.0f),              // in kpc
    pa_dist(-90.0f,90.0f),              // in degrees

    // bar distributions and values
    surf_bar_dist(22.0f,23.0f),         // in mag/arcsec^2
    bar_ellip_dist(0.5f,0.7f),
    bar_len_dist(2.0f,6.5f),            // in kpc
    bar_shape_dist(1.8f,2.2f),
    bar_scale_dist(3.0f,7.0f)           // in kpc
{
    // makes sure the disk is fainter than bar
    while (true)
    {
        surf_disk_try = surf_disk_dist(rng);
        surf_bar_try = surf_bar_dist(rng);
        const float cond = surf_disk_try - surf_bar_try;
        
        if(cond > 0.0f && cond < 1.0f)
        {
            break;
        }
    }
    // makes sure the bar is shorter than the scale length of the disk
    while (true)
    {
        scale_try = scale_dist(rng);
        len_try = bar_len_dist(rng);
        bar_scale_try = bar_scale_dist(rng);
        if(len_try < scale_try && bar_scale_try < scale_try)
        {
            break;
        }
    }
    // makes sure the bar is more eccentric than the disk
    while (true)
    {
        inc_try = inc_dist(rng);
        float disk_e = 1.0f - acos(doRadCon(inc_try));
        ellip_try = bar_ellip_dist(rng);
        if(ellip_try > disk_e)
        {
            inclination = inc_try;
            break;
        }
    }
    // initialize objects
    disk.makeDisk(surf_disk_try,scale_try,pa_dist(rng),ccd);
    bar.makeBar(surf_bar_try,pa_dist(rng),ellip_try,len_try,bar_shape_dist(rng),bar_scale_try,ccd);
    
    std::cout << "Distance (Mpc) = " << distance << std::endl;
    std::cout << "Inclination = " << inclination << std::endl;
    std::cout << std::endl;
    std::cout << "Disk surf bright = " << surf_disk_try << std::endl;
    std::cout << "Disk cen_int = " << disk.GetCenInt() << std::endl;
    std::cout << "Disk scale (arcsec) = " << disk.GetScale() << std::endl;
    std::cout << "Disk pa = " << disk.GetPa() << std::endl;
    std::cout << std::endl;
    std::cout << "Bar surf bright = " << surf_bar_try << std::endl;
    std::cout << "Bar cen_int = " << bar.GetCenInt() << std::endl;
    std::cout << "Bar ellip = " << bar.GetEllip() << std::endl;
    std::cout << "Bar len (kpc) = " << bar.GetLen() << std::endl;
    std::cout << "Bar pa = " << bar.GetPa() << std::endl;
    std::cout << "Bar scale (kpc) = " << bar.GetScale() << std::endl;
}

void Galaxy::genCoordsNew(int x_in, int y_in, const CCD& ccd)
{
    const int xcen = ccd.GetX()/2;
    const int ycen = ccd.GetY()/2;
    
    const float inc_rad = doRadCon(inclination);
    const float pa_disk_rad = doRadCon(disk.GetPa());
    const float pa_bar_rad = doRadCon(bar.GetPa() + 90.0f);
    
    float shape = bar.GetShape();
    float ellip = bar.GetEllip();
    
    // cartesian coordinates in galaxy frame from given pixel values
    x = (float(x_in-xcen)*cos(pa_disk_rad) + float(y_in-ycen)*sin(pa_disk_rad))/cos(inc_rad);
    y = float(y_in-ycen)*cos(pa_disk_rad) - float(x_in-xcen)*sin(pa_disk_rad);

    // bar coordinate
    const float x_bar = (float(x_in-xcen)*cos(pa_bar_rad) + float(y_in-ycen)*sin(pa_bar_rad))/cos(inc_rad);
    const float y_bar = float(y_in-ycen)*cos(pa_bar_rad) - float(x_in-xcen)*sin(pa_bar_rad);
    bar_coord = pow(pow(abs(x_bar),shape) + pow(abs(y_bar/(1.0f - ellip)),shape),1.0f/shape);
}

float Galaxy::diskInten(float factor)
{
    return disk.inten(x, y, factor);
}

float Galaxy::barInten(float factor)
{
    return bar.intenFreeman(bar_coord, factor);
    //return bar.intenFlat(bar_coord, factor);
}

float Galaxy::getDistance()
{
    return distance;
}

float Galaxy::doRadCon(float angle)
{
    return angle*PI/180.0f;
}