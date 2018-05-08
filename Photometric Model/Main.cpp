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

#include "Image.h"

int main()
{
    Image image;
    image.setComponents();
    image.createImage();
    image.convolveImage();
    
    return 0;
}