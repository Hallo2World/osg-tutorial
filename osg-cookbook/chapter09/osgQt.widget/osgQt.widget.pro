#-------------------------------------------------
#
# Project created by QtCreator 2023-04-14T09:51:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = osgQt.widget
TEMPLATE = app

include($$PWD/../../osg-cookbook.pri)

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
        main.cpp

HEADERS +=

FORMS += \

LIBS += $$(OSG_HOME)/lib/osgd.lib
LIBS += $$(OSG_HOME)/lib/osgGAd.lib
LIBS += $$(OSG_HOME)/lib/osgViewerd.lib
LIBS += $$(OSG_HOME)/lib/osgDBd.lib
LIBS += $$(OSG_HOME)/lib/osgQt5d.lib

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
