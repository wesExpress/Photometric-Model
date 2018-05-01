//
//  CCD.h
//  Photometric Model
//
//  Created by Wesley Peters on 5/1/18.
//  Copyright (c) 2018 Wesley Peters. All rights reserved.
//

#ifndef __Photometric_Model__CCD__
#define __Photometric_Model__CCD__

#include <stdio.h>

class CCD
{
public:
    CCD(float pix_in, int nx_in, int ny_in);
    int GetX() const;
    int GetY() const;
    float GetPix() const;
private:
    float pix;
    int nx;
    int ny;
};

#endif /* defined(__Photometric_Model__CCD__) */
