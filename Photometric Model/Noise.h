//
//  Noise.h
//  Photometric Model
//
//  Created by Wesley Peters on 5/2/18.
//  Copyright (c) 2018 Wesley Peters. All rights reserved.
//

#ifndef __Photometric_Model__Noise__
#define __Photometric_Model__Noise__

#include <stdio.h>
#include <random>

class Noise
{
public:
    Noise();
    float GenNoise();
private:
    std::random_device rd;
    std::mt19937 rng;
    
    std::uniform_real_distribution<float> skyDist;
    std::uniform_real_distribution<float> readDist;
    
    float skyN;
    float readN;
};

#endif /* defined(__Photometric_Model__Noise__) */
