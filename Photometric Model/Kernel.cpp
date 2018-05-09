//
//  Kernel.cpp
//  Photometric Model
//
//  Created by Wesley Peters on 5/8/18.
//  Copyright (c) 2018 Wesley Peters. All rights reserved.
//

#include "Kernel.h"
#include <iostream>
#include <numeric>

#define PI 3.1415926535

bool Kernel::convolve(UserInput& io)
{
    name = "seeing";
    if(std::stof(io.GetValue(name, 0)) == 1.0f)
    {
        return true;
    }
    return false;
}

void Kernel::ReadSeeing(UserInput& io)
{
    // must be in pixels!!! //
    name = "fwhm";
    fwhm = std::stof(io.GetValue(name,0));
    name = "beta";
    beta = std::stof(io.GetValue(name,0));
    alpha = fwhm/(2.0f*sqrt(pow(2.0f,1.0f/beta) - 1.0f));
        
    std::cout << std::endl;
    std::cout << "FWHM (pixels) = " << fwhm << std::endl;
    std::cout << "Beta = " << beta << std::endl;
    std::cout << std::endl;
}

void Kernel::calculateMoffat()
{
    float top = beta - 1.0f;
    float bottom = PI*alpha*alpha;
    float moffatSum = 0.0f;
    
    for (int i = 0; i < rows; i++)
    {
        for(int j =0; j < cols; j++)
        {
            float r = x[j]*x[j] + y[i]*y[i];
            float right = pow(1.0f + (r*r)/alpha,-beta);
            
            moffat[i*rows + j] = right*top/bottom;
            
            moffatSum += moffat[i*rows + j];
            //std::cout << moffatSum << std::endl;
        }
    }
    
    for (int i = 0; i < rows; i++)
    {
        for(int j =0; j < cols; j++)
        {
            moffat[i*rows + j] = moffat[i*rows + j]/moffatSum;
            
        }
    }
}

int Kernel::GetCols()
{
    return cols;
}

int Kernel::GetRows()
{
    return rows;
}

float Kernel::GetMoffat(int i, int j)
{
    return moffat[i*rows + j];
}