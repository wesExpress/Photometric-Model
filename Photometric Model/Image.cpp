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
    galaxy.setGalaxy();
    
    dist_kpc = galaxy.getDistance()*1000.;
    pix_factor = 1.0f/dist_kpc*206265.0f/ccd.GetPix();

    galaxy.setDisk(ccd.GetZeropt(),ccd.GetExpt(),ccd.GetPix());
    galaxy.setBar(ccd.GetZeropt(),ccd.GetExpt(),ccd.GetPix());
    
    galaxy.writeParams();
}

void Image::createImage()
{
    noise.GenHole(ccd);
    
    // open text file for output
    std::ofstream ofs;
    ofs.open("test.txt", std::ofstream::out | std::ofstream::app);
    
    // loop for making image text file
    float ccdInt;
    
    for(int ny = 0; ny<ccd.GetY(); ny++)
    {
        for(int nx=0;nx<ccd.GetX(); nx++)
        {
            ccdInt = 0.0f;
            galaxy.genCoordsNew(nx, ny, ccd.GetXcen(), ccd.GetYcen());
            bool barError = false;
            if(galaxy.barInten(pix_factor) == -10.0f)
            {
                barError = true;
            }
            
            if(!barError)
            {
                ccdInt = galaxy.diskInten(pix_factor) + galaxy.barInten(pix_factor);
            }
            else
            {
                ccdInt = galaxy.diskInten(pix_factor);
            }
            
            for (int i = 0; i < noise.GetNumHole(); i++)
            {
                if((nx - noise.GetHoleX(i))*(nx - noise.GetHoleX(i)) + (ny - noise.GetHoleY(i))*(ny - noise.GetHoleY(i)) < noise.GetHoleRadius(i))
                {
                    ccdInt = noise.inHole(ccdInt, noise.GetHolePercent(i));
                }
            }
            
            ccdInt += noise.GenNoise();
            
            ofs << ccdInt << " ";
        }
        ofs << std::endl;
    }
    
    // close text file
    ofs.close();
}

void Image::convolveImage()
{
    kernel.calculateMoffat();
    
    int kCenterX = kernel.GetCols()/2;
    int kCenterY = kernel.GetRows()/2;
    
    int rows = ccd.GetY();
    int cols = ccd.GetX();
    
    float *ccdIntConv = new float[rows*cols];
    
    std::ofstream ofs;
    ofs.open("testConv.txt", std::ofstream::out | std::ofstream::app);
    
    for (int i = 0; i < ccd.GetY(); i++)
    {
        for (int j = 0; j < ccd.GetX(); j++)
        {
            ccdIntConv[i*rows+j] = 0.0f;
            for (int m = 0; m < kernel.GetRows(); m++)
            {
                int mm = kernel.GetRows() - 1 - m;
                
                for (int n = 0; n < kernel.GetCols(); n++)
                {
                    int nn = kernel.GetRows() - 1 - n;
                    
                    int ii = i + (m - kCenterY);
                    int jj = j + (n - kCenterX);
                    
                    if(ii >= 0 && ii < ccd.GetY() && jj >= 0 && jj < ccd.GetX())
                    {
                        ccdIntConv[i*rows+j] += GetCCDInt(jj, ii)*kernel.GetMoffat(mm, nn);
                    }
                }
            }
            ofs << ccdIntConv[i*rows+j] << " ";
        }
        ofs << std::endl;
    }
    ofs.close();
    
    delete [] ccdIntConv;
}

float Image::GetCCDInt(int nx, int ny)
{
    float ccdInt = 0.0f;
    galaxy.genCoordsNew(nx, ny, ccd.GetXcen(), ccd.GetYcen());
    bool barError = false;
    if(galaxy.barInten(pix_factor) == -10.0f)
    {
        barError = true;
    }
    
    if(!barError)
    {
        ccdInt = galaxy.diskInten(pix_factor) + galaxy.barInten(pix_factor);
    }
    else
    {
        ccdInt = galaxy.diskInten(pix_factor);
    }
    
    for (int i = 0; i < noise.GetNumHole(); i++)
    {
        if((nx - noise.GetHoleX(i))*(nx - noise.GetHoleX(i)) + (ny - noise.GetHoleY(i))*(ny - noise.GetHoleY(i)) < noise.GetHoleRadius(i))
        {
            ccdInt = noise.inHole(ccdInt, noise.GetHolePercent(i));
        }
    }
    
    ccdInt += noise.GenNoise();
    
    return ccdInt;
}