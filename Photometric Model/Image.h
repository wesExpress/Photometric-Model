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
#include "Timer.h"
#include "RandomGen.h"

class Image
{
public:
    void Run(std::string filename, std::string output);
    void setComponents(std::string filename, std::string output);
    void createImage(std::string output_in);
    void convolveImage(float ccdArray[], int rowsIn, std::string output_in);
    float GetCCDInt(int nx, int ny);
    void writeImageParams(std::string output_in);
private:
    RandomGen randG;
    
    // components of image
    Galaxy galaxy;
    Noise noise;
    CCD ccd;
    Kernel kernel;
    UserInput io;
    Timer timer;
    
    // various parameters
    float dist_kpc;
    float pix_factor;
    
    std::string name;
};

#endif /* defined(__Photometric_Model__Image__) */
