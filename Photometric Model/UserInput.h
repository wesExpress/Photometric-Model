//
//  UserInput.h
//  Photometric Model
//
//  Created by Wesley Peters on 5/4/18.
//  Copyright (c) 2018 Wesley Peters. All rights reserved.
//

#ifndef __Photometric_Model__UserInput__
#define __Photometric_Model__UserInput__

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

class UserInput
{
public:
    std::string GetInputFile();
    void ReadInputs();
    float GetValue(int row, int col) const;
private:
    static constexpr int numRows = 10;
    static constexpr int numCols = 2;
    
    float inputs[numRows][numCols];
    
    std::string infile;
};

#endif /* defined(__Photometric_Model__UserInput__) */