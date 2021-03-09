QT += widgets

CONFIG += c++11
CONFIG -= app_bundle

include(vendor/vendor.pri)

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        BufferSaver.cpp \
        CustomKeySequenceEdit.cpp \
        CutScreenshot.cpp \
        RunGuard.cpp \
        ScreenScene.cpp \
        Screenshot.cpp \
        SettingsManager.cpp \
        SimpleScreenshot.cpp \
        dialog.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    dialog.ui

HEADERS += \
    BufferSaver.h \
    CustomKeySequenceEdit.h \
    CutScreenshot.h \
    RunGuard.h \
    ScreenScene.h \
    Screenshot.h \
    SettingsManager.h \
    SimpleScreenshot.h \
    dialog.h

RESOURCES += \
    icons.qrc
