//
//  Disk.cpp
//  Photometric Model
//
//  Created by Wesley Peters on 5/1/18.
//  Copyright (c) 2018 Wesley Peters. All rights reserved.
//

#include "Disk.h"
#include "math.h"

void Disk::makeDisk(float surf_bright_in, float scale_in, float pa_in, float zeropoint, float exptime, float pix)
{
    surf_bright = surf_bright_in;
    scale = scale_in;
    pa = pa_in;
    cen_int = exptime*pix*pix*pow(10.0f,(zeropoint-surf_bright)/2.5);
}

float Disk::inten(float x, float y, float pix_factor)
{
    const float scale_pix = scale*pix_factor;
    return cen_int*exp(-sqrt(x*x + y*y)/scale_pix);
}

float Disk::GetCenInt() const
{
    return cen_int;
}

float Disk::GetScale() const
{
    return scale;
}

float Disk::GetPa() const
{
    return pa;
}