//
//  RandomGen.h
//  Photometric Model
//
//  Created by Wesley Peters on 5/3/18.
//  Copyright (c) 2018 Wesley Peters. All rights reserved.
//

#ifndef __Photometric_Model__RandomGen__
#define __Photometric_Model__RandomGen__

#include <stdio.h>
#include <string>
#include <random>
#include <fstream>

#include "UserInput.h"

class RandomGen
{
public:
    RandomGen();
    
    // galaxy wide parameters
    float genDistance(const UserInput& io);
    float genInclination(const UserInput&  io);
    // disk parameters
    float genSurfDisk(const UserInput& io);
    float genDiskScale(const UserInput& io);
    float genDiskPA(const UserInput& io);
    // bar parameters
    float genSurfBar(const UserInput& io);
    float genBarEccen(const UserInput& io);
    float genBarLen(const UserInput& io);
    float genBarShape(const UserInput& io);
    float genBarScale(const UserInput& io);
    float genBarPa(const UserInput& io);
    
    // noise
    float genSkyNoise();
    float genReadNoise();
private:
    // random initializations
    std::random_device rd;
    std::mt19937 rng;
    
    // parameter name
    std::string name;
    static constexpr int minCol = 0;
    static constexpr int maxCol = 1;
};

#endif /* defined(__Photometric_Model__RandomGen__) */
