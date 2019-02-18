#-------------------------------------------------
#
# Project created by QtCreator 2018-10-09T23:32:58
#
#-------------------------------------------------

QT       += core gui

QT       += serialport
QT += multimedia
QT += multimediawidgets

#头文件路径
#头文件路径
INCLUDEPATH +=  D:/Qt/opencv330Lib/include\
                D:/Qt/opencv330Lib/include/opencv\
                D:/Qt/opencv330Lib/include/opencv2

LIBS += D:/Qt/opencv330Lib/lib/libopencv_core330.dll.a\
        D:/Qt/opencv330Lib/lib/libopencv_highgui330.dll.a\
        D:/Qt/opencv330Lib/lib/libopencv_ml330.dll.a\
        D:/Qt/opencv330Lib/lib/libopencv_imgproc330.dll.a\
        D:/Qt/opencv330Lib/lib/libopencv_imgcodecs330.dll.a\
        D:/Qt/opencv330Lib/lib/libopencv_stitching330.dll.a\
        D:/Qt/opencv330Lib/lib/libopencv_calib3d330.dll.a\
        D:/Qt/opencv330Lib/lib/libopencv_features2d330.dll.a\
        D:/Qt/opencv330Lib/lib/libopencv_flann330.dll.a\
        D:/Qt/opencv330Lib/lib/libopencv_video330.dll.a\
        D:/Qt/opencv330Lib/lib/libopencv_objdetect330.dll.a\
        D:/Qt/opencv330Lib/lib/libopencv_videoio330.dll.a\
        D:/Qt/opencv330Lib/lib/libopencv_photo330.dll.a\
        D:/Qt/opencv330Lib/lib/libopencv_shape330.dll.a\
        D:/Qt/opencv330Lib/lib/libopencv_superres330.dll.a\
        D:/Qt/opencv330Lib/lib/libopencv_videostab330.dll.a


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtOpencvmp4
TEMPLATE = app
DEFINES +=HAVE_CONFIG_H

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    qrcode/bitstream.c \
    qrcode/mask.c \
    qrcode/mmask.c \
    qrcode/mqrspec.c \
    qrcode/qrencode.c \
    qrcode/qrinput.c \
    qrcode/qrspec.c \
    qrcode/rscode.c \
    qrcode/split.c

HEADERS += \
        mainwindow.h \
    qrcode/bitstream.h \
    qrcode/config.h \
    qrcode/mask.h \
    qrcode/mmask.h \
    qrcode/mqrspec.h \
    qrcode/qrencode.h \
    qrcode/qrencode_inner.h \
    qrcode/qrinput.h \
    qrcode/qrspec.h \
    qrcode/rscode.h \
    qrcode/split.h

FORMS += \
        mainwindow.ui

OTHER_FILES += \
    qrcode/config.h.in

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ico.rc

RC_FILE += ico.rc

RESOURCES += \
    qrc.qrc
