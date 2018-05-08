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
            
            moffat[i][j] = right*top/bottom;
            
            moffatSum += moffat[i][j];
            //std::cout << moffatSum << std::endl;
        }
    }
    
    for (int i = 0; i < rows; i++)
    {
        for(int j =0; j < cols; j++)
        {
            moffat[i][j] = moffat[i][j]/moffatSum;
            
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
    return moffat[i][j];
}