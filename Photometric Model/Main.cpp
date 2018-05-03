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

#include "Galaxy.h"
#include "Noise.h"
#include "Timer.h"

int main()
{
    // open text file for output
    std::ofstream ofs;
    ofs.open("test.txt", std::ofstream::out | std::ofstream::app);
    
    // parameters for the CCD object
    static constexpr float pixscale = 0.228f;
    static constexpr float exptime = 600.0f;
    static constexpr float zeropoint = 25.0f;
    static constexpr int nx_ccd = 400;
    static constexpr int ny_ccd = 400;
    CCD ccd(pixscale,exptime,zeropoint,nx_ccd,ny_ccd);
    
    // object that controls the galaxy parameters
    // includes various components (see class definition of Galaxy
    Galaxy galaxy(ccd);
    
    const float dist_kpc = galaxy.getDistance()*1000.;
    
    const float pix_factor = 1.0f/dist_kpc*206265.0f/ccd.GetPix();
    
    // class of noise for image
    Noise noise;
    
    //Timer timer;
    
    // main loop for making image text file
    float ccd_int;
    for(int ny = 0; ny<ccd.GetY();ny++)
    {
        for(int nx=0;nx<ccd.GetX();nx++)
        {
            ccd_int = 0.0f;
            galaxy.genCoordsNew(nx, ny, ccd);
            
            ccd_int = galaxy.diskInten(pix_factor) + galaxy.barInten(pix_factor) + noise.GenNoise();
            
            ofs << ccd_int << " ";
        }
        
        // write out line to text file
        //ofs << dum;
        ofs << std::endl;
    }
    
    // close text file
    ofs.close();
    
    return 0;
}