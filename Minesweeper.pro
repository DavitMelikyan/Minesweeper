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
    include/boardmodel.hpp \
    include/boardwidget.hpp \
    include/cell.hpp \
    include/gamecontroller.hpp \
    include/headers.hpp \
    include/mainwindow.hpp \
    include/welcomewindow.hpp

RESOURCES += resources/resources.qrc

DISTFILES += \
    resources/qss/welcome.qss

