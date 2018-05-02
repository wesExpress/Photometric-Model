//
//  Noise.cpp
//  Photometric Model
//
//  Created by Wesley Peters on 5/2/18.
//  Copyright (c) 2018 Wesley Peters. All rights reserved.
//

#include "Noise.h"

Noise::Noise()
    :
    rng(rd()),
    skyDist(90.0f,100.0f),
    readDist(2.0f,4.0f)
{
}

float Noise::GenNoise()
{
    skyN = skyDist(rng);
    readN = readDist(rng);
    return skyN + readN;
}