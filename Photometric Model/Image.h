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
#include "Kernel.h"
#include "UserInput.h"

class Image
{
public:
    void setComponents();
    void createImage();
    void convolveImage();
    float GetCCDInt(int nx, int ny);
private:
    // components of image
    Galaxy galaxy;
    Noise noise;
    CCD ccd;
    Kernel kernel;
    UserInput io;
    
    // various parameters
    float dist_kpc;
    float pix_factor;
};

#endif /* defined(__Photometric_Model__Image__) */
