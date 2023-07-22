PROJECT_DIR = $$PWD/..

CONFIG += force_debug_info

win32 {
    msvc:QMAKE_CXXFLAGS += -execution-charset:utf-8
    msvc:QMAKE_CXXFLAGS += -source-charset:utf-8
}

contains(QT_ARCH, "i386") {
    ARCH_NAME = x86
}
contains(QT_ARCH, "x86_64") {
    ARCH_NAME = x64
}

CONFIG(debug, debug | release) {
    TARGET = $${TARGET}d
    OBJECTS_DIR = $$PROJECT_DIR/build/$$TARGET/$$ARCH_NAME/Debug
} else {
    OBJECTS_DIR = $$PROJECT_DIR/build/$$TARGET/$$ARCH_NAME/Release
}

equals(TEMPLATE, "app") {
    DESTDIR = $$PROJECT_DIR/bin
}


INCLUDEPATH += $$(OSG_HOME)/include \
               $$(QTDIR)/include/QtOpenGL
