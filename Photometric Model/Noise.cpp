//
//  Noise.cpp
//  Photometric Model
//
//  Created by Wesley Peters on 5/2/18.
//  Copyright (c) 2018 Wesley Peters. All rights reserved.
//

#include "Noise.h"

float Noise::GenNoise()
{
    skyN = randGen.genSkyNoise();
    readN = randGen.genReadNoise();
    
    return skyN + readN;
}