//
//  Galaxy.cpp
//  Photometric Model
//
//  Created by Wesley Peters on 5/1/18.
//  Copyright (c) 2018 Wesley Peters. All rights reserved.
//

#include "Galaxy.h"
#include "stdlib.h"
#include "math.h"

#define PI 3.1415926535

Galaxy::Galaxy()
    :
    // set up random
    rng(rd()),

    // parameters for galaxy as a whole
    distance_dist(60.0f,100.0f),
    inc_dist(20.0f,80.0f),
    distance(distance_dist(rng)),
    inclination(inc_dist(rng)),

    // disk distributions and values
    cen_int_disk_dist(50.0f,100.0f),
    scale_dist(3.0f,7.0f),
    pa_dist(-90.0f,90.0f),
    rmax_dist(25.0f,35.0f),
    disk(cen_int_disk_dist(rng),scale_dist(rng),pa_dist(rng),rmax_dist(rng)),

    // bar distributions and values
    cen_int_bar_dist(75.0f,300.0f),
    bar_ellip_dist(0.2f,0.7f),
    bar_len_dist(2.0f,5.0f),
    bar_shape_dist(1.8f,2.2f),
    bar(cen_int_bar_dist(rng),pa_dist(rng),bar_ellip_dist(rng),bar_len_dist(rng),bar_shape_dist(rng))
{
}

void Galaxy::genCoords(int i, int j, int coord_len, const CCD& ccd)
{
    float rmax = disk.GetRmax();
    float shape = bar.GetShape();
    float ellip = bar.GetEllip();
    
    x = -rmax + 2.0f*rmax/coord_len*(float(j) - 1.0f);
    y = -rmax + 2.0f*rmax/coord_len*(float(i) - 1.0f);
    
    // normal cartesian coordinates
    x = x/distance*206265.0f/ccd.GetPix();
    y = y/distance*206265.0f/ccd.GetPix();
    // bar coordinates
    bar_coord = pow(pow(abs(x),shape) + pow(abs(y)/(1.0f - ellip),shape),1.0f/shape);
}

float Galaxy::rotCoordX_disk(float x, float y, int xcen)
{
    const float inc_rad = inclination*PI/180.0f;
    const float pa_rad = disk.GetPa()*PI/180.0f;
    
    return x*cos(inc_rad)*cos(pa_rad) + float(xcen) - y*sin(pa_rad);
}
float Galaxy::rotCoordY_disk(float x, float y, int ycen)
{
    const float inc_rad = inclination*PI/180.0f;
    const float pa_rad = disk.GetPa()*PI/180.0f;
    
    return x*cos(inc_rad)*sin(pa_rad) + y*cos(pa_rad) + float(ycen);
}

float Galaxy::rotCoordX_bar(float x, float y, int xcen)
{
    const float inc_rad = inclination*PI/180.0f;
    const float pa_rad = bar.GetPa()*PI/180.0f;
    
    return x*cos(inc_rad)*cos(pa_rad) + float(xcen) - y*sin(pa_rad);
}

float Galaxy::rotCoordY_bar(float x, float y, int ycen)
{
    const float inc_rad = inclination*PI/180.0f;
    const float pa_rad = bar.GetPa()*PI/180.0f;
    
    return x*cos(inc_rad)*sin(pa_rad) + y*cos(pa_rad) + float(ycen);
}

float Galaxy::inten(float x_in, float y_in, float r_in, float pix_factor)
{
    return disk.inten(x_in, y_in, pix_factor) + bar.inten(r_in, pix_factor);
}

float Galaxy::GetX() const
{
    return x;
}

float Galaxy::GetY() const
{
    return y;
}

float Galaxy::GetBarCoord() const
{
    return bar_coord;
}

float Galaxy::GetDistance() const
{
    return distance;
}

float Galaxy::GetInclination() const
{
    return inclination;
}