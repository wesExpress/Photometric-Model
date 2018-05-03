//
//  Image.cpp
//  Photometric Model
//
//  Created by Wesley Peters on 5/3/18.
//  Copyright (c) 2018 Wesley Peters. All rights reserved.
//

#include <fstream>
#include <iostream>

#include "Image.h"

void Image::setComponents()
{
    ccd.setCCD(pixscale, exptime, zeropoint, nx_ccd, ny_ccd);
    galaxy.setGalaxy();
    
    dist_kpc = galaxy.getDistance()*1000.;
    pix_factor = 1.0f/dist_kpc*206265.0f/pixscale;

    galaxy.setDisk(zeropoint, exptime, pixscale);
    galaxy.setBar(zeropoint, exptime, pixscale);
    
    galaxy.writeParams();
}

void Image::createImage()
{
    // open text file for output
    std::ofstream ofs;
    ofs.open("test.txt", std::ofstream::out | std::ofstream::app);
    
    // loop for making image text file
    float ccd_int;
    for(int ny = 0; ny<ccd.GetY();ny++)
    {
        for(int nx=0;nx<ccd.GetX();nx++)
        {
            ccd_int = 0.0f;
            galaxy.genCoordsNew(nx, ny, xcen, ycen);
            
            ccd_int = galaxy.diskInten(pix_factor) + galaxy.barInten(pix_factor) + noise.GenNoise();
            
            ofs << ccd_int << " ";
        }
        
        // write out line to text file
        //ofs << dum;
        ofs << std::endl;
    }
    
    // close text file
    ofs.close();
}