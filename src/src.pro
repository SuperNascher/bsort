SOURCES += main.cpp \
    test.cpp \
    bmainwindow.cpp \
    bpluginmanager.cpp \
    bvaluewidget.cpp
TEMPLATE = app
CONFIG += warn_on \
    thread \
    qt
TARGET = bsort
DESTDIR = ../bin
OBJECTS_DIR = .lib
UI_DIR = .ui
MOC_DIR = .moc
INCLUDEPATH += ../interface_sort
LIBS += ../interface_sort/libinterface_sort.a
HEADERS += test.h \
    bmainwindow.h \
    bpluginmanager.h \
    bvaluewidget.h \
    brand.h
TARGETDEPS += ../interface_sort/libinterface_sort.a
FORMS += bmainwindow.ui
QT += widgets
