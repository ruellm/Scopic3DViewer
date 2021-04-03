# Scopic3DViewer

- Implemented in QT6 (6.0.1) C++
- Tested in Windows 10 environment (QT 6.0.1 MSVC2019 64bit)
- Supports toggle of grid view and coordinate axis
- Camera navigation by dragging mouse : (pan, rotate, zoom). Rotate center rotate at a center of an imaginary target computed as: position + look vector * distance. Distance is precomputed.
- Uses camera axis handle (look, up, right) vectors to manipulate camera position.
- Supports Ambient and Diffuse lighting as well as Diffuse (as object color) for material. No specular material.
- Cube shapes (and other shapes in the future) are cloned on render to optimized rendering. We do not create vertices and GPU buffers during addition to scene.
- Cubes/Shapes are created infront of the camera look vector * default distance (computed at approx distance = 10).
- Cube/Shape Id format is "Cube#N" where N is the unique number that describes the number sequence it is generated.
- Remove/Delete of Shape is not supported in the GUI but already supported in the SceneManager class. Supporting this feature will be minimal change.
- Default light is attached to the camera position. Moving the camera moves the light.
- shaders are loaded from file, therefore 'shaders' folder should be copied to the build directory during execution.
- No scale and rotation support of objects. Size of cube is 10x10 (laid out in -5 to 5 in vertices).

## Precompiled
A precompiled binary is available here:
(Please request for access)

https://tinyurl.com/sefdzupb
