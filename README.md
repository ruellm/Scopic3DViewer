# Scopic3DViewer

- Implemented in QT6 (6.0.1) C++
- Tested in Windows 10 environment (QT 6.0.1 MSVC2019 64bit)
- Supports toggle of grid view and coordinate axis
- Camera navigation by dragging mouse : (pan, rotate, zoom). Rotate center rotate at a center of an imaginary target computed as: position + look vector * distance. Distance is precomputed.
- Supports Ambient and Diffuse lighting as well as Diffuse (as object color) for material. No specular material.
- Cube shapes (and other shapes in the future) are cloned on render to optimized rendering. We do not create vertices and GPU buffers during addition to scene.
- Cubes/Shapes are created infront of the camera look vector * default distance (computed at approx distance = 10).
- Cube/Shape Id format is "Cube#N" where N is the unique number that describes the number sequence it is generated.
- Default light is attached to the camera position. Moving the camera moves the light.
- shaders are loaded from file, therefore 'shaders' folder should be copied to the build directory during execution.
- No scale and rotation support of objects. size of cube is 10x10 (laid out in -5 to 5 in vertices).

## Important notes
shaders are loaded from file, therefore the 'shaders' folder should be copied to the build directory when running from QT Creator

example, on windows QT generate the folder name *build-ScopicTestQTQL-Desktop_Qt_6_0_1_MSVC2019_64bit-Debug*, copy the 'shaders' folder inside the build directory as such

***build-ScopicTestQTQL-Desktop_Qt_6_0_1_MSVC2019_64bit-Debug/shaders***

However, when running as stand-alone executable, the 'shaders' folder should be in the same level as the exe file.

--Auto copy of the folders to build directory is in progress.--

## Precompiled
A precompiled binary is available here:
(Please request for access)

https://tinyurl.com/sefdzupb
