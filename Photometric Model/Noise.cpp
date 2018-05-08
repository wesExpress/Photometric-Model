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

bool Noise::patchyDisk(UserInput& io)
{
    name = "patchy_disk";
    return io.GetValue(name, 0) == 1.0f;
}

void Noise::GenHole(const CCD& ccd)
{
    for (int i = 0; i < numHoles; i++)
    {
        holeX[i] = randGen.genHoleX(ccd);
        holeY[i] = randGen.genHoleY(ccd);
        holePercent[i] = randGen.genHolePercent();
        holeRadii[i] = randGen.genHoleRadii();
    }
}

float Noise::inHole(float inten, float percent)
{
    return inten*percent;
}

int Noise::GetHoleX(int i)
{
    return holeX[i];
}

int Noise::GetHoleY(int i)
{
    return holeY[i];
}

float Noise::GetHoleRadius(int i)
{
    return holeRadii[i];
}

float Noise::GetHolePercent(int i)
{
    return holePercent[i];
}

int Noise::GetNumHole()
{
    return numHoles;
}