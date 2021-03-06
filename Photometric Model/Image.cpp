//
//  Image.cpp
//  Photometric Model
//
//  Created by Wesley Peters on 5/3/18.
//  Copyright (c) 2018 Wesley Peters. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <cstdio>
#include <iomanip>

#include "Image.h"

void Image::Run(std::string filename, std::string output)
{
    setComponents(filename, output);
    createImage(output);
}

void Image::setComponents(std::string filename, std::string output)
{
    galaxy.setGalaxy(io,filename,randG);
    
    dist_kpc = galaxy.getDistance()*1000.;
    pix_factor = 1.0f/dist_kpc*206265.0f/ccd.GetPix();

    galaxy.setDisk(ccd,io,randG);
    galaxy.setBar(ccd,io,randG);
    
    galaxy.writeParamsTerminal();
    
    if(kernel.convolve(io))
    {
        kernel.ReadSeeing(io,randG);
    }
    
    writeImageParams(output);
}

void Image::createImage(std::string output_in)
{
    std::string output = output_in + ".txt";
    
    std::ifstream fileCheck(output);
    if(fileCheck)
    {
        if(std::remove(output.c_str()) != 0)
        {
            perror("Error deleting file.");
        }
        else
        {
            //puts("Deleted file.");
        }
    }
    
    // open text file for output
    std::ofstream ofs;
    ofs.open(output, std::ofstream::out | std::ofstream::app);
    
    std::cout << "Creating image... " << std::endl;
    timer.Mark();
    
    if(noise.patchyDisk(io))
    {
        noise.GenHole(ccd);
    }
    
    // loop for making image text file
    int ccdCols = ccd.GetX();
    int ccdRows = ccd.GetY();
    float *ccdInt = new float[ccdCols*ccdRows];
    
    for(int ny = 0; ny < ccdRows; ny++)
    {
        for(int nx=0;nx < ccdCols; nx++)
        {
            ccdInt[ny*ccdRows + nx] = GetCCDInt(nx, ny);
            
            ofs << ccdInt[ny*ccdRows + nx] << " ";
        }
        ofs << std::endl;
    }
    
    // close text file
    ofs.close();
    
    std::cout << "Done. Took " << timer.Mark() << " seconds." << std::endl;
    
    if(kernel.convolve(io))
    {
        std::cout << "Convolving image..." << std::endl;
        timer.Mark();
        convolveImage(ccdInt, ccdRows, output_in);
        std::cout << "Done. Took " << timer.Mark() << " seconds." << std::endl;
    }
    else
    {
        std::cout << "No convolution performed." << std::endl;
    }
    
    delete [] ccdInt;
}

void Image::convolveImage(float ccdArray[], int rowsIn, std::string output_in)
{
    std::string output = output_in + "_conv.txt";
    
    std::ifstream fileCheck(output);
    if(fileCheck)
    {
        if(std::remove(output.c_str()) != 0)
        {
            perror("Error deleting file.");
        }
        else
        {
            //puts("Deleted file.");
        }
    }
    
    std::ofstream ofs;
    ofs.open(output, std::ofstream::out | std::ofstream::app);
    
    kernel.calculateMoffat();
    
    int kCenterX = kernel.GetCols()/2;
    int kCenterY = kernel.GetRows()/2;
    
    int rows = ccd.GetY();
    int cols = ccd.GetX();
    
    float *ccdIntConv = new float[rows*cols];
    
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
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
                    
                    if(ii >= 0 && ii < rows && jj >= 0 && jj < cols)
                    {
                        ccdIntConv[i*rows+j] += ccdArray[ii*rowsIn + jj]*kernel.GetMoffat(mm, nn);
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
    float inten = 0.0f;
    galaxy.genCoordsNew(nx, ny, ccd.GetXcen(), ccd.GetYcen());
    bool barError = false;
    if(galaxy.barInten(pix_factor) == -10.0f)
    {
        barError = true;
    }
    
    if(!barError)
    {
        inten = galaxy.diskInten(pix_factor) + galaxy.barInten(pix_factor);
    }
    else
    {
        inten = galaxy.diskInten(pix_factor);
    }
    
    if(noise.patchyDisk(io))
    {
        for (int i = 0; i < noise.GetNumHole(); i++)
        {
            if((nx - noise.GetHoleX(i))*(nx - noise.GetHoleX(i)) + (ny - noise.GetHoleY(i))*(ny - noise.GetHoleY(i)) < noise.GetHoleRadius(i))
            {
                inten = noise.inHole(inten, noise.GetHolePercent(i));
            }
        }
    }
    
    inten += noise.GenNoise();
    
    return inten;
}

void Image::writeImageParams(std::string output_in)
{
    std::string output = output_in + "_params.txt";
    
    std::ifstream fileCheck(output);
    if(fileCheck)
    {
        if(std::remove(output.c_str()) != 0)
        {
            perror("Error deleting file.");
        }
        else
        {
            //puts("Deleted file.");
        }
    }
    
    galaxy.writeParamsFile(output,pix_factor);
    
    std::ofstream ofs;
    ofs.open(output, std::ofstream::out | std::ofstream::app);
    
    int align = 20;
    
    ofs << std::right << std::setw(align) << "seeing ";
    ofs << std::right << std::setw(align) << kernel.GetFWHM() << std:: endl;
}
