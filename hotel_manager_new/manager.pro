#-------------------------------------------------
#
# Project created by QtCreator 2017-10-25T17:32:54
#
#-------------------------------------------------

QT       += core gui
QT       += xml
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = manager
TEMPLATE = app
QMAKE_MAC_SDK = macosx10.13
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    cpp_source/ui/login_window.cpp \
    cpp_source/core/main.cpp \
    cpp_source/ui/main_window.cpp \
    cpp_source/core/database_util.cpp \
    cpp_source/core/room.cpp \
    cpp_source/core/customer.cpp \
    cpp_source/ui/customer_dialog.cpp \
    cpp_source/ui/room_dialog.cpp \
    cpp_source/ui/edit_room_data.cpp \
    cpp_source/ui/edit_customerdata_dialog.cpp \
    cpp_source/ui/delete_dialog.cpp \
    cpp_source/ui/pay_information_dialog.cpp \
    cpp_source/ui/number_input_dialog.cpp \
    cpp_source/ui/vip_checkin_dialog.cpp \
    cpp_source/ui/dateinput_dialog.cpp

HEADERS += \
    cpp_source/ui/login_window.h \
    cpp_source/ui/main_window.h \
    cpp_source/core/database_util.h \
    cpp_source/core/room.h \
    cpp_source/core/customer.h \
    cpp_source/ui/customer_dialog.h \
    cpp_source/ui/room_dialog.h \
    cpp_source/ui/edit_room_data.h \
    cpp_source/ui/edit_customerdata_dialog.h \
    cpp_source/ui/delete_dialog.h \
    cpp_source/ui/pay_information_dialog.h \
    cpp_source/ui/number_input_dialog.h \
    cpp_source/ui/vip_checkin_dialog.h \
    cpp_source/ui/dateinput_dialog.h

FORMS += \
    ui/login_window.ui \
    ui/main_window.ui \
    ui/customer_dialog.ui \
    ui/room_dialog.ui \
    ui/edit_room_data.ui \
    ui/edit_customerdata_dialog.ui \
    ui/delete_dialog.ui \
    ui/pay_information_dialog.ui \
    ui/number_input_dialog.ui \
    ui/vip_checkin_dialog.ui \
    ui/dateinput_dialog.ui
