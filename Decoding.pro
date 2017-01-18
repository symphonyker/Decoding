TEMPLATE = app
CONFIG += console

SOURCES += main.cpp \
    filemanager.cpp \
    parsemanager.cpp \
    decdecrypter.cpp \
    codegenerator.cpp \
    threadpool.cpp

HEADERS += \
    filemanager.h \
    parsemanager.h \
    decdecrypter.h \
    codegenerator.h \
    threadpool.h

QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += /usr/include/openssl \
  $$(BOOST_ROOT)/include

LIBS += -L/usr/lib/x86_64-linux-gnu/ -lssl -lcrypto \
    -L$$(BOOST_ROOT)/lib -lboost_system -lboost_thread


