QT       += core gui sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abstractdatabaseelement.cpp \
    additionalmnemonic.cpp \
    additionalmnemonicaddwindow.cpp \
    conversionformula.cpp \
    customtreeview.cpp \
    databasemanager.cpp \
    databasestorage.cpp \
    main.cpp \
    mainmnemonic.cpp \
    mainmnemonicaddwindow.cpp \
    mainwindow.cpp \
    sensor.cpp \
    sensoraddwindow.cpp \
    tool.cpp \
    tooladdwindow.cpp

HEADERS += \
    abstractdatabaseelement.h \
    additionalmnemonic.h \
    additionalmnemonicaddwindow.h \
    conversionformula.h \
    customtreeview.h \
    databasemanager.h \
    databasestorage.h \
    mainmnemonic.h \
    mainmnemonicaddwindow.h \
    mainwindow.h \
    sensor.h \
    sensoraddwindow.h \
    tool.h \
    tooladdwindow.h

FORMS += \
    additionalmnemonicaddwindow.ui \
    mainmnemonicaddwindow.ui \
    mainwindow.ui \
    sensoraddwindow.ui \
    tooladdwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
