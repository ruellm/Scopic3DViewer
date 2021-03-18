#pragma once

#include <stdio.h>
#include <vector>
#include <string>
#include <stddef.h>
#include <queue>
#include <map>
#include <cstdlib>
#include <time.h>
#include <memory>

// For QT only
#include <QOpenGLFunctions>

// GLM!!
// vec3, vec4, ivec4, mat4
#include <glm/glm.hpp>
// value_ptr
#include <glm/gtc/type_ptr.hpp>

// translate, rotate, scale, perspective
#include <glm/gtc/matrix_transform.hpp>

#define SAFE_DELETE( obj ) { if( obj ) { delete obj; obj = NULL; } }
#define SAFE_DELETE_ARRAY( obj ) { if( obj ) { delete[] obj; obj = NULL; } }
