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

float RandomGen::genDistance()
{
    return distance_dist(rng);
}

float RandomGen::genInclination()
{
    return inc_dist(rng);
}

float RandomGen::genSurfDisk()
{
    return surf_disk_dist(rng);
}

float RandomGen::genDiskScale()
{
    return disk_scale_dist(rng);
}

float RandomGen::genDiskPA()
{
    return pa_dist(rng);
}

float RandomGen::genSurfBar()
{
    return surf_bar_dist(rng);
}

float RandomGen::genBarEccen()
{
    return bar_ellip_dist(rng);
}

float RandomGen::genBarLen()
{
    return bar_len_dist(rng);
}

float RandomGen::genBarShape()
{
    return bar_shape_dist(rng);
}

float RandomGen::genBarScale()
{
    return bar_scale_dist(rng);
}

float RandomGen::genBarPa()
{
    return pa_dist(rng);
}

float RandomGen::genSkyNoise()
{
    return skyDist(rng);
}

float RandomGen::genReadNoise()
{
    return readDist(rng);
}