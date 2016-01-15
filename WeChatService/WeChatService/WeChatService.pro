TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    wechatservice.cpp \
    userservice.cpp \
    userdb.cpp \
    basedb.cpp

HEADERS += \
    wechatservice.h \
    userservice.h \
    userdb.h \
    basedb.h

LIBS +=  -lboost_system -lboost_thread
