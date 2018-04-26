#-------------------------------------------------
#
# Project created by QtCreator 2015-10-26T15:36:44
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Laundry_Management_System
TEMPLATE = app


SOURCES += main.cpp\
        lms.cpp \
    pricelist.cpp \
    insertprice.cpp \
    invoice.cpp \
    insertinvoice.cpp \
    updateprice.cpp \
    viewandsearchprice.cpp \
    viewandsearchinvoice.cpp \
    customer.cpp \
    manageitem.cpp \
    salesreport.cpp

HEADERS  += lms.h \
    pricelist.h \
    insertprice.h \
    invoice.h \
    insertinvoice.h \
    updateprice.h \
    viewandsearchprice.h \
    viewandsearchinvoice.h \
    customer.h \
    manageitem.h \
    salesreport.h

FORMS    += lms.ui \
    pricelist.ui \
    insertprice.ui \
    invoice.ui \
    insertinvoice.ui \
    updateprice.ui \
    viewandsearchprice.ui \
    viewandsearchinvoice.ui \
    customer.ui \
    manageitem.ui \
    salesreport.ui
