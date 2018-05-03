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
#include "RandomGen.h"

class Noise
{
public:
    float GenNoise();
private:
    RandomGen randGen;
    float skyN;
    float readN;
};

#endif /* defined(__Photometric_Model__Noise__) */
