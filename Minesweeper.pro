QT       += core gui widgets
CONFIG   += c++17

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/models/boardmodel.cpp \
    src/models/cellmodel.cpp \
    src/welcomewindow.cpp \
    src/boardwidget.cpp \
    src/cell.cpp \
    src/gamecontroller.cpp

HEADERS += \
    include/boardmodel.hpp \
    include/boardwidget.hpp \
    include/cell.hpp \
    include/cellmodel.hpp \
    include/gamecontroller.hpp \
    include/headers.hpp \
    include/mainwindow.hpp \
    include/welcomewindow.hpp

RESOURCES += resources/resources.qrc

DISTFILES += \
    resources/qss/game.qss \
    resources/qss/welcome.qss

