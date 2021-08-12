QT       += core gui
QT           += widgets svg
QT       += core xml
qtHaveModule(opengl): QT += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    camimageeditwidget.cpp \
    camlayersettingwidget.cpp \
    drawingboardscene.cpp \
    drawingboardview.cpp \
    graphicviewwidget.cpp \
    importfilewidget.cpp \
    layereditwidget.cpp \
    layerrenderwidget.cpp \
    listtreewidget.cpp \
    main.cpp \
    mainwindow.cpp \
    pathitem.cpp \
    procedurenavigationwidget.cpp \
    rectitem.cpp \
    svgparser.cpp

HEADERS += \
    camimageeditwidget.h \
    camlayersettingwidget.h \
    drawingboardscene.h \
    drawingboardview.h \
    graphicviewwidget.h \
    importfilewidget.h \
    layereditwidget.h \
    layerrenderwidget.h \
    listtreewidget.h \
    mainwindow.h \
    pathitem.h \
    procedurenavigationwidget.h \
    rectitem.h \
    svgparser.h

FORMS += \
    camimageeditwidget.ui \
    camlayersettingwidget.ui \
    graphicviewwidget.ui \
    importfilewidget.ui \
    layereditwidget.ui \
    layerrenderwidget.ui \
    listtreewidget.ui \
    mainwindow.ui \
    procedurenavigationwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
