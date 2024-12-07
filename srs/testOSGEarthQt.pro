#-------------------------------------------------
#
# Project created by QtCreator 2024-11-28T22:16:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testOSGEarthQt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow_osgearth.cpp \
    guieventhandler_mouseposition.cpp

HEADERS += \
        mainwindow_osgearth.h \
    guieventhandler_mouseposition.h

FORMS += \
        mainwindow_osgearth.ui

#osg osgQt

INCLUDEPATH += "E:\src\vcpkg\installed\x64-windows\include"
CONFIG(debug, debug|release){
    LIBS += -L"E:\src\vcpkg\installed\x64-windows\debug\lib" -losgd -losgUtild -losgViewerd  -losgGAd  -losgDBd  -lOpenThreadsd -lopengl32d
    LIBS += -L"E:\src\vcpkg\installed\x64-windows\debug\lib" -losgQOpenGLd
    LIBS += -L"E:\src\vcpkg\installed\x64-windows\debug\lib" -losgEarthd
}else{
    LIBS += -L"E:\src\vcpkg\installed\x64-windows\lib" -losg -losgUtil -losgViewer  -losgGA  -losgDB  -lOpenThreads -lopengl32
    LIBS += -L"E:\src\vcpkg\installed\x64-windows\lib" -losgQOpenGL
    LIBS += -L"E:\src\vcpkg\installed\x64-windows\lib" -losgEarth
}


#osg osgQt


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
