//
//  Main.cpp
//  Photometric Model
//
//  Created by Wesley Peters on 5/1/18.
//  Copyright (c) 2018 Wesley Peters. All rights reserved.
//
//  Now on GitHub!

#include <fstream>
#include <iostream>
#include <string>

#include "Image.h"

int main(int argc, char* argv[])
{
    std::string filename = argv[1];
    std::string output = argv[2];
    
    Image image;
    image.Run(filename,output);
    
    return 0;
}