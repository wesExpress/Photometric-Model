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

class Disk
{
public:
    Disk(float cen_int_in, float scale_in, float pa_in, float rmax_in);
    float inten(float x, float y);
    float GetRmax() const;
    float GetPa() const;
private:
    float cen_int;
    float scale;
    float pa;
    float rmax;
};

#endif /* defined(__Photometric_Model__Disk__) */
