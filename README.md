# GSG-Framework
Engine (C++ and SDL) with 'common' purpose framework for the usage of Grand Strategy Game (GSG) development

Licensed under - Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)

# Building

To build this project, take the following steps. Make sure you have installed `cmake`, the GNU compiler collection or an alternative C++ compiler, and have the `SDL2` and `SDL2_image` libraries installed where your compiler can find them.

1. Clone the repository to a local directory.

       git clone https://github.com/ImperatorAugustus/GSG-Framework.git <directory>
       cd <directory>

2. Create a `build` directory and move over there.

       mkdir build
       cd build

3. Setup the cmake targets and build.

       cmake ..
       cmake --build .
