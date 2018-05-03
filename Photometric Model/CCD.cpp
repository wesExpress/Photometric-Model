//
//  CCD.cpp
//  Photometric Model
//
//  Created by Wesley Peters on 5/1/18.
//  Copyright (c) 2018 Wesley Peters. All rights reserved.
//

#include "CCD.h"

void CCD::setCCD(float pix_in, float expt_in, float zeropt_in, int nx_in, int ny_in)
{
    pix = pix_in;
    expt = expt_in;
    zeropt = zeropt_in;
    nx = nx_in;
    ny = ny_in;
}

int CCD::GetX() const
{
    return nx;
}

int CCD::GetY() const
{
    return ny;
}

float CCD::GetPix() const
{
    return pix;
}

float CCD::GetExpt() const
{
    return expt;
}

float CCD::GetZeropt() const
{
    return zeropt;
}