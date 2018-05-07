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
#include "CCD.h"

class Noise
{
public:
    float GenNoise();
    void GenHole(const CCD& ccd);
    float inHole(float inten, float percent);
    int GetHoleX(int i);
    int GetHoleY(int i);
    int GetNumHole();
    float GetHoleRadius(int i);
    float GetHolePercent(int i);
private:
    RandomGen randGen;
    
    float skyN;
    float readN;
    
    static constexpr int numHoles = 100;
    int holeX[numHoles];
    int holeY[numHoles];
    float holePercent[numHoles];
    float holeRadii[numHoles];
};

#endif /* defined(__Photometric_Model__Noise__) */
