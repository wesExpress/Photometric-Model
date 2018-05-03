//
//  Bar.cpp
//  Photometric Model
//
//  Created by Wesley Peters on 5/1/18.
//  Copyright (c) 2018 Wesley Peters. All rights reserved.
//

#include <iostream>

#include "Bar.h"
#include "math.h"

void Bar::makeBar(float surf_bright_in, float pa_in, float ellip_in, float len_in, float shape_in, float scale_in, const CCD& ccd)
{
    surf_bright = surf_bright_in;
    pa=pa_in;
    ellip=ellip_in;
    len=len_in;
    shape=shape_in;
    cen_int = ccd.GetExpt()*ccd.GetPix()*ccd.GetPix()*pow(10,(ccd.GetZeropt()-surf_bright)/2.5);
    scale = scale_in;
}

float Bar::intenFreeman(float r, float pix_factor)
{
    const float len_pix = len*pix_factor;
    if(r <= len_pix)
    {
        return cen_int*pow(1.0f - (r/len_pix)*(r/len_pix),2.5f);
    }
    else
    {
        return 0.0f;
    }
}

float Bar::intenFlat(float r, float pix_factor)
{
    const float len_pix = len*pix_factor;
    return cen_int*(1.0f/(1.0f+exp((r-len_pix)/scale)));
}

float Bar::GetCenInt() const
{
    return cen_int;
}

float Bar::GetLen() const
{
    return len;
}

float Bar::GetShape() const
{
    return shape;
}

float Bar::GetEllip() const
{
    return ellip;
}

float Bar::GetPa() const
{
    return pa;
}

float Bar::GetScale() const
{
    return scale;
}