# SCLT: Spectral Clara Lux Tracer

[![Build Status](https://travis-ci.org/chicio/Spectral-Clara-Lux-Tracer.svg?branch=master&aa)](https://travis-ci.org/chicio/Spectral-Clara-Lux-Tracer)
[![Build status](https://ci.appveyor.com/api/projects/status/5ngd4y0qx5n8ygnm?svg=true)](https://ci.appveyor.com/project/chicio/spectral-clara-lux-tracer)
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/chicio/Spectral-Clara-Lux-Tracer/master/LICENSE.md)
![Supported platform] (https://img.shields.io/badge/platforms-iOS%20%7C%20OS%20X%20%7C%20Windows%20%7C%20Linux-orange.svg)

Physically based ray tracer with multiple shading models support and CRI evaluation develop for my master degree thesis at <a href="https://www.disco.unimib.it">University Milano-Bicocca</a> - <a href="http://www.ivl.disco.unimib.it">Imaging and Vision Laboratory</a>.

<p align="center">
<img width="350" height="350" src="https://github.com/chicio/Spectral-Clara-Lux-Tracer/blob/master/Images/Readme/logo.jpg"
</p>

<a href="https://drive.google.com/open?id=0BxeVnHLvT8-7dkxQRjV6M29TeUk">Link to my thesis</a>.
***
###Introduction

Physically Based Rendering (PBR) aims at treating light the way it works in the real world, using physically correct lighting models and materials to achieve a new level of realism in rendering. 
PBR is extensively used with different rendering techniques. In particular, it is often used in conjunction with ray tracing. 
Ray tracing is a rendering technique that simulates the natural flow of light in the environment by tracing all its path, and calculating its effect on the various surfaces that it could encounter. In fact, ray tracing is a global illumination rendering technique: it takes into account direct light coming from a source on a surface, and also indirect light that it is reflected or transmitted by other objects in a scene.
The base of all global illumination algorithms is the rendering equation, described by Kajiya in 1986 [1]:

![Rendering equation](https://raw.githubusercontent.com/chicio/Spectral-Clara-Lux-Tracer/master/Images/Readme/rendere-equation.png)

PBR lighting models are a physically correct representation of the first term inside the integral, called Bidirectional Reflectance Distribution Function (Pharr et al., 2010 [2]).
Another interesting field of study strictly correlated to PBR is colorimetry. In particular, as a consequence of the fact that light is a subset of the entire electromagnetic spectrum, color in rendering can be computed using spectral distribution data, the tristimulus values and the correlated CIE XYZ color space (Kang, 2007 [3]). This color space was created by the main authority on color and illumination: International Commission on Illumination (CIE).
The formulas that defines the tristimulus values are (Kang, 2007 [3]):

![tristimulus x](https://raw.githubusercontent.com/chicio/Spectral-Clara-Lux-Tracer/master/Images/Readme/tristimulus-x.png)

![tristimulus y](https://raw.githubusercontent.com/chicio/Spectral-Clara-Lux-Tracer/master/Images/Readme/tristimulus-y.png)

![tristimulus z](https://raw.githubusercontent.com/chicio/Spectral-Clara-Lux-Tracer/master/Images/Readme/tristimulus-z.png)

In this way it is possible to render scenes with high color fidelity, that could show physical phenomenons like metamerism, impossible to obtain with standard RGB data.
As a consequence of using spectral power distribution for light and objects in a scene, it is possible also to evaluate how a light source accurately render all frequency of its color spectrum in comparison with an ideal/natural light source using the Color Rendering Index [4]. The lower the CRI, the less accurately colors will be reproduced.

***
###Overview

Spectrum Clara Lux Tracer (SCLT) is new multi-platform physically based ray tracing rendering engine. It has been created to explore some of the possibilities of PBR and colorimetry in computer graphics rendering.
The main features of SCLT are:

- ability to render scenes using PBR and empirical lighting models. In this way it is possible to compare physically base scenes with standard empirical light scenes.  In particular, for PBR, SCLT implements the following models: Lambertian, Oren-Nayar [5], Torrance-Sparrow [6], specular reflection, specular transmission and measured BRDF [7]. This models are derived from their implementation in PBRT [8].

- support for different ray tracing technique:

	* Whitted ray tracing, created by Turner Whitted in 1979 [9], a model where different kind of ray: reflection rays for mirror surfaces, refracted rays for transmissive surfaces (e.g. glass) and shadow rays. This model is implemented using PBR and empirical models;

	* Path Tracing, a model presented by Kajiya in 1986 [1]. This model uses Monte Carlo integration techniques to find a numerical solution to the rendering equation. This model is implemented using only PBR models;

- color calculation using spectral data and the CIE XYZ color space in PBR scenes, to achieve high color fidelity;

- support for the calculation of the CRI for the light source of a PBR scene, using two main methods: Test samples method [10] and R96a [11].

- Cross-platform support: SCLT is a native application that could be executed on any Apple iPad devices starting from iPad 2 with iOS 9.0, any Apple computer with OS X El Captain 10.11.0 and any PC with Windows 10.

The ability to render PBR scenes using spectral data, and the CRI calculation support, let SCLT be a perfect tool for industrial light design and production. In fact, with SCLT light designer could test the ability of new light product to reveal color, giving a numerical precise quantification with CRI. The support to multiple devices and operating system gives to the user the freedom to choose the preferred platform without any restriction.

***
###Usage

SCLT could run on:

- Apple iOS 9.0 (and above) and OS X El Capitan 10.11 operating system with a native user inteface
- Windows 10 as a native UWP application
- Linux as a command line application using CMake (compatible/tested also with OS X)
 
For Apple version, it is possible to create a build using the most recent version of XCode (> 7.0).
For Microsoft Windows, it is possible to create a build using Visual Studio 2015.
For Linux command line application, the CMake version required is 2.8.

***
###Scenes

**Scene 1**
- Ray tracing technique: Whitted 
- BRDFs: Lambertian, Oren-Nayar, Torrance-Sparrow, Specular reflection and transmission, measured BRDF
- Illuminant: D65

<p align="center">
<img width="512" height="512" src="https://raw.githubusercontent.com/chicio/Spectral-Clara-Lux-Tracer/master/Images/03%20-%20spectral-whitted-scene3-D65-AA4X.jpg"/>
</p>

**Scene 2**
- Ray tracing technique: Whitted 
- BRDFs: Lambertian, Oren-Nayar, Torrance-Sparrow, Specular reflection and transmission, measured BRDF
- Illuminant: FL4

<p align="center">
<img width="512" height="512" src="https://raw.githubusercontent.com/chicio/Spectral-Clara-Lux-Tracer/master/Images/04%20-%20spectral-whitted-scene3-FL4-AA4X.jpg"/>
</p>

**Scene 3**
- Ray tracing technique: Whitted 
- BRDFs: Lambertian, Oren-Nayar, Torrance-Sparrow, Specular reflection and transmission, measured BRDF
- Illuminant: FL9

<p align="center">
<img width="512" height="512" src="https://raw.githubusercontent.com/chicio/Spectral-Clara-Lux-Tracer/master/Images/05%20-%20spectral-whitted-scene3-FL9-AA4X.jpg"/>
</p>

**Scene 4**
- Ray tracing technique: Whitted 
- BRDFs: Lambertian, Oren-Nayar, Torrance-Sparrow, Specular reflection and transmission, measured BRDF
- Illuminant: A

<p align="center">
<img width="512" height="512" src="https://raw.githubusercontent.com/chicio/Spectral-Clara-Lux-Tracer/master/Images/06%20-%20spectral-whitted-scene3-A-AA4X.jpg"/>
</p>

**Scene 5**
- Ray tracing technique: Path Tracing
	- samples per pixel: 20000
- BRDFs: Lambertian, Oren-Nayar, Specular reflection and transmission
- Illuminant: D65

<p align="center">
<img width="512" height="512" src="https://github.com/chicio/Spectral-Clara-Lux-Tracer/blob/master/Images/16%20-%20spectral-path-scene5-D65-20000sample-AA2X.jpg"/>
</p>

**Scene 6**
- Ray tracing technique: Path Tracing
	- samples per pixel: 40000
- BRDFs: Lambertian, Oren-Nayar, Torrance-Sparrow, Specular reflection and transmission, measured BRDF
- Illuminant: D65

<p align="center">
<img width="512" height="512" src="https://github.com/chicio/Spectral-Clara-Lux-Tracer/blob/master/Images/19a%20-%20spectral-path-scene6-D65-40000sample-AA2X.png"/>
</p>

**Scene 7**
- Ray tracing technique: Path Tracing
	- samples per pixel: 40000
- BRDFs: Lambertian, Oren-Nayar, Torrance-Sparrow, Specular reflection and transmission, measured BRDF
- Illuminant: FL4

<p align="center">
<img width="512" height="512" src="https://raw.githubusercontent.com/chicio/Spectral-Clara-Lux-Tracer/master/Images/18a%20-%20spectral-path-scene7-FL4-40000sample-AA2X.png"/>
</p>

**Scene 8**
- Ray tracing technique: Path Tracing
	- samples per pixel: 40000
	- low light brightness
- BRDFs: Lambertian, Oren-Nayar, Torrance-Sparrow, Specular reflection and transmission, measured BRDF
- Illuminant: D65

<p align="center">
<img width="512" height="512" src="https://raw.githubusercontent.com/chicio/Spectral-Clara-Lux-Tracer/master/Images/20a%20-%20spectral-path-scene8-D65-40000sample-AA2X.png"
</p>

**Scene 9**
- Ray tracing technique: Path Tracing
	- samples per pixel: 40000
- BRDFs: Lambertian, Torrance-Sparrow, Specular reflection and transmission, measured BRDF
- Illuminant: FL9

<p align="center">
<img width="512" height="512" src="https://raw.githubusercontent.com/chicio/Spectral-Clara-Lux-Tracer/master/Images/21a%20-%20spectral-path-scene9-FL9-40000sample-AA2X.png"/>
</p>

**Scene 10**
- Ray tracing technique: Whitted
- BRDFs: Lambertian
- Illuminant: D65
- Polygonal mesh

<p align="center">
<img width="512" height="512" src="https://raw.githubusercontent.com/chicio/Spectral-Clara-Lux-Tracer/master/Images/22%20-%20spectral-whitted-scene11-D65-dragon-AA2X.png"/>
</p>

**Scene 11**
- Ray tracing technique: Path Tracing
    - samples per pixel: 10000
- BRDFs: Lambertian
- Illuminant: D65
- Polygonal mesh

<p align="center">
<img width="512" height="512" src="https://raw.githubusercontent.com/chicio/Spectral-Clara-Lux-Tracer/master/Images/27%20-%20spectral-path-scene12-D65-10000sample-AA2X.png"/>
</p>

**Scene 12**
- Ray tracing technique: Path Tracing
    - samples per pixel: 10000
- BRDFs: Torrance Sparrow
- Illuminant: D65
- Polygonal mesh

<p align="center">
<img width="512" height="512" src="https://raw.githubusercontent.com/chicio/Spectral-Clara-Lux-Tracer/master/Images/28%20-%20spectral-path-scene12-D65-10000sample-TorranceSparrow-AA2X.png"/>
</p>

**Scene 13**
- Ray tracing technique: Path Tracing
    - samples per pixel: 20000
- BRDFs: Specular reflection and transmission
- Illuminant: D65
- Polygonal mesh

<p align="center">
<img width="512" height="512" src="https://github.com/chicio/Spectral-Clara-Lux-Tracer/blob/master/Images/29%20-%20spectral-path-scene12-D65-20000sample-Glass-AA2X.png?a"/>
</p>

***

###References

[1]  J. T. Kajiya, "The Rendering Equation," in SIGGRAPH '86, Dallas, 1986, pp. 143-150.

[2]  M. Pharr and G. Humphreys, "Color and Radiometry," in Physically based rendering: from theory to implementation, 2nd ed., Burlington, Massachusetts: Morgan Kaufmann, 2010, ch. 5, pp. 262-297.

[3]  H. R. Kang, "Tristimulus specification," in Computation color technology, Bellingham, Washington: SPIE Publications, 2006, ch. 1, pp. 1-16.

[4]  Lowel-Light Mfg., "Color Temperature & Color Rendering Index DeMystified," The Tiffen Company, 5 August 2014. [Online]. Available: http://lowel.tiffen.com/edu/color_temperature_and_rendering_demystified.html. [Accessed 8 June 2016].

[5]  M. Oren and K. S. Nayar, "Generalization of Lambert’s Reflectance Model," in SIGGRAPH '94, Orlando, 1994, pp. 239-246.

[6]  K. E. Torrance and E. M. Sparrow, "Theory for off-specular reflection from roughened surfaces," JOSA, vol. 57, no. 9, pp. 1105-1114, 1967. 

[7]  S. R. Marschner, "Inverse rendering for computer graphics," PhD Thesis, Cornell Univ., Dept. Computer Graphics, New York, 1998.

[8]  M. Pharr and G. Humphreys, “Reflection models,” in Physically based rendering: from theory to implementation, 2nd ed., Burlington, Morgan Kaufmann, 2010, ch. 8, pp. 423-496.

[9]  T. J. Whitted, “An improved illumination model for shaded display,” Communications of the ACM, vol. 23, no. 6, pp. 343-349, 6 June 1980.

[10] CIE Commission Internationale de l'Eclairage, "Method of Measuring and Specifying Colour Rendering Properties of Light Sources," CIE Commission Internationale de l'Eclairage, CIE, Vienna, 1995.

[11] P. Bodrogi, "Colour rendering: past, present(2004), and future," in CIE Symposium '04 on "LED Light Sources: Physical Measurement and Visual and Photobiological Assessment, Tokyo, 2010, pp. 10-12.


