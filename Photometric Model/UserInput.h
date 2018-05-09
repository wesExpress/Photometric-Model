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
    std::string GetInputFile(std::string filename);
    void ReadInputs(std::string filename);
    std::string GetValue(std::string name, int col) const;
private:
    static constexpr int numRows = 19;
    static constexpr int numCols = 2;
    
    std::string input_vals[numRows][numCols];
    std::string input_names[numRows];
    
    std::string infile;
};

#endif /* defined(__Photometric_Model__UserInput__) */
