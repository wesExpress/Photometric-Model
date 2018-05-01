//
//  Main.cpp
//  Photometric Model
//
//  Created by Wesley Peters on 5/1/18.
//  Copyright (c) 2018 Wesley Peters. All rights reserved.
//

#include <fstream>
#include <iostream>

#include "Galaxy.h"
#include "Timer.h"

int main()
{
    // open text file for output
    std::ofstream ofs;
    ofs.open("test.txt", std::ofstream::out | std::ofstream::app);
    
    // object that controls the galaxy parameters
    // includes various components
    Galaxy galaxy;
    
    // parameters for the CCD object
    static constexpr float pixscale = 0.228f;
    static constexpr int nx_ccd = 400;
    static constexpr int ny_ccd = 400;
    CCD ccd(pixscale,nx_ccd,ny_ccd);
    float dum[nx_ccd] = {0.0f};
    
    // looping variables
    static constexpr int rad_len = 500;
    static constexpr int coord_len = 2*rad_len;
    //static constexpr int array_len = coord_len*coord_len;
    //int l = 0;
    
    Timer timer;
    
    float dt = timer.Mark();
    
    // main loop for making image text file
    for(int ny = 0; ny<ccd.GetY();ny++)
    {
        // test write to terminal
        if(ny != 0)
        {
            std::cout << dt << "seconds" << std::endl;
        }
        
        float ccd_int = 0.0f;
        float ccd_int_disk = 0.0f;
        float ccd_int_bar= 0.0f;
        
        for(int nx=0;nx<ccd.GetX();nx++)
        {
            int disk_cnt=0;
            int bar_cnt=0;
            
            // run through the galaxy coordinates
            for(int i = 0; i < coord_len; i++)
            {
                for(int j = 0; j<coord_len; j++)
                {
                    galaxy.genCoords(i, j, coord_len, ccd);
                    float x = galaxy.GetX();
                    float y = galaxy.GetY();
                    float r = galaxy.GetR();
                
                    float inten = galaxy.inten(x,y,r);
                
                    int xcen = ccd.GetX()/2;
                    int ycen = ccd.GetY()/2;
                    float x_disk_rot = galaxy.rotCoordX_disk(x, y, xcen);
                    float y_disk_rot = galaxy.rotCoordY_disk(x, y, ycen);
                    float x_bar_rot = galaxy.rotCoordX_bar(x, y, xcen);
                    float y_bar_rot = galaxy.rotCoordY_bar(x, y, ycen);
                    
                    // check if disk intensity falls in a CCD pixel
                    if(x_disk_rot >= nx && x_disk_rot < nx+1 && y_disk_rot >= ny && y_disk_rot < ny+1)
                    {
                        ccd_int_disk+=inten;
                        disk_cnt+=1;
                    }
                    // check if bar intensity falls in a CCD pixel
                    if(x_bar_rot >= nx && x_bar_rot < nx+1 && y_bar_rot >= ny && y_bar_rot < ny+1)
                    {
                        ccd_int_bar+=inten;
                        bar_cnt+=1;
                    }
                }
            }
            // normalizes disk intensity based on how much of disk is in one pixel
            if(disk_cnt != 0)
            {
                ccd_int_disk = ccd_int_disk/float(disk_cnt);
            }
            else
            {
                ccd_int_disk = 0.0f;
            }
            
            // normalizes disk intensity based on how much of bar is in one pixel
            if(bar_cnt != 0)
            {
                ccd_int_bar = ccd_int_bar/float(bar_cnt);
            }
            else
            {
                ccd_int_bar = 0.0f;
            }
            
            // assigns the intensity to pixel
            ccd_int += ccd_int_disk+ccd_int_disk;
            // assigns this pixel intensity to array to be written out
            dum[nx] = ccd_int;
            if(ccd_int != 0)
            {
                std::cout << ccd_int << std::endl;
            }
            // resets the values for next iteration
            ccd_int = 0.0f;
            ccd_int_disk=0.0f;
            ccd_int_bar=0.0f;
            
            disk_cnt=0.0f;
            bar_cnt=0.0f;
            
            //l++;
        }
        
        // write out line to text file
        ofs << dum;
        
        dt = timer.Mark();
    }
    
    // close text file
    ofs.close();
    
    return 0;
}