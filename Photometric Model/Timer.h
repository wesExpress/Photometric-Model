//
//  Timer.h
//  Photometric Model
//
//  Created by Wesley Peters on 5/1/18.
//  Copyright (c) 2018 Wesley Peters. All rights reserved.
//

#ifndef __Photometric_Model__Timer__
#define __Photometric_Model__Timer__

#include <stdio.h>
#include <chrono>

class Timer
{
public:
    Timer();
    float Mark();
private:
    std::chrono::steady_clock::time_point last;
};

#endif /* defined(__Photometric_Model__Timer__) */
