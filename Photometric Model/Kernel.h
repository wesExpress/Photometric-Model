//
//  Kernel.h
//  Photometric Model
//
//  Created by Wesley Peters on 5/8/18.
//  Copyright (c) 2018 Wesley Peters. All rights reserved.
//

#ifndef __Photometric_Model__Kernel__
#define __Photometric_Model__Kernel__

#include <stdio.h>
#include "math.h"
#include "UserInput.h"
#include "RandomGen.h"
#include <string>

class Kernel
{
public:
    void ReadSeeing(UserInput& io, RandomGen& randG);
    void calculateMoffat();
    int GetCols();
    int GetRows();
    float GetMoffat(int i, int j);
    bool convolve(UserInput& io);
    float GetFWHM();
private:
    static constexpr int cols = 11;
    static constexpr int rows = 11;
    
    float beta;
    float fwhm;
    float alpha;
    
    float moffat[cols*rows];
    float x[cols] = {-5,-4,-3,-2,-1,0,1,2,3,4,5};
    float y[rows] = {-5,-4,-3,-2,-1,0,1,2,3,4,5};
    
    std::string name;
};

#endif /* defined(__Photometric_Model__Kernel__) */
