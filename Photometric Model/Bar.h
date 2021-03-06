//
//  Bar.h
//  Photometric Model
//
//  Created by Wesley Peters on 5/1/18.
//  Copyright (c) 2018 Wesley Peters. All rights reserved.
//

#ifndef __Photometric_Model__Bar__
#define __Photometric_Model__Bar__

#include <stdio.h>

class Bar
{
public:
    void makeBarFerrer(float surf_bright_in, float pa, float ellip_in, float len_in, float shape_in, float zeropoint, float exptime, float pix);
    void makeBarFlat(float surf_bright_in, float pa, float ellip_in, float len_in, float shape_in, float scale_in, float zeropoint, float exptime, float pix);
    void makeBarFreeman(float surf_bright_in, float pa, float ellip_in, float len_in, float shape_in, float zeropoint, float exptime, float pix);
    float intenFerrer(float r, float pix_factor);
    float intenFlat(float r, float pix_factor);
    float intenFreeman(float r, float pix_factor);
    float GetCenInt() const;
    float GetLen() const;
    float GetShape() const;
    float GetEllip() const;
    float GetPa() const;
    float GetScale() const;
private:
    float cen_int;
    float surf_bright;
    float pa;
    float ellip;
    float len;
    float shape;
    float scale;
};

#endif /* defined(__Photometric_Model__Bar__) */
