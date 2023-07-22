TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

include($$PWD/../../osg-cookbook.pri)

LIBS += $$(OSG_HOME)/lib/osgd.lib
LIBS += $$(OSG_HOME)/lib/osgGAd.lib
LIBS += $$(OSG_HOME)/lib/osgViewerd.lib
LIBS += $$(OSG_HOME)/lib/osgDBd.lib
LIBS += $$(OSG_HOME)/lib/osgWidgetd.lib

SOURCES += \
        main.cpp
