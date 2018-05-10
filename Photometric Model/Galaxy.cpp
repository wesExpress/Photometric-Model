//
//  Galaxy.cpp
//  Photometric Model
//
//  Created by Wesley Peters on 5/1/18.
//  Copyright (c) 2018 Wesley Peters. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iomanip>

#include "Galaxy.h"
#include "math.h"

#define PI 3.1415926535

void Galaxy::setGalaxy(UserInput& io, std::string filename, RandomGen& randG)
{
    io.ReadInputs(filename);
    
    barInput = std::stof(io.GetValue(barInputString, 0));
    
    distance = randG.genDistance(io);
    
    if(barInput != barNo)
    {
        // makes sure the disk is fainter than bar
        while (true)
        {
            surfDiskTry = randG.genSurfDisk(io);
            surfBarTry = randG.genSurfBar(io);
            const float cond = surfDiskTry - surfBarTry;
        
            if(cond > 0.0f && cond < 1.0f)
            {
                break;
            }
        }
        // makes sure the bar is shorter than the scale length of the disk
        while (true)
        {
            diskScaleTry = randG.genDiskScale(io);
            barLenTry = randG.genBarLen(io);
            if(barInput == barFerrer || barInput == barFreeman)
            {
                if(barLenTry < diskScaleTry)
                {
                    break;
                }
            }
            if(barInput == barFlat)
            {
                barScaleTry = randG.genBarScale(io);
                if(barLenTry < diskScaleTry && barScaleTry < diskScaleTry)
                {
                    break;
                }
            }
        
            
        }
        // makes sure the bar is more eccentric than the disk
        while (true)
        {
            incTry = randG.genInclination(io);
            float disk_e = 1.0f - acos(doRadCon(incTry));
            barEllipTry = randG.genBarEccen(io);
        
            if(barEllipTry > disk_e)
            {
            inclination = incTry;
                break;
            }
        }
    }
    else
    {
        surfDiskTry = randG.genSurfDisk(io);
        diskScaleTry = randG.genDiskScale(io);
        inclination = randG.genInclination(io);
    }
}

void Galaxy::writeParamsTerminal()
{
    int align = 5;
    
    std::cout << std::right << std::setw(align) << "Distance (Mpc) = ";
    std::cout << std::right << std::setw(align) <<distance << std::endl;
    std::cout << std::right << std::setw(align) << "Inclination = ";
    std::cout << std::right << std::setw(align) <<inclination << std::endl;
    std::cout << std::endl;
    std::cout << std::right << std::setw(align) << "Disk surf bright = ";
    std::cout << std::right << std::setw(align) <<surfDiskTry << std::endl;
    std::cout << std::right << std::setw(align) << "Disk cen_int = ";
    std::cout << std::right << std::setw(align) <<disk.GetCenInt() << std::endl;
    std::cout << std::right << std::setw(align) << "Disk scale (kpc) = ";
    std::cout << std::right << std::setw(align) <<disk.GetScale() << std::endl;
    std::cout << std::right << std::setw(align) << "Disk pa = ";
    std::cout << std::right << std::setw(align) <<disk.GetPa() << std::endl;
    std::cout << std::right << std::setw(align) << std::endl;
    if(barInput != barNo)
    {
        std::cout << std::right << std::setw(align) << "Bar surf bright = ";
        std::cout << std::right << std::setw(align) <<surfBarTry << std::endl;
        std::cout << std::right << std::setw(align) << "Bar cen_int = ";
        std::cout << std::right << std::setw(align) <<bar.GetCenInt() << std::endl;
        std::cout << std::right << std::setw(align) << "Bar ellip = ";
        std::cout << std::right << std::setw(align) <<bar.GetEllip() << std::endl;
        std::cout << std::right << std::setw(align) << "Bar len (kpc) = ";
        std::cout << std::right << std::setw(align) <<bar.GetLen() << std::endl;
        std::cout << std::right << std::setw(align) << "Bar pa = ";
        std::cout << std::right << std::setw(align) <<bar.GetPa() << std::endl;
        if(barInput == barFlat)
        {
            std::cout << std::right << std::setw(align) << "Bar scale (kpc) = ";
            std::cout << std::right << std::setw(align) << bar.GetScale() << std::endl;
        }
    }
}

void Galaxy::writeParamsFile(std::string output_in, float factor)
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
    
    std::ofstream ofs;
    ofs.open(output, std::ofstream::out | std::ofstream::app);
    
    int align = 20;
    
    ofs << std::right << std::setw(align) << "distance ";
    ofs << std::right << std::setw(align) << distance << std:: endl;
    ofs << std::right << std::setw(align) << "inclination ";
    ofs << std::right << std::setw(align) << inclination << std::endl;
    ofs << std::right << std::setw(align) << "cen_i_disk ";
    ofs << std::right << std::setw(align) << disk.GetCenInt() << std::endl;
    ofs << std::right << std::setw(align) << "pa_disk ";
    ofs << std::right << std::setw(align) << disk.GetPa() << std::endl;
    ofs << std::right << std::setw(align) << "disk_scale ";
    ofs << std::right << std::setw(align) << disk.GetScale() << std::endl;
    if(barInput != barNo)
    {
        ofs << std::right << std::setw(align) << "cen_i_bar ";
        ofs << std::right << std::setw(align) << bar.GetCenInt() << std::endl;
        ofs << std::right << std::setw(align) << "pa_bar ";
        ofs << std::right << std::setw(align) << bar.GetPa() << std::endl;
        ofs << std::right << std::setw(align) << "e_bar ";
        ofs << std::right << std::setw(align) << bar.GetEllip() << std::endl;
        ofs << std::right << std::setw(align) << "bar_len (pixels) ";
        ofs << std::right << std::setw(align) << bar.GetLen()*factor << std::endl;
        if(barInput == barFlat)
        {
            ofs << std::right << std::setw(align) << "bar_scale ";
            ofs << std::right << std::setw(align) << bar.GetScale() << std::endl;
        }
    }
}

void Galaxy::setDisk(CCD& ccd, UserInput& io, RandomGen& randG)
{
    disk.makeDisk(surfDiskTry,diskScaleTry,randG.genDiskPA(io),ccd.GetZeropt(),ccd.GetExpt(),ccd.GetPix());
}

void Galaxy::setBar(CCD& ccd, UserInput& io, RandomGen& randG)
{
    float barPa = randG.genBarPa(io);
    float barShape = randG.genBarShape(io);
    float zeropt = ccd.GetZeropt();
    float expt = ccd.GetExpt();
    float pix = ccd.GetPix();
    
    if(barInput != barNo)
    {
        if(barInput == barFerrer)
        {
            bar.makeBarFerrer(surfBarTry,barPa,barEllipTry,barLenTry,barShape,zeropt,expt,pix);
        }
        else if(barInput == barFlat)
        {
            bar.makeBarFlat(surfBarTry,barPa,barEllipTry,barLenTry,barShape,barScaleTry,zeropt,expt,pix);
        }
        else if(barInput == barFreeman)
        {
            bar.makeBarFreeman(surfBarTry,barPa,barEllipTry,barLenTry,barShape,zeropt,expt,pix);
        }
        else
        {
            std::cout << "Error: Wrong input for bar profile." << std::endl;
        }
    }
}

void Galaxy::genCoordsNew(int x_in, int y_in, int xcen, int ycen)
{
    const float inc_rad = doRadCon(inclination);
    const float pa_disk_rad = doRadCon(disk.GetPa());
    const float pa_bar_rad = doRadCon(bar.GetPa() + 90.0f);
    
    float shape = bar.GetShape();
    float ellip = bar.GetEllip();
    
    // cartesian coordinates in galaxy frame from given pixel values
    x = (float(x_in-xcen)*cos(pa_disk_rad) + float(y_in-ycen)*sin(pa_disk_rad))/cos(inc_rad);
    y = float(y_in-ycen)*cos(pa_disk_rad) - float(x_in-xcen)*sin(pa_disk_rad);

    // bar coordinate
    const float x_bar = (float(x_in-xcen)*cos(pa_bar_rad) + float(y_in-ycen)*sin(pa_bar_rad))/cos(inc_rad);
    const float y_bar = float(y_in-ycen)*cos(pa_bar_rad) - float(x_in-xcen)*sin(pa_bar_rad);
    if(barInput != barNo)
    {
        bar_coord = pow(pow(abs(x_bar),shape) + pow(abs(y_bar/(1.0f - ellip)),shape),1.0f/shape);
    }
}

float Galaxy::diskInten(float factor)
{
    return disk.inten(x, y, factor);
}

float Galaxy::barInten(float factor)
{
    if(barInput == barFerrer)
    {
        return bar.intenFerrer(bar_coord, factor);
    }
    else if(barInput == barFlat)
    {
        return bar.intenFlat(bar_coord, factor);
    }
    else if(barInput == barFreeman)
    {
        return bar.intenFreeman(bar_coord, factor);
    }
    else if(barInput == barNo)
    {
        return 0.0f;
    }
    else
    {
        std::cout << "Error: Wrong input for bar profile." << std::endl;
        return badInput;
    }
}

float Galaxy::getDistance() const
{
    return distance;
}

float Galaxy::getInclination() const
{
    return inclination;
}

float Galaxy::doRadCon(float angle)
{
    return angle*PI/180.0f;
}