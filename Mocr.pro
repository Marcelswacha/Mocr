QT += core gui widgets
TARGET = Mocr
TEMPLATE = app
CONFIG += qt link_pkgconfig
PKGCONFIG += tesseract

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    ImageView.cpp

HEADERS += \
    MainWindow.h \
    ImageView.h

LIBS += -llept
