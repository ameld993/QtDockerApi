TEMPLATE = lib

QT                  *= network quick

CONFIG              *= c++11

DESTDIR             = lib
OBJECTS_DIR         = obj
MOC_DIR             = moc

HEADERS += \
    DockerReply.h \
    DockerRequestGenerator.h \
    Engine.h \
    Image.h \
    ImageListModel.h \
    ImageListReply.h

SOURCES += \
    DockerReply.cpp \
    DockerRequestGenerator.cpp \
    Engine.cpp \
    Image.cpp \
    ImageListModel.cpp \
    ImageListReply.cpp

unix{
    libs.path = /usr/local/lib
    libs.files = $$OUT_PWD/lib/*

    headers.path = /usr/local/include/QtDockerApi
    headers.files = $$PWD/*.h

    INSTALLS += libs
    INSTALLS += headers
}
