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
#include <random>
#include <fstream>

class RandomGen
{
public:
    RandomGen();
    void readInputs();
    // galaxy wide parameters
    float genDistance();
    float genInclination();
    // disk parameters
    float genSurfDisk();
    float genDiskScale();
    float genDiskPA();
    // bar parameters
    float genSurfBar();
    float genBarEccen();
    float genBarLen();
    float genBarShape();
    float genBarScale();
    float genBarPa();
    
    // noise
    float genSkyNoise();
    float genReadNoise();
private:
    // random initializations
    std::random_device rd;
    std::mt19937 rng;
    
    static constexpr int numRows = 10;
    static constexpr int numCols = 2;
    
    float inputs[numRows][numCols];
};

#endif /* defined(__Photometric_Model__RandomGen__) */
