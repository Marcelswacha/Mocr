QT += core gui widgets
TARGET = Mocr
TEMPLATE = app
CONFIG += qt link_pkgconfig
PKGCONFIG += tesseract

SOURCES += \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    MainWindow.h

LIBS += -llept
