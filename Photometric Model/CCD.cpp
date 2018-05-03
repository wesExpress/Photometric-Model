//
//  CCD.cpp
//  Photometric Model
//
//  Created by Wesley Peters on 5/1/18.
//  Copyright (c) 2018 Wesley Peters. All rights reserved.
//

#include "CCD.h"

int CCD::GetX() const
{
    return nx;
}

int CCD::GetY() const
{
    return ny;
}

int CCD::GetXcen() const
{
    return xcen;
}

int CCD::GetYcen() const
{
    return ycen;
}

float CCD::GetPix() const
{
    return pixscale;
}

float CCD::GetExpt() const
{
    return exptime;
}

float CCD::GetZeropt() const
{
    return zeropoint;
}

