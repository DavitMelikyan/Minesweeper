QT       += core gui widgets
CONFIG   += c++17

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/welcomewindow.cpp \
    src/boardmodel.cpp \
    src/boardwidget.cpp \
    src/cell.cpp \
    src/gamecontroller.cpp

HEADERS += \
    headers/mainwindow.hpp \
    headers/welcomewindow.hpp \
    headers/boardmodel.hpp \
    headers/boardwidget.hpp \
    headers/cell.hpp \
    headers/gamecontroller.hpp \
    headers/headers.hpp

RESOURCES += resources/resources.qrc

DISTFILES += \
    resources/qss/welcome.qss

