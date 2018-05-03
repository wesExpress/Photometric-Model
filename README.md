# Photometric-Model

Measuring galaxy properties is an important part of studying galaxy evolution and testing our current models. For instance, the length of a stellar bar is useful for determining things like bar strength and relative pattern speed; both of which can tell us about the underlying mass distribution of a galaxy. In a perfect world, we can measure galaxy properties with no error. Sadly, we run into various issues that complicate things greatly. 

In order to mitigate these issues, this code generates mock galaxy images in order to test any measuring routines and algorithms being used. By knowing the properties a priori and then measuring these said properties, once can get a grasp of how well the parameters are being measured. Once can also determine if the results are being biased in a certain way: e.g. short bars are always over predicted, or bad seeing always hides bars smaller than a certain size.

Currently, this code generates a galaxy with a distance in Mpc and inclination in degrees. It then adds a disk and bar component, both with various parameters. The disk and bar are coupled so that the parameters are always physically meaningful. The code is open so that more components can be added later (i.e. spiral arms). Next, read and sky noise are added to mimic observing. Again, the code is open to future noise additions. Finally, we run through a mock CCD of specified pixel size and generate the on-sky intensity profile of the galaxy.

Inputs
------
Code takes a file called "inputs.txt" currently that contains the min and max values for the parameter distributions. For some reason, need to leave first line blank or have '//', since std::getline skips this line for some reason. The order of parameters is currently:
+ distance (Mpc)
+ inclination (degrees)
+ disk central surface brightness (mag/arcsec^2)
+ disk scale length (kpc)
+ disk position angle (degrees)
+ bar central surface brightness (mag/arcsec^2)
+ bar eccentricity
+ bar length (kpc)
+ bar shape (*c* parameter in Freeman bar profile)
+ bar scale length (*r_s* parameter in Flat bar profile)

Disk
----
+ central surface brightness --> turned into ADU counts
+ scale length --> in kpc
+ position angle --> in degrees

Currently, only a pure Sèrsic profile is assumed.

Bar
---
+ central surface brightness --> turned into ADU counts
+ position angle --> in degrees
+ ellipticity
+ length --> in kpc
+ shape --> value *c* in Freeman profile
+ scale length --> value *r_s* in Flat profile

Currently has the option of a Freeman or Flat profile.

Noise
-----
+ sky
+ read

COUPLING OF PARAMETERS
----------------------

+ Disk is forced to be fainter than the bar, with a maximum differce of 1 mag/arcsec^2
+ Bar length is forced to be shorter than the disk scale length
+ Bar ellipticity is forced to be larger than the disk ellipticity (disk inclination)

TO BE ADDED IN FUTURE
---------------------

+ Seeing effects --> convolve image with either Gaussian or Moffat profile
+ 'Patchy' Disk 
+ Spiral arms --> would be nice to add spiral arms into the image
