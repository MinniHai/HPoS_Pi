#-------------------------------------------------
#
# Project created by QtCreator 2016-09-25T09:35:47
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HPOS
TEMPLATE = app
QTPLUGIN += qsqlmysql

SOURCES += main.cpp\
    utils.cpp \
    session.cpp \
    shoppingcart.cpp \
    barcodescanner.cpp \
    keyboard.cpp \
    s_waiting.cpp \
    s_login.cpp \
    s_product.cpp \
    s_manufacture.cpp \
    s_search.cpp \
    s_payment.cpp \
    s_menu.cpp \
    s_checkout.cpp \
    e_user.cpp \
    e_product.cpp \
    e_picture.cpp \
    e_manifacturer.cpp \
    e_country.cpp \
    e_barcode.cpp \
    e_invoice.cpp \
    e_invoicedetail.cpp \
    e_category.cpp \
    customeqlabel.cpp \
    repository.cpp \
    s_shoppingcart.cpp \
    s_usermanager.cpp

HEADERS  += \
    utils.h \
    session.h \
    shoppingcart.h \
    barcodescanner.h \
    keyboard.h \
    ui_keyboard.h \
    s_login.h \
    s_waiting.h \
    s_product.h \
    s_manufacture.h \
    s_payment.h \
    s_search.h \
    s_menu.h \
    s_checkout.h \
    e_user.h \
    e_product.h \
    e_picture.h \
    e_country.h \
    e_barcode.h \
    e_invoice.h \
    e_invoicedetail.h \
    e_category.h \
    e_manufacturer.h \
    customeqlabel.h \
    repository.h \
    s_shoppingcart.h \
    s_usermanager.h

FORMS    += \
    keyboard.ui \
    productScreen.ui \
    paymentScreen.ui \
    searchScreen.ui \
    waitingScreen.ui \
    menuScreen.ui \
    manufactureScreen.ui \
    checkoutScreen.ui \
    loginScreen.ui \
    shoppingCartScreen.ui \
    s_usermanager.ui

RESOURCES += \
    images.qrc

OTHER_FILES += \
    HPOS.pro.user \
    HPOS.pro.user.3.3-pre1 \
    HPOS.pro.user.18 \
    HPOS.pro.user.aaa229c \
    HPOS.pro.user.b4b2bb7.3.3-pre1 \
    HPOS.pro.user.e263716.18

#CONFIG += build_ubuntu
#build_ubuntu{

#    INCLUDEPATH += /opt/opencv/include/opencv

#    INCLUDEPATH += /opt/zbar/include

#    LIBS += /opt/opencv/lib/*.so

#    LIBS += /opt/opencv/lib/*.so.2.4

#    LIBS += /opt/zbar/lib/*.so

#}

#build_arm{
#INCLUDEPATH += /opt/zbar.arm/include
#INCLUDEPATH += /opt/opencv2.4.13/include
#INCLUDEPATH += $$[QT_SYSROOT]/usr/local/include
#LIBS += -L$$[QT_SYSROOT]/usr/local/lib -lwiringPi
#LIBS += /opt/zbar.arm/lib/*.so
#LIBS += /opt/opencv2.4.13/lib/*.so
#LIBS += /opt/opencv2.4.13/lib/*.so.2.4
#LIBS += /opt/opencv2.4.13/lib/*.so.2.4.13

#}

DISTFILES += \
    HPOS.pro.user.e263716
