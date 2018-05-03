//
//  Image.h
//  Photometric Model
//
//  Created by Wesley Peters on 5/3/18.
//  Copyright (c) 2018 Wesley Peters. All rights reserved.
//

#ifndef __Photometric_Model__Image__
#define __Photometric_Model__Image__

#include <stdio.h>

#include "Galaxy.h"
#include "Noise.h"
#include "CCD.h"

class Image
{
public:
    void setComponents();
    void createImage();
private:
    // components of image
    Galaxy galaxy;
    Noise noise;
    CCD ccd;
    
    // parameters for the CCD object
    static constexpr float pixscale = 0.228f;
    static constexpr float exptime = 600.0f;
    static constexpr float zeropoint = 25.0f;
    static constexpr int nx_ccd = 400;
    static constexpr int ny_ccd = 400;
    static constexpr int xcen = nx_ccd/2;
    static constexpr int ycen = ny_ccd/2;
    
    // various parameters
    float dist_kpc;
    float pix_factor;
};

#endif /* defined(__Photometric_Model__Image__) */
