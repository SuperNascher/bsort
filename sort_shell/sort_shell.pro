TEMPLATE = lib

CONFIG += dll

INCLUDEPATH += ../interface_sort

LIBS += ../interface_sort/libinterface_sort.a

TARGETDEPS += ../interface_sort/libinterface_sort.a

OBJECTS_DIR = .lib

UI_DIR = .ui

MOC_DIR = .moc

DESTDIR = ../bin

HEADERS += shellplugin.h \
shellsort.h
SOURCES += shellplugin.cpp \
shellsort.cpp
