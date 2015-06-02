QT      +=  core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET   =  fatigue-detection
TEMPLATE =  app
SOURCES +=  main.cpp \
            window.cpp \
            mattoqimage.cpp \
            videoprocessor.cpp \
            image.cpp \
            ringbuffer.cpp \
    faceeyedetector.cpp \
    eyeanalyzer.cpp \
    eyeballcolordetector.cpp \
    yawningdetector.cpp
HEADERS +=  window.h \
            mattoqimage.h \
            videoprocessor.h \
            image.h \
            rect.h \
            ringbuffer.h \
            util.h \
            color.h \
    faceeyedetector.h \
    eyeanalyzer.h \
    eyeballcolordetector.h \
    yawningdetector.h \
    defines.h
FORMS   +=  window.ui
unix: LIBS += /usr/local/lib/libopencv_core.so \
            /usr/local/lib/libopencv_highgui.so \
            /usr/local/lib/libopencv_imgproc.so \
            /usr/local/lib/libopencv_photo.so \
            /usr/local/lib/libopencv_video.so \
            /usr/local/lib/libopencv_objdetect.so

win32: INCLUDEPATH += C:\opencv\include
win32: LIBS += -LC:\opencv\bin \
            -llibopencv_core249 \
            -llibopencv_highgui249 \
            -llibopencv_imgproc249 \
            -llibopencv_photo249 \
            -llibopencv_video249 \
            -llibopencv_objdetect249
RC_FILE += icon.rc
