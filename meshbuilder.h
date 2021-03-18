#pragma once

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include "mesh.h"

namespace builder {

    void LoadPrefab();

    Mesh CloneCubeMesh();

    Mesh CreteAxis(float length);

    Mesh CreateGrid(int width, int height);

    void Cleanup();

    QOpenGLVertexArrayObject* GetCubeMeshVao();
}

