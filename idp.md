# computer vision

Computer vision is an interdisciplinary scientific field that deals with how computers can gain high-level understanding from digital images or videos. From the perspective of engineering, it seeks to understand and automate tasks that the human visual system can do.

## Digital images :
A digital image is an image composed of picture elements, also known as pixels, each with finite, discrete quantities of numeric representation for its intensity or gray level that is an output from its two-dimensional functions fed as input by its spatial coordinates denoted with x, y on the x-axis and y-axis, respectively. Depending on whether the image resolution is fixed, it may be of vector or raster type. By itself, the term "digital image" usually refers to raster images or bitmapped images

characterstics of images:
 1. number of pixels
 2. depth of pixel
 3. number of channels

### number of pixels:
Each image is divided into several pixels and each pixel is smallest part which we are going to deal with it 

eg: 1280x1024 ,1920x1080 etc..

### depth of pixel:
Each pixel information is stored as integers or characters with information of intensity the size allocated to that integer or character is called as depth of image

eg: 1-bitcolor,2-bit colur,3bit-colur etc..

### number of channels:
it is number of diiferent primary colurs you have choosen for the image

eg: greyscale:1-channel,rgb:3-channels,etc..

please see this beautiful wikepedia page for betterunderstanding on 
[colordepth](https://en.wikipedia.org/wiki/Color_depth)

## Few cv libraries:
when comming to computer vision there many beautiful libraries to do all the baic stuff of image processing like:

 1. Opencv
 2. Pillow
 3. skikit image
 4. simplecv

few paid ones also available like cloud vision api etc..

for this tutorial we will be going and dealing with opencv module 

## opencv:

opencv is opensource source computervision library written in c++ majorly and later binded to many languages like python java etc..

the main advantage of opencv it is constantly updatd and many scientific papers are added 

![alt text](github.png "githubpage")

they are constantly updated with lot of contributors 

the main disadvantage of opencv is it default to 8bit per channel depth to read and write images which we are mostly working with but in the near future we are moving 10-bit per channel which is not supported natively in github for reading those images

# Image processing:

so know we basically understood how images are read and now on we refer image as a matrix of numbers and now letus see some basic filters and stuff

## Grayscale:
Mostly all image processing is done with greyscale images as we are mostly intrested in intensities than colours of them so we rather deal with greyscale images rather than very complex colour images

## filters :
filters are something which removes few information or few refinemnet towards our goal 

few eg: gaussian filter,sobel filter,bilateralfilter etc..

### How :
basically all filters have specific kernals with specific features and those keranls are convuluved with image matrix to get the resultant image

***Let us see few kernals :***
 1. Gaussian kernal:

      Gaussian kernal is a keranl which basically blurs the image using
      gaussian noice it is very useful for smoothing the image and removing few noicess in images as gausssian noicess supress those noicess 

      gaussian kernal is given by:

    ![alt text](gaussian.png "gaussianpage")

    where size of kernal is (2k+1)x(2k+1)
2. Bilateral kernal:

      The issue with gaussian kernal is it basically smoothens everything so that it ripoff few edges so we need a filter which preserves the edges and also does smoothening but how ?

      The solution for that is it checks for difference in the intensity of the point and the it's neighbhouring point and then based on that it decides it's weightage 
      ![alt text](bilateral.png "bilateralpage")

3. Sobel kernal:

      The sobel kernal is the most important kernal in the edge detection and this kernal is used to find gradient along an axis say x-axis and y-axis and find the angle of gradient flow at a particular pixel which gives a gradient mat and angle matrix 

      sow how gradient is taken it is taken by a kernal called sobel kernal and it is basically vary's as the size of kernal varies let's see 3x3 kernal of sobel 

      ![alt text](sobel.png "sobelpage")

There are many more kernals which we would see in the following tutorial

***Convulution of matrix:***

convulution of matrix with a kernal matrix is very similar to the convution of two functions following image easily depicts and can give you a intiative of how convulution is done:

![alt text](convolution.png "convulutionpage")

## Edge detection algorithms:
***Using sobel filter:***

Using sobel filter we get a gradient map wich is and drewing lines perpenducular to the gradient map give you the edge detection's which is very well used for edge detection

***Using laplacian algorithm***

Insted of using two kernals the laplacian directly finds the second derivative by using laplacive kernal 

***Using canny edge detection:***

This is a very advanced algorithm to find the edge detection It basically uses the sobel filtering and rectifies it's issues

**The main issue of sobel filter** is the edges are of varing thickness and the intensity of the image is very less than regular grey scale 

These two issues are solved by 3 steps in canny algorithm

1. Non-max supression

     This step aims at reducing the duplicate merging pixels along the edges to make them uneven. For each pixel find two neighbors in the positive and negative gradient directions, supposing that each neighbor occupies the angle of pi /4, and 0 is the direction straight to the right. If the magnitude of the current pixel is greater than the magnitude of the neighbors, nothing changes, otherwise, the magnitude of the current pixel is set to zero.

2. Double Thresholding :

     This is basically sets two threshold one minimum and other is maximum the pixels with intensities less than mimnium are supressed and the pixel which are above max threshold are marked as white and pixel which are in between are marked as weak 

3. Edge detection by hyteresis :

   This basically checks neighbhourhood of weak pixels to check strong pixels if any strong pixel is found  it is converted to strong 
   at last after several iterations it marks all left over weak as blacks 
   
By doing this It overcomes the two problems of sobel detection 

# Contours: 
Contours can be explained simply as a curve joining all the continuous points (along the boundary), having same color or intensity. The contours are a useful tool for shape analysis and object detection and recognition.

Contours are marked based on difference in the intenisinties of neighbhourhood pixels 

Contours are has many uses in potraits and image down sampling .
Contours are found using many methods and approximations 
eg:

1. approx simple : Finding number of points required only
2. aprrox none: Doing complete 
etc..


# End project:

Creating a gui tool using different small opencv functions

the opencv functions used here are:

1. simple opening 
2. Laplacian edge detection using ddepth =CV16S( Using 16 bit to avoid overflow)
3. Canny algorithm using 0.8 as max and 0.2 as min threshold
4. Number plate detection by finding rectangle contour and passing it to pytesseract to detect the numbers 

I will go through this 
[idp.py]("./home/chandrahaas/Python/idp.py")

