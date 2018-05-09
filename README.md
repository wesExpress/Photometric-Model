# Photometric-Model

Measuring galaxy properties is an important part of studying galaxy evolution and testing our current models. For instance, the length of a stellar bar is useful for determining things like bar strength and relative pattern speed; both of which can tell us about the underlying mass distribution of a galaxy. In a perfect world, we can measure galaxy properties with no error. Sadly, we run into various issues that complicate things greatly. 

In order to mitigate these issues, this code generates mock galaxy images in order to test any measuring routines and algorithms being used. By knowing the properties a priori and then measuring these said properties, once can get a grasp of how well the parameters are being measured. Once can also determine if the results are being biased in a certain way: e.g. short bars are always over predicted, or bad seeing always hides bars smaller than a certain size.

Currently, this code generates a galaxy with a distance in Mpc and inclination in degrees. It then adds a disk and bar component, both with various parameters. The disk and bar are coupled so that the parameters are always physically meaningful. The code is open so that more components can be added later (i.e. spiral arms). Next, read and sky noise are added to mimic observing. Again, the code is open to future noise additions. Finally, we run through a mock CCD of specified pixel size and generate the on-sky intensity profile of the galaxy.

Inputs
------
Code takes a file called "inputs.txt" currently that contains the min (second column) and max (third column) values for the parameter (first column) distributions. Need to leave first line blank or have '//', since std::getline skips this line for some reason. The parameters don't need to be in any order, as the code searches for each parameter needed based on a string, the first column of the input file. For disk_profile and bar_profile, only the second column needs a number, the third can be anything. **For disk_profile**, 1 = sersic profile. **For bar_profile**, 1 = Ferrer, 2 = Flat and 3 = Freeman. Likewise, the seeing parameters (seeing, fwhm, beta) only need a number in the second column. **If seeing is 1**, then the program convolves the CCD intensity with a Moffat profile given the next two parameters (FWHM and beta). **If patchy_disk is 1**, then the program adds some 'holes' to the disk in order to make it less perfect.

The current accepted parameters are (with the required string name):
+ **output** --> name output file
+ **output_conv** --> name of output file with seeing convolution
+ **disk_profile** --> 1 for sersic
+ **bar_profile** --> 1 for Ferrer, 2 for flat, 3 for Freeman
+ **seeing** --> 1 for seeing convolution, 0 to ignore
+ **patchy_disk** --> 1 for patchy disk, 0 to ignore
+ **distance** --> must be in Mpc
+ **inclination** --> must be in degrees
+ **surf_disk** --> disk central surface brightness (must be in mag/arcsec^2)
+ **disk_scale** --> disk scale length (must be in kpc)
+ **disk_pa** --> disk position angle (must be in degrees)
+ **surf_bar** --> bar central surface brightness (must be in mag/arcsec^2)
+ **bar_ecc** --> bar eccentricity
+ **bar_len** --> bar length (must be in kpc)
+ **bar_shape** --> bar shape (*c* parameter in bar coordinate equation)
+ **bar_scale** --> bar scale length (*r_s* parameter in Flat bar profile)
+ **fwhm** --> fwhm of seeing of image (must be in pixels)
+ **beta** --> shape of Moffat profile

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
+ shape --> *c* parameter in bar coordinate equation
+ scale length --> value *r_s* in Flat profile

Currently has the option of a Ferrer, Flat or Freeman profile.

CCD
---
+ nx --> number of x pixels
+ ny --> number of y pixels
+ pixscale --> plate scale of CCD (arcsec/pixel)
+ exptime --> exposure time of image in seconds
+ zeropoint --> photometric zeropoint of image (in magnitudes)

Noise
-----
+ sky
+ read
+ patchy disk --> random (x,y) positions of random radii with random light percentage decreases to mimic a patchy disk

COUPLING OF PARAMETERS
----------------------
+ Disk is forced to be fainter than the bar, with a maximum differce of 1 mag/arcsec^2
+ Bar length is forced to be shorter than the disk scale length
+ Bar ellipticity is forced to be larger than the disk ellipticity (disk inclination)

TO BE ADDED IN FUTURE
---------------------
+ Spiral arms --> would be nice to add spiral arms into the image
