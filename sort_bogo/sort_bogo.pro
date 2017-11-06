TEMPLATE = lib

CONFIG += dll
HEADERS += bogoplugin.h \
bogosort.h
SOURCES += bogoplugin.cpp \
bogosort.cpp
INCLUDEPATH += ../interface_sort ../src

DESTDIR = ../bin

OBJECTS_DIR = .lib

UI_DIR = .ui

MOC_DIR = .moc

LIBS += ../interface_sort/libinterface_sort.a

TARGETDEPS += ../interface_sort/libinterface_sort.a

QT -= gui

