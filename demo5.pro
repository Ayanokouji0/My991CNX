QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
TARGET=demo5
TEMPLATE=app
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    mainplot.cpp \
    mainwindow_.cpp \
    plot.cpp \
    qcustomplot.cpp

HEADERS += \
    mainwindow_.h \
    plot.h \
    qcustomplot.h

FORMS += \
    mainwindow_.ui

TRANSLATIONS += \
    demo5_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations
QMAKE_CXXFLAGS += -Wa,-mbig-obj
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
