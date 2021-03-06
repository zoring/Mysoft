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
    chatbuffer.cpp \
    friendsbuffer.cpp \
    elumdata.cpp \
    usersdatasave.cpp \
    databasemsg.cpp \
    groundservice.cpp \
    serchservice.cpp \
    updateservice.cpp \
    inserservice.cpp \
    deleteservice.cpp \
    userdbservice.cpp

HEADERS += \
    wechatservice.h \
    userservice.h \
    userdb.h \
    basedb.h \
    connetdb.h \
    dbcontrol.h \
    logindb.h \
    logincontrol.h \
    chatbuffer.h \
    friendsbuffer.h \
    elumdata.h \
    usersdatasave.h \
    databasemsg.h \
    groundservice.h \
    serchservice.h \
    updateservice.h \
    inserservice.h \
    deleteservice.h \
    userdbservice.h

LIBS +=  -lboost_system -lboost_thread -lmysqlclient -lboost_signals
