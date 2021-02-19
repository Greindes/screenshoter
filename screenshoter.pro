QT += widgets gui

CONFIG += c++11 console
CONFIG -= app_bundle

include(vendor/vendor.pri)

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        buffersaver.cpp \
        customkeysequenceedit.cpp \
        dialog.cpp \
        main.cpp \
        screenshot.cpp \
        simplescreenshot.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    dialog.ui

HEADERS += \
    buffersaver.h \
    customkeysequenceedit.h \
    dialog.h \
    screenshot.h \
    simplescreenshot.h
