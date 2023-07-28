QT = core

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        numberofprecedinglettersiseven.cpp \
        reduplicator.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-mortal-engine-Desktop_Qt_5_15_1_MinGW_64_bit-Release/mortal-engine/release/ -lmortalengine
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-mortal-engine-Desktop_Qt_5_15_1_MinGW_64_bit-Debug/mortal-engine/debug/ -lmortalengine
else:unix: LIBS += -L$$PWD/../build-mortal-engine-Desktop_Qt_5_15_1_MinGW_64_bit-Release/mortal-engine/ -lmortalengine

INCLUDEPATH += $$PWD/../mortal-engine/mortal-engine
DEPENDPATH += $$PWD/../mortal-engine/mortal-engine

HEADERS += \
    numberofprecedinglettersiseven.h \
    reduplicator.h
