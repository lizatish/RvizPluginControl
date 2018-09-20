QT += gui core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += /opt/ros/kinetic/include
INCLUDEPATH += ../../devel/include
INCLUDEPATH += /liza/include
INCLUDEPATH += ~/catkin_ws/devel/include

SOURCES += src/drive_widget.cpp \
    src/boat_parameters.cpp \
    src/boat_server_node.cpp

DISTFILES += \
    CMakeLists.txt

FORMS += \ src/boat_parameters.ui

HEADERS += \
    src/drive_widget.h \
    src/boat_parameters.h \
    src/boat_server_node.h
