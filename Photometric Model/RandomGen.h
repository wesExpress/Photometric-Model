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

class RandomGen
{
public:
    RandomGen();
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
    
    // galaxy parameters
    std::uniform_real_distribution<float> distance_dist{70.0f,120.0f};
    std::uniform_real_distribution<float> inc_dist{20.0f,65.0f};
    std::uniform_real_distribution<float> surf_disk_dist{22.5f,24.0f};
    std::uniform_real_distribution<float> disk_scale_dist{3.0f,7.0f};
    std::uniform_real_distribution<float> pa_dist{-90.0f,90.0f};
    std::uniform_real_distribution<float> surf_bar_dist{22.0f,23.0f};
    std::uniform_real_distribution<float> bar_ellip_dist{0.5f,0.7f};
    std::uniform_real_distribution<float> bar_len_dist{2.0f,6.5f};
    std::uniform_real_distribution<float> bar_shape_dist{1.8f,2.2f};
    std::uniform_real_distribution<float> bar_scale_dist{3.0f,7.0f};
    
    // noise parameters
    std::uniform_real_distribution<float> skyDist{90.0f,100.0f};
    std::uniform_real_distribution<float> readDist{3.5f,4.0f};
};

#endif /* defined(__Photometric_Model__RandomGen__) */
