TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    wechatservice.cpp \
    userservice.cpp \
    userdb.cpp \
    basedb.cpp \
    connetdb.cpp \
    dbcontrol.cpp \
    logindb.cpp \
    logincontrol.cpp \
    generfuntions.cpp

HEADERS += \
    wechatservice.h \
    userservice.h \
    userdb.h \
    basedb.h \
    connetdb.h \
    dbcontrol.h \
    logindb.h \
    logincontrol.h \
    generfuntions.h

LIBS +=  -lboost_system -lboost_thread -lmysqlclient -lboost_signals
