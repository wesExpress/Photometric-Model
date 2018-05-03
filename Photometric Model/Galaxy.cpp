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

void Galaxy::setGalaxy()
{
    distance = randGen.genDistance();
    
    // makes sure the disk is fainter than bar
    while (true)
    {
        surf_disk_try = randGen.genSurfDisk();
        surf_bar_try = randGen.genSurfBar();
        const float cond = surf_disk_try - surf_bar_try;
        
        if(cond > 0.0f && cond < 1.0f)
        {
            break;
        }
    }
    // makes sure the bar is shorter than the scale length of the disk
    while (true)
    {
        disk_scale_try = randGen.genDiskScale();
        bar_len_try = randGen.genBarLen();
        bar_scale_try = randGen.genBarScale();
        
        if(bar_len_try < disk_scale_try && bar_scale_try < disk_scale_try)
        {
            break;
        }
    }
    // makes sure the bar is more eccentric than the disk
    while (true)
    {
        inc_try = randGen.genInclination();
        float disk_e = 1.0f - acos(doRadCon(inc_try));
        bar_ellip_try = randGen.genBarEccen();
        
        if(bar_ellip_try > disk_e)
        {
            inclination = inc_try;
            break;
        }
    }
}

void Galaxy::writeParams()
{
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

void Galaxy::setDisk(float zeropoint, float exptime, float pix)
{
    disk.makeDisk(surf_disk_try,disk_scale_try,randGen.genDiskPA(),zeropoint,exptime,pix);
}

void Galaxy::setBar(float zeropoint, float exptime, float pix)
{
    bar.makeBar(surf_bar_try,randGen.genBarPa(),bar_ellip_try,bar_len_try,randGen.genBarShape(),bar_scale_try,zeropoint,exptime,pix);
}

void Galaxy::genCoordsNew(int x_in, int y_in, int xcen, int ycen)
{
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

float Galaxy::getDistance() const
{
    return distance;
}

float Galaxy::getInclination() const
{
    return inclination;
}

float Galaxy::doRadCon(float angle)
{
    return angle*PI/180.0f;
}