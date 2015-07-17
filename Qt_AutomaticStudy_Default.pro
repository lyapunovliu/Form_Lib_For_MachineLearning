#-------------------------------------------------
#
# Project created by QtCreator 2015-04-20T10:23:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_AutomaticStudy_Default
TEMPLATE = app


SOURCES += main.cpp\
        qt_automaticstudy_default.cpp \
    character_select_dlg.cpp \
    my_algorithm.cpp

HEADERS  += qt_automaticstudy_default.h \
    character_select_dlg.h \
    my_algorithm.h \
    Characters_Strip_Contour.h

FORMS    += qt_automaticstudy_default.ui \
    character_select_dlg.ui
INCLUDEPATH += D:/soft/software/opencv/opencv/build/include
INCLUDEPATH += D:/soft/software/opencv/opencv/build/include/opencv
INCLUDEPATH += D:/soft/software/opencv/opencv/build/include/opencv2
CONFIG(debug, debug|release) {
LIBS += -LD:\soft\software\opencv\opencv\build\x86\vc11\lib \
-lopencv_core246d \
-lopencv_highgui246d \
-lopencv_imgproc246d \
-lopencv_features2d246d \
-lopencv_calib3d246d \
-lopencv_video246d \
-lopencv_ml246d \

}
else {
LIBS += -LD:\soft\software\opencv\opencv\build\x86\vc11\lib \
-lopencv_core246 \
-lopencv_highgui246 \
-lopencv_imgproc246 \
-lopencv_features2d246 \
-lopencv_calib3d246 \
-lopencv_video246 \
-lopencv_ml246 \
}
