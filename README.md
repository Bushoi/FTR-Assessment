# FTR-Assessment

Here's my submission for the FTR coding assessment. It comprises of two 
applications, [DataEntry](DataEntry/) and [UnitTests](UnitTests/).

Both have been developed on Linux using GCC v9.2.1. The code is written to c++11 language standard and make minimal use of additional libraries. Use of the c++ Threading library required [Posix threads](https://en.wikipedia.org/wiki/POSIX_Threads) (pthread) to be included in the build. [Google Test](https://en.wikipedia.org/wiki/Google_Test) is also used to provide the unit-testing framework.

## Building

Each application has been supplied with a **CMakeLists.txt**. Which may need to be modifed to suit your build environment. Both applications make use of the C++11 Thread support library. When using GCC this requires the pthread library to be included. Both **CMakeLists.txt** files will need to be modified to include any libraries that your tooldchain requires you to include.

The UnitTests application also requires the gtest library. The **CMakeLists.txt** file for UnitTests will need to be modified so that paths to the Google Test include and library directories are set appropriately for your environment.

A complimentary build directory will need to be created when using CMake to build the applications.

For example
```
mkdir DataEntry-Build
cd DataEntry-Build
cmake ../DataEntry-Build
cmake --build .
```
