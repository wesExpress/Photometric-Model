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
    int GetX() const;
    int GetY() const;
    int GetXcen() const;
    int GetYcen() const;
    float GetPix() const;
    float GetExpt() const;
    float GetZeropt() const;
private:
    static constexpr float pixscale = 0.228f;
    static constexpr float exptime = 600.0f;
    static constexpr float zeropoint = 25.0f;
    static constexpr int nx = 400;
    static constexpr int ny = 400;
    static constexpr int xcen = nx/2;
    static constexpr int ycen = ny/2;
};

#endif /* defined(__Photometric_Model__CCD__) */
