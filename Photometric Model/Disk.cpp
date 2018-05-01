//
//  Disk.cpp
//  Photometric Model
//
//  Created by Wesley Peters on 5/1/18.
//  Copyright (c) 2018 Wesley Peters. All rights reserved.
//

#include "Disk.h"
#include "math.h"

Disk::Disk(float cen_int_in, float scale_in, float pa_in, float rmax_in)
    :
    cen_int(cen_int_in),
    scale(scale_in),
    pa(pa_in),
    rmax(rmax_in)
{
}

float Disk::inten(float x, float y)
{
    return cen_int*exp(-sqrt(x*x + y*y)/scale);
}

float Disk::GetRmax() const
{
    return rmax;
}

float Disk::GetPa() const
{
    return pa;
}