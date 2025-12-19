QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    socialnetworkmainwindow.cpp \
    network.cpp \
    user.cpp \
    post.cpp \
    bio.cpp \
    messageFilter.cpp \

HEADERS += \
    socialnetworkmainwindow.h \
    network.h \
    user.h \
    post.h \
    bio.h \
    messageFilter.h \


FORMS += \
    socialnetworkmainwindow.ui

DISTFILES += \
    users.txt \
    posts.txt \
    bios.txt


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
