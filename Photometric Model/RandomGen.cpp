//
//  RandomGen.cpp
//  Photometric Model
//
//  Created by Wesley Peters on 5/3/18.
//  Copyright (c) 2018 Wesley Peters. All rights reserved.
//

#include "RandomGen.h"
#include <iostream>

RandomGen::RandomGen()
    :
    rng(rd())
{
}

float RandomGen::genDistance(const UserInput& io)
{
    std::uniform_real_distribution<float> distance_dist{io.GetValue(0,0),io.GetValue(0,1)};
    return distance_dist(rng);
}

float RandomGen::genInclination(const UserInput& io)
{
    std::uniform_real_distribution<float> inc_dist{io.GetValue(1,0),io.GetValue(1,1)};
    return inc_dist(rng);
}

float RandomGen::genSurfDisk(const UserInput& io)
{
    std::uniform_real_distribution<float> surf_disk_dist{io.GetValue(2,0),io.GetValue(2,1)};
    return surf_disk_dist(rng);
}

float RandomGen::genDiskScale(const UserInput& io)
{
    std::uniform_real_distribution<float> disk_scale_dist{io.GetValue(3,0),io.GetValue(3,1)};
    return disk_scale_dist(rng);
}

float RandomGen::genDiskPA(const UserInput& io)
{
    std::uniform_real_distribution<float> pa_dist{io.GetValue(4,0),io.GetValue(4,1)};
    return pa_dist(rng);
}

float RandomGen::genSurfBar(const UserInput& io)
{
    std::uniform_real_distribution<float> surf_bar_dist{io.GetValue(5,0),io.GetValue(5,1)};
    return surf_bar_dist(rng);
}

float RandomGen::genBarEccen(const UserInput& io)
{
    std::uniform_real_distribution<float> bar_ellip_dist{io.GetValue(6,0),io.GetValue(6,1)};
    return bar_ellip_dist(rng);
}

float RandomGen::genBarLen(const UserInput& io)
{
    std::uniform_real_distribution<float> bar_len_dist{io.GetValue(7,0),io.GetValue(7,1)};
    return bar_len_dist(rng);
}

float RandomGen::genBarShape(const UserInput& io)
{
    std::uniform_real_distribution<float> bar_shape_dist{io.GetValue(8,0),io.GetValue(8,1)};
    return bar_shape_dist(rng);
}

float RandomGen::genBarScale(const UserInput& io)
{
    std::uniform_real_distribution<float> bar_scale_dist{io.GetValue(9,0),io.GetValue(9,1)};
    return bar_scale_dist(rng);
}

float RandomGen::genBarPa(const UserInput& io)
{
    std::uniform_real_distribution<float> pa_dist{io.GetValue(4,0),io.GetValue(4,1)};
    return pa_dist(rng);
}

float RandomGen::genSkyNoise()
{
    std::uniform_real_distribution<float> skyDist{90.0f,100.0f};
    return skyDist(rng);
}

float RandomGen::genReadNoise()
{
    std::uniform_real_distribution<float> readDist{3.5f,4.0f};
    return readDist(rng);
}