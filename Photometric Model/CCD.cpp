//
//  CCD.cpp
//  Photometric Model
//
//  Created by Wesley Peters on 5/1/18.
//  Copyright (c) 2018 Wesley Peters. All rights reserved.
//

#include "CCD.h"

CCD::CCD(float pix_in, int nx_in, int ny_in)
    :
    pix(pix_in),
    nx(nx_in),
    ny(ny_in)
{
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