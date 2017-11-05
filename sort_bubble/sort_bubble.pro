TEMPLATE = lib

CONFIG += dll
HEADERS += bubbleplugin.h \
bubblesort.h
SOURCES += bubbleplugin.cpp \
bubblesort.cpp
INCLUDEPATH += ../interface_sort

DESTDIR = ../bin

OBJECTS_DIR = .lib

UI_DIR = .ui

MOC_DIR = .moc

LIBS += ../interface_sort/libinterface_sort.a

TARGETDEPS += ../interface_sort/libinterface_sort.a

QT -= gui

