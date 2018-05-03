//
//  Disk.h
//  Photometric Model
//
//  Created by Wesley Peters on 5/1/18.
//  Copyright (c) 2018 Wesley Peters. All rights reserved.
//

#ifndef __Photometric_Model__Disk__
#define __Photometric_Model__Disk__

#include <stdio.h>
#include "CCD.h"

class Disk
{
public:
    void makeDisk(float surf_bright_in, float scale_in, float pa_in, float zeropoint, float exptime,float pix);
    float inten(float x, float y, float scale_pix);
    float GetCenInt() const;
    float GetScale() const;
    float GetPa() const;
private:
    float surf_bright;
    float cen_int;
    float scale;
    float pa;
};

#endif /* defined(__Photometric_Model__Disk__) */
