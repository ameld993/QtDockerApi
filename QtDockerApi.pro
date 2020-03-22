TEMPLATE = lib

QT                  *= network

CONFIG              *= c++11

DESTDIR             = lib
OBJECTS_DIR         = obj
MOC_DIR             = moc

HEADERS += \
    dockerapi.h \
    dockerrequestgenerator.h \
    dockerreply.h

SOURCES += \
    dockerapi.cpp \
    dockerrequestgenerator.cpp \
    dockerreply.cpp


unix{
    libs.path = /usr/local/lib
    libs.files = $$OUT_PWD/lib/*

    headers.path = /usr/local/include/QtDockerApi
    headers.files = $$PWD/*.h

    INSTALLS += libs
    INSTALLS += headers
}
