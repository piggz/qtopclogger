# Add more folders to ship with the application, here
folder_01.source = qml/QtOpcLogger
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
QMAKE_CFLAGS=/D _USING_V110_SDK71_
QMAKE_CXXFLAGS=/D _USING_V110_SDK71_

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

QT += qml quick widgets printsupport webview
#CONFIG += c++11

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    opclogger.cpp \
    livedatamodel.cpp \
    qmlsettings.cpp \
    qcustomplot.cpp \
    plotdialog.cpp \
    opchistory.cpp \
    fileio.cpp \
    grouplogger.cpp \
    groupdatamodel.cpp \
    reporttemplatemodel.cpp
LIBS += -lC:/QtOpcSdk/QtOpc -L"C:\Program Files\Microsoft SDKs\Windows\v7.1A\Lib"
INCLUDEPATH += C:/QtOpcSdk "C:\Program Files\Microsoft SDKs\Windows\v7.1A\Include"

# Installation path
# target.path =

#include(qtquick1applicationviewer/qtquick1applicationviewer.pri)

# Default rules for deployment.
include(deployment.pri)

OTHER_FILES += \
    QtOpc/QtOpc.lib \
    QtOpc/QtOpc.exp \
    QtOpc/QtOpc.dll.embed.manifest \
    QtOpc/QtOpc.dll \
    tags.db

HEADERS += \
    opclogger.h \
    livedatamodel.h \
    qmlsettings.h \
    qcustomplot.h \
    plotdialog.h \
    opchistory.h \
    fileio.h \
    grouplogger.h \
    groupdatamodel.h \
    reporttemplatemodel.h

DISTFILES += \
    tags.db \
    deployment.pri \
    qml/QtOpcLogger/main.qml \
    qml/QtOpcLogger/TagEditor.qml \
    qml/QtOpcLogger/TagViewer.qml \
    qml/QtOpcLogger/GroupEditor.qml \
    qml/QtOpcLogger/GroupViewer.qml \
    qml/QtOpcLogger/ReportViewer.qml

RESOURCES += \
    resources.qrc

FORMS += \
    plotdialog.ui
