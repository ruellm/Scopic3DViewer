#include "meshbuilder.h"
#include "common.h"

static QOpenGLVertexArrayObject*   f_cubeVAO = 0;
static QOpenGLBuffer*              f_cubeVBO = 0;
static int                         f_cubeVertCount = 0;

namespace builder {

void BuildCube()
{
    QOpenGLFunctions *glFuncs = QOpenGLContext::currentContext()->functions();

    SAFE_DELETE(f_cubeVAO);

    float buffer[] = {
        // position             normal
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    f_cubeVAO = new QOpenGLVertexArrayObject;
    if (f_cubeVAO->create())
        f_cubeVAO->bind();

    f_cubeVBO = new QOpenGLBuffer;
    f_cubeVBO->create();
    f_cubeVBO->bind();

    // Give our vertices to OpenGL.
    glFuncs->glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);

    // position attribute
    glFuncs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glFuncs->glEnableVertexAttribArray(0);

    // normal attribute
    glFuncs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glFuncs->glEnableVertexAttribArray(1);

    f_cubeVertCount = 36;
    f_cubeVAO->release();

}

void LoadPrefab(){

    // Create the cube buffers
    BuildCube();

    //.. Build other shapes
}

Mesh CloneCubeMesh()
{
    return Mesh(f_cubeVAO, f_cubeVBO, f_cubeVertCount, true);
}

void Cleanup()
{
    f_cubeVAO->destroy();
    f_cubeVBO->destroy();

    SAFE_DELETE(f_cubeVAO);
    SAFE_DELETE(f_cubeVBO);
}

QOpenGLVertexArrayObject* GetCubeMeshVao()
{
    return f_cubeVAO;
}

Mesh CreteAxis(float length) {

    QOpenGLFunctions *glFuncs = QOpenGLContext::currentContext()->functions();

    QOpenGLVertexArrayObject* vao = new QOpenGLVertexArrayObject;
    if (vao->create())
        vao->bind();

    QOpenGLBuffer* vbo = new QOpenGLBuffer;
    vbo->create();
    vbo->bind();

    float size = 6 * 6;

    float buffer[] = {
        // X axis - Red
        0, 0, 0,            1, 0, 0,
        length, 0, 0,       1, 0, 0,

        // Y axis - Green
        0, 0, 0,            0, 1, 0,
        0, length, 0,       0, 1, 0,

        // Z axis - Blue
        0, 0, 0,           0, 0, 1,
        0, 0, length,      0, 0, 1,
    };

    glFuncs->glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), buffer, GL_STATIC_DRAW);
    glFuncs->glVertexAttribPointer(
                0,
                3,
                GL_FLOAT,
                GL_FALSE,
                6 * sizeof(float),
                (void*)0
                );

    glFuncs->glEnableVertexAttribArray(0);

    glFuncs->glVertexAttribPointer(
                1,
                3,
                GL_FLOAT,
                GL_FALSE,
                6 * sizeof(float),
                (void*)(3 * sizeof(float))
                );


    glFuncs->glEnableVertexAttribArray(1);

    glFuncs->glBindBuffer(GL_ARRAY_BUFFER, 0);

    return Mesh(std::move(vao), std::move(vbo), 6);
}

Mesh CreateGrid(int width, int height)
{
    int horiz_cnt = width + 1;
    int vert_cnt = height + 1;
    float cellspace = 1;// 0.5f;
    float WIDE = cellspace * (float)width;
    float HEIGHT = cellspace * (float)height;

    int vertCount = (horiz_cnt * 2) + (vert_cnt * 2);

    QOpenGLVertexArrayObject* vao = new QOpenGLVertexArrayObject;
    if (vao->create())
        vao->bind();

    QOpenGLBuffer* vbo = new QOpenGLBuffer;
    vbo->create();
    vbo->bind();

    unsigned long size = (horiz_cnt * 6) + (vert_cnt * 6);
    float* buffer = new float[size];

    float xoffset = -WIDE / 2.0f;
    float yoffset = WIDE / 2.0f;
    int index = 0;

    for (int x = 0; x < horiz_cnt; x++) {

        buffer[index++] = xoffset;
        buffer[index++] = 0;
        buffer[index++] = yoffset;

        buffer[index++] = xoffset + WIDE;
        buffer[index++] = 0;
        buffer[index++] = yoffset;

        yoffset -= cellspace;
    }

    xoffset = -WIDE / 2;
    yoffset = WIDE / 2;
    for (int x = 0; x < vert_cnt; x++) {
        buffer[index++] = xoffset;
        buffer[index++] = 0;
        buffer[index++] = yoffset;

        buffer[index++] = xoffset;
        buffer[index++] = 0;
        buffer[index++] = yoffset - HEIGHT;

        xoffset += cellspace;
    }

    QOpenGLFunctions *glFuncs = QOpenGLContext::currentContext()->functions();

    glFuncs->glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), buffer, GL_STATIC_DRAW);
    glFuncs->glVertexAttribPointer(
                0,
                3,
                GL_FLOAT,
                GL_FALSE,
                0,
                (void*)0
                );

    glFuncs->glEnableVertexAttribArray(0);

    glFuncs->glBindBuffer(GL_ARRAY_BUFFER, 0);
    delete[] buffer;

    return Mesh(std::move(vao), std::move(vbo), vertCount);
}

}
