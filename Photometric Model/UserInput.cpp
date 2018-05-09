//
//  UserInput.cpp
//  Photometric Model
//
//  Created by Wesley Peters on 5/4/18.
//  Copyright (c) 2018 Wesley Peters. All rights reserved.
//

#include "UserInput.h"

std::string UserInput::GetInputFile()
{
    while (true)
    {
        std::cout << "Enter file name : " << std::endl;
        std::string test;
        getline(std::cin, test);
        
        std::ifstream fileCheck(test);
        if(fileCheck)
        {
            infile = test;
            std::cout << std::endl;
            //std::cout << infile << std::endl;
            return infile;
        }
        else
        {
            std::cout << "Error: No such file in this directory. Try again." << std::endl;;
        }
    }
}

void UserInput::ReadInputs()
{
    std::ifstream infile(GetInputFile());
    std::string s;
    int i = 0;
    while(std::getline(infile, s))
    {
        infile >> input_names[i] >> input_vals[i][0] >> input_vals[i][1];
        //std::cout << input_names[i] << std::endl;
        i++;
    }
    infile.close();
}

std::string UserInput::GetValue(std::string name, int col) const
{
    int index = -1;
    for(int i = 0; i < numRows; i++)
    {
        if(name == input_names[i])
        {
            index = i;
        }
    }
    
    if(index != -1)
    {
        return input_vals[index][col];
    }
    else
    {
        std::cout << "Error: Parameter " << name << " missing from input file.";
        return std::to_string(-180.0f);
    }
}