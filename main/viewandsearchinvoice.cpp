#include "viewandsearchinvoice.h"
#include "ui_viewandsearchinvoice.h"
#include <QMessageBox>
#include <Qtsql>
#include <QStringList>
#include <QString>
#include <QPdfWriter>
#include <QPainter>
#include <QUrl>
#include <QDesktopServices>

ViewAndSearchInvoice::ViewAndSearchInvoice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewAndSearchInvoice)
{
    ui->setupUi(this);


}

ViewAndSearchInvoice::~ViewAndSearchInvoice()
{
    delete ui;
}



void ViewAndSearchInvoice::on_searchButton_clicked()
{
    QString invoiceContact = ui->invoiceContactNo->text();
    QString check, check2;

    QSqlQueryModel *modelLaundry = new QSqlQueryModel();
    QSqlQuery queryLaundry;

    if (invoiceContact == NULL)
    {
        QMessageBox::warning(this,tr("Invalid Search."),tr("Please insert either invoice no. or contact no.."));
    }
    else
    {
        queryLaundry.prepare("SELECT InvoiceNo, ContactNo FROM INVOICE WHERE InvoiceNo='"+invoiceContact+"' or ContactNo='"+invoiceContact+"'");
        queryLaundry.exec();
        while (queryLaundry.next())
        {
            check = queryLaundry.value(0).toString();
            check2 = queryLaundry.value(1).toString();
        }

        if (check == invoiceContact or check2 == invoiceContact)
        {
            queryLaundry.prepare("SELECT InvoiceNo as 'Invoice No', ContactNo as 'Contact No', DroppedOffDate 'Dropped Off Date' FROM INVOICE WHERE InvoiceNo='"+invoiceContact+"' or ContactNo='"+invoiceContact+"'");
            queryLaundry.exec();

            modelLaundry->setQuery(queryLaundry);
            ui->invoiceTableView->setModel(modelLaundry);

            ui->invoiceContactNo->clear();

        }
        else
        {
            QMessageBox::warning(this,tr("Invalid Search."),tr("Please insert a valid invoice no. or contact no.."));
            ui->invoiceContactNo->clear();
        }
    }
}

void ViewAndSearchInvoice::on_loadAllButton_clicked()
{
    ui->invoiceContactNo->clear();

    QSqlQueryModel *modelLaundry = new QSqlQueryModel();

    QSqlQuery queryLaundry;
    queryLaundry.prepare("SELECT InvoiceNo as 'Invoice No', ContactNo as 'Contact No', DroppedOffDate 'Dropped Off Date' FROM INVOICE");
    queryLaundry.exec();
    modelLaundry->setQuery(queryLaundry);

    ui->invoiceTableView->setModel(modelLaundry);
}

void ViewAndSearchInvoice::on_invoiceTableView_activated(const QModelIndex &index)
{
    //ui->InvoiceListView->show();

    QString invoiceNo = ui->invoiceTableView->model()->data(index).toString();



    QString CustName, contactNo, droppedOffDate, readyDate;

    const int i = 15;
    QString itemName[i], itemCode[i], itemPrice[i];


    QSqlQuery queryLaundry;

    queryLaundry.prepare("SELECT c.CustName, i.ContactNo, i.DroppedOffDate, i.ReadyDate FROM CUSTOMER c, INVOICE i WHERE c.ContactNo = i.ContactNo AND i.InvoiceNo = '"+invoiceNo+"'");
    queryLaundry.exec();
    while (queryLaundry.next())
    {
        CustName = queryLaundry.value(0).toString();
        contactNo = queryLaundry.value(1).toString();
        droppedOffDate = queryLaundry.value(2).toString();
        readyDate = queryLaundry.value(3).toString();
    }

    queryLaundry.prepare("SELECT i.ItemName, i.ItemCode, p.ItemPrice FROM PRICELIST p, ITEM i WHERE p.ItemName=i.ItemName AND i.InvoiceNo = '"+invoiceNo+"'");
    queryLaundry.exec();
    for (int i = 0; i<15 ; i++)
    {
        if (queryLaundry.next())
        {
            itemName[i] = queryLaundry.value(0).toString();
            itemCode[i] = queryLaundry.value(1).toString();
            itemPrice[i] = queryLaundry.value(2).toString();
        }
    }

    double total,finalTotal = 0.00;

    queryLaundry.exec("SELECT SUM(ItemPrice)FROM PRICELIST, ITEM WHERE PRICELIST.ItemName=ITEM.ItemName AND ITEM.InvoiceNo = '"+invoiceNo+"'");

    if (queryLaundry.next())
        total += queryLaundry.value(0).toDouble();

    if (total >= 50)
    {
        finalTotal = (total * 0.90) ;
    }
    else
    {
        finalTotal = total;
    }




    QString fileName = tr("../Laundry_Management_System/invoice.pdf");
    QPdfWriter pdf(fileName);
    QPainter painter(&pdf);
    pdf.setPageSize(QPagedPaintDevice::A4);

    painter.drawImage(QRect(150,0,4800,2160), QImage("../Laundry_Management_System/logo BBL"));

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(5200,800,"BIG BOSS LAUNDRY SDN BHD");

    painter.setFont(QFont("Arial", 10, QFont::Normal));
    painter.drawText(5200,1200,"Freeport A Famosa, Unit 88 and 89");
    painter.drawText(5200,1400,"Melaka, Malaysia.");
    painter.drawText(5200,1600,"Tel: 062820333");
    painter.drawText(5200,1800,"Email: bigbosslaundry@gmail.com");
    painter.drawText(5200,2000,"Visit us at www.bigbosslaundry.com");

    QPen paintpen(Qt::black);
    paintpen.setWidth(30);
    painter.setPen(paintpen);
    painter.drawLine(0,2500,9600,2500);

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(6650,3000,"Tax Invoice:");
    painter.drawText(8350,3000,invoiceNo);

    painter.setFont(QFont("Arial", 12, QFont::Normal));
    painter.drawText(1000,3500,CustName);
    painter.drawText(1000,3800,contactNo);
    painter.drawText(1000,4100,"Dropped off: ");
    painter.drawText(2200,4100,droppedOffDate);
    painter.setFont(QFont("Arial", 14, QFont::Bold));
    painter.drawText(1000,4400,"Ready on: ");
    painter.drawText(2300,4400,readyDate);

    painter.setFont(QFont("Arial", 16, QFont::Bold));
//    painter.drawText(1200, 5100, "No.");
    painter.drawText(2500,5100,"Item");
    painter.drawText(6500,5100,"Amount (RM)");
    paintpen.setWidth(30);
    painter.setPen(paintpen);
    painter.drawLine(0,5200,9600,5200);




    for (int a=5800, i=0; i<10;i++, a+=600)
    {
        painter.setFont(QFont("Arial", 16, QFont::Bold));
        painter.drawText(2500,a,itemName[i]);
        painter.setFont(QFont("Arial", 16, QFont::Normal));
        painter.drawText(6500,a,itemPrice[i]);
        painter.setFont(QFont("Arial", 10, QFont::Normal));
        painter.drawText(3500,a,itemCode[i]);
    }

    paintpen.setWidth(30);
    painter.setPen(paintpen);
    painter.drawLine(0,10700,9600,10700);
    painter.setFont(QFont("Arial", 16, QFont::Normal));
    painter.drawText(5000,11300,"Sub Total:");
    painter.drawText(5000,11700,"Total:");
    painter.drawText(7200,11300,"RM "+QString::number(total));
    painter.drawText(7200,11700,"RM "+QString::number(finalTotal));
    painter.setFont(QFont("Arial", 20, QFont::Bold));
    painter.setPen(Qt::blue);
    painter.drawText(6300,13000,"PAID!");

    painter.setPen(Qt::black);

    painter.end();
    QDesktopServices::openUrl(QUrl("file:///C:/Users/user-pc/Documents/Laundry_Management_System/invoice.pdf", QUrl::TolerantMode));


}

void ViewAndSearchInvoice::on_backButton_clicked()
{
    QSqlQueryModel *modelLaundry = new QSqlQueryModel();
    modelLaundry->setQuery("");
    ui->invoiceTableView->setModel(modelLaundry);

    this->close();
}
