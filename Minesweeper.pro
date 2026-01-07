QT       += core gui widgets
CONFIG   += c++17

SOURCES += \
    src/controllers/gamecontroller.cpp \
    src/main.cpp \
    src/models/boardmodel.cpp \
    src/models/cellmodel.cpp \
    src/ui/boardwidget.cpp \
    src/ui/cell.cpp \
    src/windows/gamewindow.cpp \
    src/windows/mainwindow.cpp \
    src/windows/welcomewindow.cpp

HEADERS += \
    include/controllers/gamecontroller.hpp \
    include/headers.hpp \
    include/models/boardmodel.hpp \
    include/models/cellmodel.hpp \
    include/ui/boardwidget.hpp \
    include/ui/cell.hpp \
    include/windows/gamewindow.hpp \
    include/windows/mainwindow.hpp \
    include/windows/welcomewindow.hpp

RESOURCES += resources/resources.qrc

DISTFILES += \
    resources/icons/gameicon.png \
    resources/qss/game.qss \
