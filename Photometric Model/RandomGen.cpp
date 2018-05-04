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
    name = "distance";
    std::uniform_real_distribution<float> distance_dist{io.GetValue(name,0),io.GetValue(name,1)};
    return distance_dist(rng);
}

float RandomGen::genInclination(const UserInput& io)
{
    name = "inclination";
    std::uniform_real_distribution<float> inc_dist{io.GetValue(name,0),io.GetValue(name,1)};
    return inc_dist(rng);
}

float RandomGen::genSurfDisk(const UserInput& io)
{
    name = "surf_disk";
    std::uniform_real_distribution<float> surf_disk_dist{io.GetValue(name,0),io.GetValue(name,1)};
    return surf_disk_dist(rng);
}

float RandomGen::genDiskScale(const UserInput& io)
{
    name = "disk_scale";
    std::uniform_real_distribution<float> disk_scale_dist{io.GetValue(name,0),io.GetValue(name,1)};
    return disk_scale_dist(rng);
}

float RandomGen::genDiskPA(const UserInput& io)
{
    name = "disk_pa";
    std::uniform_real_distribution<float> pa_dist{io.GetValue(name,0),io.GetValue(name,1)};
    return pa_dist(rng);
}

float RandomGen::genSurfBar(const UserInput& io)
{
    name = "surf_bar";
    std::uniform_real_distribution<float> surf_bar_dist{io.GetValue(name,0),io.GetValue(name,1)};
    return surf_bar_dist(rng);
}

float RandomGen::genBarEccen(const UserInput& io)
{
    name = "bar_ecc";
    std::uniform_real_distribution<float> bar_ecc_dist{io.GetValue(name,0),io.GetValue(name,1)};
    return bar_ecc_dist(rng);
}

float RandomGen::genBarLen(const UserInput& io)
{
    name = "bar_len";
    std::uniform_real_distribution<float> bar_len_dist{io.GetValue(name,0),io.GetValue(name,1)};
    return bar_len_dist(rng);
}

float RandomGen::genBarShape(const UserInput& io)
{
    name = "bar_shape";
    std::uniform_real_distribution<float> bar_shape_dist{io.GetValue(name,0),io.GetValue(name,1)};
    return bar_shape_dist(rng);
}

float RandomGen::genBarScale(const UserInput& io)
{
    name = "bar_scale";
    std::uniform_real_distribution<float> bar_scale_dist{io.GetValue(name,0),io.GetValue(name,1)};
    return bar_scale_dist(rng);
}

float RandomGen::genBarPa(const UserInput& io)
{
    name = "bar_pa";
    std::uniform_real_distribution<float> pa_dist{io.GetValue(name,0),io.GetValue(name,1)};
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