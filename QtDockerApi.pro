TEMPLATE = lib

QT                  *= network

CONFIG              *= c++11

DESTDIR             = lib
OBJECTS_DIR         = obj
MOC_DIR             = moc

HEADERS += \
    DockerEngine.h \
    DockerImage.h \
    DockerImageList.h \
    DockerImageListReply.h \
    DockerReply.h \
    DockerRequestGenerator.h

SOURCES += \
    DockerEngine.cpp \
    DockerImage.cpp \
    DockerImageList.cpp \
    DockerImageListReply.cpp \
    DockerReply.cpp \
    DockerRequestGenerator.cpp

unix{
    libs.path = /usr/local/lib
    libs.files = $$OUT_PWD/lib/*

    headers.path = /usr/local/include/QtDockerApi
    headers.files = $$PWD/*.h

    INSTALLS += libs
    INSTALLS += headers
}
