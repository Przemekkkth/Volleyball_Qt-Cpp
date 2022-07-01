greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    game.cpp \
    gamescene.cpp \
    main.cpp \
    view.cpp

INCLUDEPATH += $$PWD/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/release/ -lbox2d
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/debug/ -lbox2d
else:unix: LIBS += -L$$PWD/libs/ -lbox2d

INCLUDEPATH += $$PWD/libs
DEPENDPATH += $$PWD/libs

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/release/libbox2d.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/debug/libbox2d.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/release/box2d.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/debug/box2d.lib
else:unix: PRE_TARGETDEPS += $$PWD/libs/libbox2d.a

HEADERS += \
    game.h \
    gamescene.h \
    view.h

RESOURCES += \
    resource.qrc
