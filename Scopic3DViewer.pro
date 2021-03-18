QT       += core gui widgets opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    glwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    camera.cpp \
    intersect.cpp \
    mesh.cpp \
    meshbuilder.cpp \
    renderer.cpp \
    scenemanager.cpp \
    shape.cpp

HEADERS += \
    material.h \
    glwidget.h \
    mainwindow.h \
    common.h \
    camera.h \
    intersect.h \
    mesh.h \
    meshbuilder.h \
    renderer.h \
    scenemanager.h \
    shape.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += .
INCLUDEPATH += 3rd_party/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32 {
    PWD_WIN = $${PWD}
    PWD_WIN ~= s,/,\\,g

    QMAKE_POST_LINK += $$quote(mkdir DestFolder)
    QMAKE_POST_LINK += $$quote(xcopy $${PWD_WIN}\\shaders $${OUT_PWD_WIN}\\shaders /E)
}
