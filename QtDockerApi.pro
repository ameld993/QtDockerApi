TEMPLATE = lib

QT                  *= network quick

CONFIG              *= c++11

DESTDIR             = lib
OBJECTS_DIR         = obj
MOC_DIR             = moc

INCLUDEPATH += include

HEADERS += \
    include/Container.h \
    include/ContainerListReply.h \
    include/DockerReply.h \
    include/DockerRequestGenerator.h \
    include/Engine.h \
    include/Image.h \
    include/ImageListModel.h \
    include/ImageListReply.h

SOURCES += \
    src/Container.cpp \
    src/ContainerListReply.cpp \
    src/DockerReply.cpp \
    src/DockerRequestGenerator.cpp \
    src/Engine.cpp \
    src/Image.cpp \
    src/ImageListModel.cpp \
    src/ImageListReply.cpp


# --- make install ---
unix{
    libs.path = /usr/local/lib
    libs.files = $$OUT_PWD/lib/*

    headers.path = /usr/local/include/QtDockerApi
    headers.files = $$PWD/include/*.h

    INSTALLS += libs
    INSTALLS += headers
}
