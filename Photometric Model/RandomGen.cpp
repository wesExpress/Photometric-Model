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

void RandomGen::readInputs()
{
    std::ifstream infile(io.GetInputFile());
    std::string s;
    int i = 0;
    while(std::getline(infile, s))
    {
        infile >> inputs[i][0] >> inputs[i][1];
        i++;
    }
    infile.close();
}

float RandomGen::genDistance()
{
    std::uniform_real_distribution<float> distance_dist{inputs[0][0],inputs[0][1]};
    return distance_dist(rng);
}

float RandomGen::genInclination()
{
    std::uniform_real_distribution<float> inc_dist{inputs[1][0],inputs[1][1]};
    return inc_dist(rng);
}

float RandomGen::genSurfDisk()
{
    std::uniform_real_distribution<float> surf_disk_dist{inputs[2][0],inputs[2][1]};
    return surf_disk_dist(rng);
}

float RandomGen::genDiskScale()
{
    std::uniform_real_distribution<float> disk_scale_dist{inputs[3][0],inputs[3][1]};
    return disk_scale_dist(rng);
}

float RandomGen::genDiskPA()
{
    std::uniform_real_distribution<float> pa_dist{inputs[4][0],inputs[4][1]};
    return pa_dist(rng);
}

float RandomGen::genSurfBar()
{
    std::uniform_real_distribution<float> surf_bar_dist{inputs[5][0],inputs[5][1]};
    return surf_bar_dist(rng);
}

float RandomGen::genBarEccen()
{
    std::uniform_real_distribution<float> bar_ellip_dist{inputs[6][0],inputs[6][1]};
    return bar_ellip_dist(rng);
}

float RandomGen::genBarLen()
{
    std::uniform_real_distribution<float> bar_len_dist{inputs[7][0],inputs[7][1]};
    return bar_len_dist(rng);
}

float RandomGen::genBarShape()
{
    std::uniform_real_distribution<float> bar_shape_dist{inputs[8][0],inputs[8][1]};
    return bar_shape_dist(rng);
}

float RandomGen::genBarScale()
{
    std::uniform_real_distribution<float> bar_scale_dist{inputs[9][0],inputs[9][1]};
    return bar_scale_dist(rng);
}

float RandomGen::genBarPa()
{
    std::uniform_real_distribution<float> pa_dist{inputs[4][0],inputs[4][1]};
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