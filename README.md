# Scopic3DViewer

- Implemented in QT6 (6.0.1) C++
- Tested in Windows 10 environment (QT 6.0.1 MSVC2019 64bit)
- Supports toggle of grid view and coordinate axis
- Camera navigation by dragging mouse : (pan, rotate, zoom). Rotate center rotate at a center of an imaginary target computed as: position + look vector * distance. Distance is precomputed.
- Only supports Ambient and Diffuse lighting as well as Diffuse (as object color) for material.
- Cube shapes (and other shapes in the future) are cloned on render to optimized rendering. We do not create vertices and GPU buffers during addition to scene.
- Default light is attached to the camera position. Moving the camera moves the light.
- shaders are loaded from file, therefore 'shaders' folder should be copied to the build directory during execution.
- No scale and rotation support of objects. size of cube is 10x10 (laid out in -5 to 5 in vertices).

## Important notes
shaders are loaded from file, therefore the 'shaders' folder should be copied to the build directory when running from QT Creator

example, on windows QT generate the folder name *build-ScopicTestQTQL-Desktop_Qt_6_0_1_MSVC2019_64bit-Debug*, copy the 'shaders' folder inside the build directory as such

***build-ScopicTestQTQL-Desktop_Qt_6_0_1_MSVC2019_64bit-Debug/shaders***

--Auto copy of the folders to build directory is in progress.--
