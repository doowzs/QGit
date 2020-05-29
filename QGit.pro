TEMPLATE += app
QT += core widgets
CONFIG += object_parallel_to_source

DEFINES += "CMAKE_VERSION_MAJOR=1"
DEFINES += "CMAKE_VERSION_MINOR=0"
DEFINES += "CMAKE_VERSION_PATCH=0"

INCLUDEPATH += src/headers src/3rdparty

SOURCES += src/*.cpp
HEADERS += src/headers/*.h
RESOURCES += src/resources/*.qrc

LIBS += -lz # ZLib
QMAKE_CXXFLAGS += -std=c++17

CONFIG(debug, debug|release) {
  DESTDIR = build/debug
} else {
  DESTDIR = build/release
}
OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.u
