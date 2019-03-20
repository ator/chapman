# Chapman
(Tracy) Chapman is a hobby project (command line) raytracer written in C++, for Windows and Linux.

The ray tracing algorithm is derived from several online sources and some trial-and-error to make it look "nice". It's probably not the way it "should" be done. :)

## Current status
* Renders a scene built programatically
* Supports spheres and planes
* Supports ambient, directional, and point lights
* Supports reflection but not refraction
* Saves image as PPM file
* Multithreaded (will use as many threads as given by std::thread::hardware_concurrency(), or 1 if unknown)

## TODO/Wish list:
* Other object types (cylinders, cones, triangles, cubes, etc)
* Object combination (union, intersection, etc)
* Directional lights (ie point lights with a shading cone)
* Surface lights
* Scene file loading (preferably some common format)
* Material texture images
* Material bump maps
* Procedural materials
* Camera lense
* Other image output format(s)
* Distributed rendering (master/slave)
* Animation
* Motion blur
