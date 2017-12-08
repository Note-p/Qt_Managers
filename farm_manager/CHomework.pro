#-------------------------------------------------
#
# Project created by QtCreator 2017-07-17T14:28:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CHomework
TEMPLATE = app

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
        CppSource/main.cpp \
        CppSource/mainwindow.cpp \
    Csource/MyStringUtil.c \
    Csource/PlantingInfo.c \
    Csource/VegInfo.c \
    Csource/VegTypeEnum.c \
    CppSource/add_plantinfo_dialog.cpp \
    CppSource/add_vegtype_dialog.cpp \
    CppSource/edit_plantinfo_dialog.cpp \
    CppSource/edit_veginfo_dialog.cpp \
    CppSource/imformation_dialog.cpp \
    CppSource/notfound_dialog.cpp \
    CppSource/yearinput_dialog.cpp \
    CppSource/delete_plantinfo_dialog.cpp \
    CppSource/searchinput_dialog.cpp \
    CppSource/delete_veginfo_dialog.cpp \
    Csource/PlantInfoListSort.c \
    Csource/ListAll.c \
    Csource/TypeInfo.c \
    Csource/VegInfoListSort.c \
    CppSource/add_type_dialog.cpp \
    CppSource/delete_type_dialog.cpp \
    CppSource/edit_type_dialog.cpp \
    CppSource/search2_input_dialog.cpp \
    CppSource/range_input_dialog.cpp \
    CppSource/vegcode_input_dialog.cpp \
    Csource/VegDataBackupUtil.c

HEADERS += \
        CppSource/mainwindow.h \
    Csource/MyStringUtil.h \
    Csource/PlantingInfo.h \
    Csource/sys.h \
    Csource/VegInfo.h \
    Csource/VegTypeEnum.h \
    Csource/cppincludes.h \
    CppSource/add_plantinfo_dialog.h \
    CppSource/add_vegtype_dialog.h \
    CppSource/edit_plantinfo_dialog.h \
    CppSource/edit_veginfo_dialog.h \
    CppSource/imformation_dialog.h \
    CppSource/notfound_dialog.h \
    CppSource/yearinput_dialog.h \
    CppSource/delete_plantinfo_dialog.h \
    CppSource/searchinput_dialog.h \
    CppSource/delete_veginfo_dialog.h \
    Csource/PlantInfoListSort.h \
    Csource/ListAll.h \
    Csource/TypeInfo.h \
    Csource/VegInfoListSort.h \
    CppSource/add_type_dialog.h \
    CppSource/delete_type_dialog.h \
    CppSource/edit_type_dialog.h \
    CppSource/search2_input_dialog.h \
    CppSource/range_input_dialog.h \
    CppSource/vegcode_input_dialog.h \
    Csource/VegDataBackupUtil.h


FORMS += \
        UI/mainwindow.ui \
    UI/add_plantinfo_dialog.ui \
    UI/add_vegtype_dialog.ui \
    UI/edit_plantinfo_dialog.ui \
    UI/edit_veginfo_dialog.ui \
    UI/imformation_dialog.ui \
    UI/notfound_dialog.ui \
    UI/yearinput_dialog.ui \
    UI/delete_plantinfo_dialog.ui \
    UI/searchinput_dialog.ui \
    UI/delete_veginfo_dialog.ui \
    UI/add_type_dialog.ui \
    UI/delete_type_dialog.ui \
    UI/edit_type_dialog.ui \
    UI/search2_input_dialog.ui \
    UI/range_input_dialog.ui \
    UI/vegcode_input_dialog.ui
