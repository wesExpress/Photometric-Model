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

class Kernel
{
public:
    void calculateMoffat();
    int GetCols();
    int GetRows();
    float GetMoffat(int i, int j);
private:
    static constexpr int cols = 5;
    static constexpr int rows = 5;
    
    static constexpr float beta = 3.0f;
    static constexpr float fwhm = 4.385f;
    float alpha = fwhm/(2.0f*sqrt(pow(2.0f,1.0f/beta) - 1.0f));
    
    float moffat[cols][rows];
    float x[cols] = {-2,-1,0,1,2};
    float y[rows] = {-2,-1,0,1,2};
};

#endif /* defined(__Photometric_Model__Kernel__) */
